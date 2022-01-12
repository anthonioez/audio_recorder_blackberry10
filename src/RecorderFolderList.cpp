#include <QtAlgorithms>

#include "Recorder.hpp"
#include "RecorderFileList.hpp"
#include "RecorderFolderList.hpp"
#include "RecorderFolderEdit.hpp"

#include "sql/RecorderFile.hpp"
#include "sql/RecorderFolder.hpp"

#include "settings.hpp"
#include "utils.hpp"

RecorderFolderList::RecorderFolderList()
{
//	mFolder = 0;
}

void RecorderFolderList::open()
{
	QmlDocument *qml = loadQml("asset:///folderlist.qml");
	if(qml)
	{
		qml->setParent(this);

		mPage = qml->createRootObject<Page>();
		if(mPage)
		{
			mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title("Recording Folders").visibility(getUI() == 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden));

			mContainerTitle	= mPage->findChild<Container*>("titleContainer");
			mContainerNav	= mPage->findChild<Container*>("navContainer");

			mImageTheme		= mPage->findChild<ImageView*>("themeImage");

			mListFolders		= mPage->findChild<ListView*>("folderList");

			mLabelTitle		= mPage->findChild<Label*>("titleLabel");

			mImageAdd		= mPage->findChild<ImageView*>("addImage");
			mImageClose		= mPage->findChild<ImageView*>("closeImage");

			QObject::connect(mPage, 		SIGNAL(defaultItem(QVariant)), 	this, SLOT(onDefaultItem(QVariant)));
			QObject::connect(mPage, 		SIGNAL(openItem(QVariant)), 	this, SLOT(onOpenItem(QVariant)));
			QObject::connect(mPage,			SIGNAL(editItem(QVariant)), 	this, SLOT(onEditItem(QVariant)));
		    QObject::connect(mPage, 		SIGNAL(deleteItem(QVariant)), 	this, SLOT(onDeleteItem(QVariant)));
		    QObject::connect(mPage, 		SIGNAL(deleteItems()), 			this, SLOT(onDeleteItems()));

		    QObject::connect(mListFolders, 	SIGNAL(triggered(QVariantList)), 			this, SLOT(onOpen(QVariantList)));
			QObject::connect(mImageAdd, 	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchAdd(bb::cascades::TouchEvent*)));
			QObject::connect(mImageClose,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchClose(bb::cascades::TouchEvent*)));

			QObject::connect(recorder, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));

			mPage->addAction(ActionItem::create().title("Add").image(Image("asset:///images/add.png")).onTriggered(this, SLOT(onAdd())), ActionBarPlacement::OnBar);

			mDataModel = new QListDataModel<QVariant>();
			mListFolders->setDataModel(mDataModel);

			onSettingsChanged();

			recorder->mNav->push(mPage);
		}
	}
}

void RecorderFolderList::setBB10(bool bb10)
{
	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mPage->setActionBarVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);

	mContainerNav->setVisible(bb10 ? false : true);

	recorder->mNav->setBackButtonsVisible(bb10 ? true : false);
}

void RecorderFolderList::load()
{
	QVariantList tempList;

	RecorderFolder *data = new RecorderFolder(recorder->mSda);
	QString sort = data->getSortTable(getSort());

	bool ret = false;
	ret = data->load(sort, getOrder() == 1);

	QVariantMap entry;

	RecorderFile *nitem = new RecorderFile(recorder->mSda);
	int total = nitem->getCountByFolder(0);
	bool current = (getCurrentFolder() == 0);

	entry["_id"]		= QVariant((qlonglong)0);
	entry["title"]		= "Default recordings" + QString(current ? "*" : "");
	entry["desc"]		= "Default recordings folder";
	entry["current"]	= QVariant((bool)current);
	entry["info"]		= total == 0 ? "Empty" : QString("%1 recording%2").arg(total).arg(total > 1 ? "s" : "");
	tempList.append(entry);

	if(ret)
	{
		QVariantList list = data->getList();

		for(int i = 0; i < list.size(); i++)
		{
			QVariantMap map = list.at(i).value<QVariantMap>();

			RecorderFolder *item = new RecorderFolder(recorder->mSda);
			if(item->copy(map))
			{
				QVariantMap entry;

				RecorderFile *nitem = new RecorderFile(recorder->mSda);
				int total = nitem->getCountByFolder(item->id);
				bool current = (getCurrentFolder() == item->id);

				entry["_id"]		= QVariant((qlonglong)item->id);
				entry["title"]		= item->title + (current ? "*" : "");
				entry["current"]	= QVariant((bool)current);
				entry["desc"]		= item->desc.trimmed().isEmpty() ? "..." : getBodyForListing(item->desc);
				entry["info"]		= total == 0 ? "Empty" : QString("%1 recording%2").arg(total).arg(total > 1 ? "s" : "");
				tempList.append(entry);
			}
		}
	}

//	qSort(tempList.begin(), tempList.end(), listCompare);

	updateListDataModel(mDataModel, tempList);

	updateList();
}

