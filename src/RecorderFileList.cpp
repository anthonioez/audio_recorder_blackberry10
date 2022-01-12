#include <QtAlgorithms>

#include "Recorder.hpp"
#include "RecorderFileList.hpp"
#include "RecorderEdit.hpp"
#include "RecorderFolderSelector.hpp"

#include "sql/RecorderFile.hpp"
#include "sql/RecorderFolder.hpp"

#include "settings.hpp"
#include "utils.hpp"

RecorderFileList::RecorderFileList()
{
	mFolder = 0;
}

void RecorderFileList::open(long mId)
{
	mFolder = mId;
	QmlDocument *qml = loadQml("asset:///filelist.qml");
	if(qml)
	{
		qml->setParent(this);

		mPage = qml->createRootObject<Page>();
		if(mPage)
		{
			mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title("Recordings").visibility(getUI() == 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden));

			mContainerTitle	= mPage->findChild<Container*>("titleContainer");
			mContainerNav	= mPage->findChild<Container*>("navContainer");

			mImageTheme		= mPage->findChild<ImageView*>("themeImage");

			mListFiles		= mPage->findChild<ListView*>("fileList");

			mLabelTitle		= mPage->findChild<Label*>("titleLabel");

			mImageClear		= mPage->findChild<ImageView*>("clearImage");
			mImageClose		= mPage->findChild<ImageView*>("closeImage");

		    QObject::connect(mPage, 		SIGNAL(playItem(QVariant)), 		this, SLOT(onPlayItem(QVariant)));
		    QObject::connect(mPage, 		SIGNAL(shareItem(QVariant)), 		this, SLOT(onShareItem(QVariant)));
		    QObject::connect(mPage,			SIGNAL(editItem(QVariant)), 		this, SLOT(onEditItem(QVariant)));
		    QObject::connect(mPage, 		SIGNAL(deleteItem(QVariant)), 		this, SLOT(onDeleteItem(QVariant)));
		    QObject::connect(mPage, 		SIGNAL(deleteItems()), 				this, SLOT(onDeleteItems()));
		    QObject::connect(mPage, 		SIGNAL(deviceMoveItem(QVariant)), 	this, SLOT(onDeviceMoveItem(QVariant)));
		    QObject::connect(mPage, 		SIGNAL(folderMoveItem(QVariant)), 	this, SLOT(onFolderMoveItem(QVariant)));

		    QObject::connect(mListFiles, 	SIGNAL(triggered(QVariantList)), 			this, SLOT(onOpenItem(QVariantList)));
			QObject::connect(mImageClear, 	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchClear(bb::cascades::TouchEvent*)));
			QObject::connect(mImageClose,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchClose(bb::cascades::TouchEvent*)));

			QObject::connect(recorder, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));

			mActionDelete = DeleteActionItem::create().title("Delete All").image(Image("asset:///images/clear.png")).onTriggered(this, SLOT(onClear()));

			mPage->addAction(mActionDelete, ActionBarPlacement::InOverflow);

			mDataModel = new QListDataModel<QVariant>();
			mListFiles->setDataModel(mDataModel);

			onSettingsChanged();

			QObject::connect(recorder->mNav, SIGNAL(popTransitionEnded(bb::cascades::Page*)), this, SLOT(onPopped(bb::cascades::Page*)));
			recorder->mNav->push(mPage);
		}
	}
}

void RecorderFileList::setBB10(bool bb10)
{
	mPage->titleBar()->setTitle(mLabelTitle->text());

	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mPage->setActionBarVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);

	mContainerNav->setVisible(bb10 ? false : true);

	recorder->mNav->setBackButtonsVisible(bb10 ? true : false);
}

void RecorderFileList::load()
{
	QVariantList tempList;

	QString title;
	RecorderFolder *folder = new RecorderFolder(recorder->mSda);
	if(folder->get(mFolder))
	{
		title = folder->title;
	}

	RecorderFile *data = new RecorderFile(recorder->mSda);
	QString sort = data->getSortTable(getSort());

	bool ret = false;
	ret = data->loadByFolder(mFolder, sort, getOrder() == 1);

	if(ret)
	{
		QVariantList list = data->getList();

		for(int i = 0; i < list.size(); i++)
		{
			QVariantMap map = list.at(i).value<QVariantMap>();

			RecorderFile *item = new RecorderFile(recorder->mSda);
			if(item->copy(map))
			{
				QVariantMap entry;

				QString ext 		= item->path.right(3).toLower();
				QString size 		= getByteFormat(item->size, 2);
				QString duration	= getDurationFormat(item->duration, true);
				bool secure			= item->path.startsWith(recorder->mAppPrvPath);

				QString ftitle = "";
				if(mFolder == 0 && item->folder > 0 && folder->get(item->folder))
				{
					ftitle = folder->title;
				}

				entry["_id"]		= QVariant((qlonglong)item->id);
				entry["folder"]		= QVariant((qlonglong)item->folder);
				entry["ftitle"]		= ftitle;
				entry["title"]		= item->title;
				entry["desc"]		= item->desc.isEmpty() ? "..." : getBodyForListing(item->desc);
				entry["path"]		= item->path;
				entry["size"]		= size;
				entry["duration"]	= duration;
				entry["date"]	 	= getTimeFormat(item->stamp);
				entry["status"]		= QVariant((qlonglong)item->status);
				entry["secure"]		= QVariant((bool)secure);

				entry["icon"]		= "asset:///images/icon.png";
				entry["type"]		= ext;
				entry["stamp"]		= QVariant((qlonglong)item->stamp);
				tempList.append(entry);
			}
		}
	}

//	qSort(tempList.begin(), tempList.end(), listCompare);

	updateListDataModel(mDataModel, tempList);

	mLabelTitle->setText(mDataModel->isEmpty() ? "No recordings available!" : (mFolder == 0 ? "All Recordings" : ("Recordings in '" + title + "'")));

	mImageClear->setEnabled(mDataModel->isEmpty() ? false : true);
	mImageClear->setOpacity(mDataModel->isEmpty() ? 0 : 1.0);

	mActionDelete->setEnabled(mDataModel->isEmpty() ? false : true);

	mPage->titleBar()->setTitle(mLabelTitle->text());

}

