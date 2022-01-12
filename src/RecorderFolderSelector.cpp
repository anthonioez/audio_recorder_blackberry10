#include "Recorder.hpp"
#include "RecorderFolderEdit.hpp"
#include "RecorderFolderSelector.hpp"

#include "RecorderFileList.hpp"

#include "settings.hpp"
#include "utils.hpp"

RecorderFolderSelector::RecorderFolderSelector()
{
}

void RecorderFolderSelector::open(long id, long folder)
{
	mId	= id;
	mFolder = folder;
	QmlDocument *qml = loadQml("asset:///folder_selector.qml");
	if(qml)
	{
		qml->setParent(this);

		mPage = qml->createRootObject<Page>();
		if(mPage)
		{
			mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title("Select destination folder").visibility(getUI() == 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden));
			mPage->titleBar()->setDismissAction(ActionItem::create().title("Cancel").onTriggered(this, SLOT(onCancel())));

			mContainerTitle	= mPage->findChild<Container*>("titleContainer");
			mContainerNav	= mPage->findChild<Container*>("navContainer");

			mImageTheme		= mPage->findChild<ImageView*>("themeImage");

			mListFolders		= mPage->findChild<ListView*>("folderList");

			mLabelTitle		= mPage->findChild<Label*>("titleLabel");

			mImageAdd		= mPage->findChild<ImageView*>("addImage");
			mImageCancel	= mPage->findChild<ImageView*>("cancelImage");

		    QObject::connect(mPage, 			SIGNAL(selectItem(QVariant)), 	this, SLOT(onSelectItem(QVariant)));

		    QObject::connect(mListFolders, 		SIGNAL(triggered(QVariantList)), 			this, SLOT(onSelect(QVariantList)));
			QObject::connect(mImageAdd,			SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchAdd(bb::cascades::TouchEvent*)));
			QObject::connect(mImageCancel,		SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchCancel(bb::cascades::TouchEvent*)));

			QObject::connect(recorder, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));

			mPage->addAction(ActionItem::create().title("Add Folder").image(Image("asset:///images/add.png")).onTriggered(this, SLOT(onAdd())), ActionBarPlacement::OnBar);

			onSettingsChanged();

			load();

			recorder->mNav->push(mPage);
		}
	}
}

void RecorderFolderSelector::onSettingsChanged()
{
	setAppTheme(mImageTheme, getThemes());

	setBB10(getUI() == 0);
}

void RecorderFolderSelector::setBB10(bool bb10)
{
	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mPage->setActionBarVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);
	mContainerNav->setVisible(bb10 ? false : true);

	recorder->mNav->setBackButtonsVisible(false);
}

void RecorderFolderSelector::close()
{
	recorder->mNav->pop();
}

void RecorderFolderSelector::cancel()
{
	emit folderCanceled();

	close();
}

void RecorderFolderSelector::onCancel()
{
	cancel();
}

void RecorderFolderSelector::onAdd()
{
	addFolder();
}

void RecorderFolderSelector::onTouchAdd(bb::cascades::TouchEvent* event)
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
			addFolder();
		}
	}
}

void RecorderFolderSelector::onTouchCancel(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageCancel->setOpacity(0.5);
		mImageCancel->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageCancel->setOpacity(1.0);
		mImageCancel->setEnabled(true);

		if(event->isUp())
		{
			cancel();
		}
	}
}

void RecorderFolderSelector::load()
{
	mList.clear();

	RecorderFolder *data = new RecorderFolder(recorder->mSda);
	QString sort = data->getSortTable(getSort());



	if(mFolder != 0)
	{
		QVariantMap entry;

		RecorderFile *nitem = new RecorderFile(recorder->mSda);
		int total = nitem->getCountByFolder(0);
		bool current = (getCurrentFolder() == 0);

		entry["_id"]		= QVariant((qlonglong)0);
		entry["title"]		= "Default recordings" + QString(current ? "*" : "");
		entry["desc"]		= "Default recordings folder";
		entry["current"]	= QVariant((bool)current);
		entry["info"]		= total == 0 ? "Empty" : QString("%1 recording%2").arg(total).arg(total > 1 ? "s" : "");
		mList.append(entry);
	}

	if(data->load(sort, getOrder() == 1))
	{
		QVariantList list = data->getList();

		qDebug() << "size: " << list.size();

		for(int i = 0; i < list.size(); i++)
		{
			QVariantMap map = list.at(i).value<QVariantMap>();

			qDebug() << "map: " << map;

			RecorderFile *nitem = new RecorderFile(recorder->mSda);

			RecorderFolder *item = new RecorderFolder(recorder->mSda);
			if(item->copy(map))
			{
				QVariantMap fentry;

				if(mFolder != 0 && mFolder == item->id)
					continue;

				int total = nitem->getCountByFolder(item->id);

				fentry["_id"]		= QVariant((qlonglong)item->id);
				fentry["title"]		= item->title;
				fentry["desc"]		= item->desc.trimmed().isEmpty() ? "..." : getBodyForListing(item->desc);
				fentry["stamp"]		= QVariant((qlonglong)item->stamp);
				fentry["info"]		= total == 0 ? "Empty" : QString("%1 recording%2").arg(total).arg(total > 1 ? "s" : "");
				mList.append(fentry);

			}
		}
	}

	qSort(mList.begin(), mList.end(), listCompare);

	mDataModel = new QListDataModel<QVariant>(mList);
	mListFolders->setDataModel(mDataModel);
}

void RecorderFolderSelector::addFolder()
{
	RecorderFolderEdit *edit = new RecorderFolderEdit();
	QObject::connect(edit, SIGNAL(folderChanged()), this, SLOT(onFolderChanged()));
	QObject::connect(edit, SIGNAL(folderEditClosed()), this, SLOT(onFolderEditClosed()));
	edit->add();
}

void RecorderFolderSelector::onFolderChanged()
{
	emit folderChanged();

	load();
}

void RecorderFolderSelector::onFolderEditClosed()
{
	onSettingsChanged();
}

void RecorderFolderSelector::onSelect(QVariantList indexPath)
{
	QVariant data = mDataModel->data(indexPath);

	if(data.isValid())
	{
		QVariantMap map = data.value<QVariantMap>();

		long folder = map["_id"].toLongLong();

		emit folderSelected(mId, folder);

		close();
	}
}

void RecorderFolderSelector::onSelectItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();
	onSelect(list);
}