void RecorderFolderList::add()
{
	RecorderFolderEdit *edit = new RecorderFolderEdit();
	connect(edit, SIGNAL(folderChanged()), this, SLOT(onChanged()));
	connect(edit, SIGNAL(folderEditClosed()), this, SLOT(onEditClosed()));
	edit->add();
}

void RecorderFolderList::onAdd()
{
	add();
}

void RecorderFolderList::onTouchAdd(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageAdd->setOpacity(0.5);
		mImageAdd->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageAdd->setOpacity(1.0);
		mImageAdd->setEnabled(true);

		if(event->isUp())
		{
			add();
		}
	}
}

void RecorderFolderList::onTouchClose(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageClose->setOpacity(0.5);
		mImageClose->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageClose->setOpacity(1.0);
		mImageClose->setEnabled(true);

		if(event->isUp())
		{
			if(mListFolders->multiSelectHandler())
			{
				mListFolders->multiSelectHandler()->setActive(false);
			}

			recorder->mNav->pop();
		}
	}
}

void RecorderFolderList::onSettingsChanged()
{
	setAppTheme(mImageTheme, getThemes());
	setBB10(getUI() == 0);

	load();
}

void RecorderFolderList::onOpen(QVariantList indexPath)
{
	QVariant data = mDataModel->data(indexPath);

	if(data.isValid())
	{
		QVariantMap map = data.value<QVariantMap>();

		long id = map["_id"].toLongLong();
		QString path  = map["path"].toString();

		RecorderFileList *list = new RecorderFileList();
		connect(list, SIGNAL(fileListChanged()), this, SLOT(onChanged()));
		connect(list, SIGNAL(fileListClosed()), this, SLOT(onEditClosed()));
		list->open(id);
	}
}

void RecorderFolderList::onOpenItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();
	onOpen(list);
}

void RecorderFolderList::onDefaultItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();

	QVariant data = mDataModel->data(list);

	if(data.isValid())
	{
		QVariantMap map = data.value<QVariantMap>();

		long id 		= map["_id"].toLongLong();
		QString title	= map["title"].toString();

		setCurrentFolder(id);

		if(id == 0)
		{
			toast("Current recording folder set to default!");
		}
		else
		{
			toast("Current recording folder changed to '" + title + "'");
		}

		load();
	}
}

void RecorderFolderList::onEditItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();

	QVariant data = mDataModel->data(list);

	if(data.isValid())
	{
		QVariantMap map = data.value<QVariantMap>();

		long id = map["_id"].toLongLong();

		RecorderFolderEdit *edit = new RecorderFolderEdit();
		connect(edit, SIGNAL(folderChanged()), this, SLOT(onChanged()));
		connect(edit, SIGNAL(folderEditClosed()), this, SLOT(onEditClosed()));
		edit->open(id);
	}
}

void RecorderFolderList::onDeleteItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();
	int index = list.first().toInt();

	QVariant data = mDataModel->data(list);

	if(!confirm(recorder->mAppName, "All recordings in the folder will be deleted!\n\nAre you sure you want to delete this folder?")) return;

	if(data.isValid())
	{
		QVariantMap map = data.value<QVariantMap>();

		long id = map["_id"].toLongLong();
		QString path = map["path"].toString();

		RecorderFolder *item = new RecorderFolder(recorder->mSda);
		if(item->remove(id))
		{
			mDataModel->removeAt(index);

			if(getCurrentFolder() == id)
			{
				setCurrentFolder(0);

			}

			RecorderFile *nitem = new RecorderFile(recorder->mSda);
			nitem->removeFolderFiles(id);
		}
		else
		{
			toastDown("Unable to remove folder!");
		}
	}
}

void RecorderFolderList::onDeleteItems()
{
	QVariantList list = mListFolders->selectionList();

	if(list.size() == 0)
	{
		toastDown("No folder selected!");
		return;
	}

	if(!confirm(recorder->mAppName, "All recordings in selected folders will be deleted!\n\nAre you sure you want to delete the selected folders?")) return;

	int count = 0;
	for(int i = 0; i < list.size(); i++)
	{
		QVariantList itemlist = list.at(i).value<QVariantList>();

		QVariant data = mDataModel->data(itemlist);
		if(data.isValid())
		{
			QVariantMap map = data.value<QVariantMap>();

			long id 		= map["_id"].toLongLong();

			RecorderFolder *item = new RecorderFolder(recorder->mSda);
			if(item->remove(id))
			{
				if(getCurrentFolder() == id)
				{
					setCurrentFolder(0);
				}

				RecorderFile *nitem = new RecorderFile(recorder->mSda);
				nitem->removeFolderFiles(id);

				count++;
			}
		}
	}

	if(count > 0)
	{
		toastDown(QString("%1 folder%2 deleted!").arg(count).arg(count > 1 ? "s" : ""));
	}
	else
	{
		toastDown("No folder deleted!");
	}

	load();
}


void RecorderFolderList::onChanged()
{
	load();
}

void RecorderFolderList::onEditClosed()
{
	onSettingsChanged();
}

void RecorderFolderList::updateList()
{
	mLabelTitle->setText(mDataModel->isEmpty() ? "No folder available!" : "Recording Folders");
}