void RecorderFileList::clear()
{
	if(confirm(recorder->mAppName, "Are you sure you want to remove all recordings?"))
	{
		RecorderFile *data = new RecorderFile(recorder->mSda);
		if(data->load())
		{
			QVariantList list = data->getList();
			int count = 0;
			for(int i = 0; i < list.size(); i++)
			{
				QVariantMap map = list.at(i).value<QVariantMap>();

				long id = map["_id"].toLongLong();
				QString path 	= map["path"].toString();

				if(data->remove(id))
				{
					if(data->removeFile(path))
					{
					}

					count++;
				}
			}

			if(count > 0)
			{
				toastDown(QString("%1 recording%2 removed!").arg(count).arg(count > 1 ? "s" : ""));
			}
			else
			{
				toastDown("Unable to remove recording!");
			}
			load();

			return;
		}

		toastDown("No recording found!");
	}
}

void RecorderFileList::moveToFolder(long id, long folder)
{
	RecorderFolderSelector *move = new RecorderFolderSelector();
	QObject::connect(move, SIGNAL(folderSelected(long, long)), this, SLOT(onMoveComplete(long, long)));
	QObject::connect(move, SIGNAL(folderChanged()), this, SLOT(onMoveChanged()));
	QObject::connect(move, SIGNAL(folderCanceled()), this, SLOT(onMoveCanceled()));
	move->open(id, folder);
}

void RecorderFileList::moveToDevice(long id, const QString &src)
{
	QFileInfo srcInfo(src);
	QString dst = recorder->mAppDevPath + "/voice/"  + recorder->mAppFolder + "/"+ srcInfo.fileName();

	QFile dstFile(dst);
	if(dstFile.exists())
	{
		dstFile.remove();
	}

	if(QFile::rename(src, dst))
	{
		RecorderFile *item = new RecorderFile(recorder->mSda);
		if(item->get(id))
		{
			item->path = dst;
			if(item->update())
			{
				toastDown("Private recording moved to device memory!");

				load();

				return;
			}
		}

		QFile::rename(dst, src);
	}
}
void RecorderFileList::onClear()
{
	clear();
}

void RecorderFileList::onTouchClear(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageClear->setOpacity(0.5);
		mImageClear->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageClear->setOpacity(1.0);
		mImageClear->setEnabled(true);

		if(event->isUp())
		{
			clear();
		}
	}
}

void RecorderFileList::onTouchClose(bb::cascades::TouchEvent* event)
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
			if(mListFiles->multiSelectHandler())
			{
				mListFiles->multiSelectHandler()->setActive(false);
			}

			recorder->mNav->pop();
		}
	}
}

void RecorderFileList::onPopped(bb::cascades::Page *page)
{
	if(page != NULL && page == mPage)
	{
		emit fileListClosed();
	}
}

void RecorderFileList::onSettingsChanged()
{
	setAppTheme(mImageTheme, getThemes());
	setBB10(getUI() == 0);

	load();
}

void RecorderFileList::onOpenItem(QVariantList indexPath)
{
	QVariant data = mDataModel->data(indexPath);

	if(data.isValid())
	{
		QVariantMap map = data.value<QVariantMap>();

		long id = map["_id"].toLongLong();
		QString path  = map["path"].toString();

		QFileInfo fileinfo(path);
		if(!fileinfo.exists())
		{
			alert(recorder->mAppName, "File not found!");
			return;
		}

		if(getInternalPlayer())
		{
			RecorderFile *entry = new RecorderFile(recorder->mSda);
			if(entry->get(id))
			{
				RecorderEdit *edit = new RecorderEdit(false);
				QObject::connect(edit, SIGNAL(editClosed()), this, SLOT(onChanged()));
				edit->open(entry, false);
			}
		}
		else
		{
			path = "file://" + path;

			qDebug() << "invoke player: " << path;

			InvokeRequest cardRequest;
			cardRequest.setAction("bb.action.OPEN");
			cardRequest.setTarget("sys.mediaplayer.previewer");
			cardRequest.setUri(path);
			InvokeManager* invokeManager = new InvokeManager();
			invokeManager->invoke(cardRequest);
		}
	}
}

void RecorderFileList::onPlayItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();

	onOpenItem(list);
}

void RecorderFileList::onEditItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();

	QVariant data = mDataModel->data(list);

	if(data.isValid())
	{
		QVariantMap map = data.value<QVariantMap>();

		long id = map["_id"].toLongLong();

		RecorderFile *entry = new RecorderFile(recorder->mSda);
		if(entry->get(id))
		{
			RecorderEdit *edit = new RecorderEdit(false);
			connect(edit, SIGNAL(editChanged()), this, SLOT(onChanged()));
			edit->open(entry, true);
		}
	}
}

void RecorderFileList::onDeleteItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();
	int index = list.first().toInt();

	QVariant data = mDataModel->data(list);

	if(!confirm(recorder->mAppName, "Are you sure you want to delete this recording?")) return;

	if(data.isValid())
	{
		QVariantMap map = data.value<QVariantMap>();

		long id = map["_id"].toLongLong();
		QString path = map["path"].toString();

		RecorderFile *item = new RecorderFile(recorder->mSda);
		if(item->remove(id))
		{
			mDataModel->removeAt(index);

			if(!item->removeFile(path))
			{
				alert(recorder->mAppName, "Unable to delete recording file!");	//TODO alert if not on secure folder
			}
		}
		else
		{
			toastDown("Unable to remove recording!");
		}
	}
}

void RecorderFileList::onDeleteItems()
{
	QVariantList list = mListFiles->selectionList();

	if(list.size() == 0)
	{
		toastDown("No recording selected!");
		return;
	}

	if(!confirm(recorder->mAppName, QString("Are you sure you want to delete the selected recording%1?").arg(list.size() > 1 ? "s" : ""))) return;

	int count = 0;
	for(int i = 0; i < list.size(); i++)
	{
		QVariantList itemlist = list.at(i).value<QVariantList>();

		QVariant data = mDataModel->data(itemlist);
		if(data.isValid())
		{
			QVariantMap map = data.value<QVariantMap>();

			long id 		= map["_id"].toLongLong();
			QString path 	= map["path"].toString();

			RecorderFile *item = new RecorderFile(recorder->mSda);
			if(item->remove(id))
			{
				if(item->removeFile(path))
				{
				}
				count++;
			}
		}
	}

	if(count > 0)
	{
		toastDown(QString("%1 recording%2 deleted!").arg(count).arg(count > 1 ? "s" : ""));
	}
	else
	{
		toastDown("No recording deleted!");
	}

	load();
}

void RecorderFileList::onFolderMoveItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();
//	int index = list.first().toInt();

	QVariant data = mDataModel->data(list);
	qDebug() << "move 2 another folder : " << data;

	if(data.isValid())
	{
		QVariantMap map = data.value<QVariantMap>();

		long id = map["_id"].toLongLong();
		long folder = map["folder"].toLongLong();

		moveToFolder(id, folder);
	}
}

void RecorderFileList::onDeviceMoveItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();
//	int index = list.first().toInt();

	QVariant data = mDataModel->data(list);

	if(data.isValid())
	{
		if(!confirm(recorder->mAppName, "This recording will no longer be private!\n\nDo you want to continue?"))
		{
			return;
		}

		QVariantMap map = data.value<QVariantMap>();

		long id 		= map["_id"].toLongLong();
		QString src 	= map["path"].toString();

		moveToDevice(id, src);
	}
}

//TODO shred file
void RecorderFileList::onShareItem(QVariant indexPath)
{
	QVariantList list = indexPath.value<QVariantList>();

	QVariant data = mDataModel->data(list);
	qDebug() << "invoke share: " << data;

	if(data.isValid())
	{
		QVariantMap map = data.value<QVariantMap>();

		QString title 	= map["title"].toString();
		QString desc 	= map["desc"].toString();
		QString path 	= map["path"].toString();
		path  = "file://" + path;

		recorder->share(title, desc, path);
	}
}

void RecorderFileList::onChanged()
{
	load();
}

void RecorderFileList::onMoveComplete(long id, long folder)
{
	onSettingsChanged();

	RecorderFile *entry = new RecorderFile(recorder->mSda);
	if(entry->get(id))
	{
		entry->folder = folder;
		if(entry->update())
		{
			toastDown("Recording successfully moved!");

			emit fileListChanged();

			load();
			return;
		}
	}

	toastDown("Unable to move recording!");
}

void RecorderFileList::onMoveCanceled()
{
	onSettingsChanged();
}

void RecorderFileList::onMoveChanged()
{
	onSettingsChanged();

	emit fileListChanged();
}

