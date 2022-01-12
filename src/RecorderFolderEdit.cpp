#include "Recorder.hpp"
#include "RecorderFolderEdit.hpp"
#include "sql/RecorderFolder.hpp"
#include "settings.hpp"
#include "utils.hpp"

RecorderFolderEdit::RecorderFolderEdit()
{
	mUndoIndex = 0;
}

void RecorderFolderEdit::add()
{
	mId = 0;
	mFolder = new RecorderFolder(recorder->mSda);
	start();
}

void RecorderFolderEdit::open(long id)
{
	mId = id;
	mFolder = new RecorderFolder(recorder->mSda);
	if(!mFolder->get(id))
	{
		toastUp("Folder not found!");
		return;
	}

	start();
}

void RecorderFolderEdit::start()
{
	QmlDocument *qml = loadQml("asset:///folder_edit.qml");
	if(qml)
	{
		qml->setParent(this);

		mPage = qml->createRootObject<Page>();
		if(mPage)
		{
			mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title("Add Folder").visibility(getUI() == 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden));
			mPage->titleBar()->setAcceptAction(ActionItem::create().title("Save").onTriggered(this, SLOT(onSave())));
			mPage->titleBar()->setDismissAction(ActionItem::create().title("Cancel").onTriggered(this, SLOT(onClose())));

			mImageTheme		= mPage->findChild<ImageView*>("themeImage");

			mContainerTitle	= mPage->findChild<Container*>("titleContainer");
			mContainerNav	= mPage->findChild<Container*>("navContainer");

			mLabelTitle		= mPage->findChild<Label*>("titleLabel");

			mTextTitle		= mPage->findChild<TextField*>("titleText");
			mTextDesc		= mPage->findChild<TextArea*>("descText");

//			QObject::connect(mTextDesc, SIGNAL(textChanging(const QString)), this, SLOT(onTextChanging(const QString)));

			QObject::connect(mTextDesc->input(), SIGNAL(submitted(bb::cascades::AbstractTextControl *)), this, SLOT(onSubmitted(bb::cascades::AbstractTextControl *)));

			mImageSave		= mPage->findChild<ImageView*>("saveImage");
			mImageDelete	= mPage->findChild<ImageView*>("deleteImage");
			mImageClose		= mPage->findChild<ImageView*>("closeImage");

			if(mId > 0)
			{
				mPage->addAction(ActionItem::create().title("Delete").image(Image("asset:///images/delete.png")).onTriggered(this, SLOT(onDelete() )), ActionBarPlacement::OnBar);
			}
//			mPage->addAction(ActionItem::create().title("Save").image(Image("asset:///images/yes.png")).onTriggered(this, SLOT(onSave() )), ActionBarPlacement::OnBar);


			QObject::connect(mImageSave,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchSave(bb::cascades::TouchEvent*)));
			QObject::connect(mImageClose,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchClose(bb::cascades::TouchEvent*)));
			QObject::connect(mImageDelete, 	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchRemove(bb::cascades::TouchEvent*)));

			QObject::connect(recorder, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));

			setAppTheme(mImageTheme, getThemes());

			if(mId == 0)
			{
				mLabelTitle->setText("Add Folder");
				mImageDelete->setEnabled(false);
				mImageDelete->setOpacity(0);
			}
			else
			{
				mLabelTitle->setText("Edit Folder");

				mTextTitle->setText(mFolder->title);
				mTextDesc->setText(mFolder->desc);
			}

			onSettingsChanged();

			QObject::connect(recorder->mNav, SIGNAL(pushTransitionEnded(bb::cascades::Page*)), this, SLOT(onPushed(bb::cascades::Page*)));
			QObject::connect(recorder->mNav, SIGNAL(popTransitionEnded(bb::cascades::Page*)), this, SLOT(onPopped(bb::cascades::Page*)));
			recorder->mNav->push(mPage);

			if(mId == 0)
			{
				mTextTitle->requestFocus();
			}
		}
	}
}


void RecorderFolderEdit::setBB10(bool bb10)
{
	mPage->titleBar()->setTitle(mLabelTitle->text());

	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mPage->setActionBarVisibility(bb10 ? (mId > 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden) : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);
	mContainerNav->setVisible(bb10 ? false : true);

//	recorder->mNav->setBackButtonsVisible(false);
}

void RecorderFolderEdit::onPushed(bb::cascades::Page *page)
{
	if(page != NULL && page == mPage)
	{
		pushed();
	}
}

void RecorderFolderEdit::onPopped(bb::cascades::Page *page)
{
	if(page != NULL && page == mPage)
	{
		popped();
	}
}

void RecorderFolderEdit::onSettingsChanged()
{
	setAppTheme(mImageTheme, getThemes());

	setBB10(getUI() == 0);
}

void RecorderFolderEdit::onSubmitted(bb::cascades::AbstractTextControl *submitter)
{
	Q_UNUSED(submitter)

	save();
}

void RecorderFolderEdit::onTextChanging(const QString text)
{
	Q_UNUSED(text)
}

void RecorderFolderEdit::onTouchSave(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageSave->setOpacity(0.5);
		mImageSave->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageSave->setOpacity(1.0);
		mImageSave->setEnabled(true);

		if(event->isUp())
		{
			save();
		}
	}
}

void RecorderFolderEdit::onTouchRemove(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageDelete->setOpacity(0.5);
		mImageDelete->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageDelete->setOpacity(1.0);
		mImageDelete->setEnabled(true);

		if(event->isUp())
		{
			remove();
		}
	}
}

void RecorderFolderEdit::onTouchClose(bb::cascades::TouchEvent* event)
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
			close();
		}
	}
}

void RecorderFolderEdit::onSave()
{
	save();
}

void RecorderFolderEdit::onClose()
{
	close();
}

void RecorderFolderEdit::onDelete()
{
	remove();
}

void RecorderFolderEdit::pushed()
{
	OrientationSupport *support = OrientationSupport::instance();
	support->setSupportedDisplayOrientation(SupportedDisplayOrientation::DisplayPortrait);
}

void RecorderFolderEdit::popped()
{
	OrientationSupport *support = OrientationSupport::instance();
	support->setSupportedDisplayOrientation(SupportedDisplayOrientation::All);

	emit folderEditClosed();
}

void RecorderFolderEdit::save()
{
	if(mTextTitle->text().trimmed().size() == 0)
	{
		toastUp("Enter the folder title!");
		mTextTitle->requestFocus();
		return ;
	}

	mFolder->id 	= mId;
	mFolder->title 	= mTextTitle->text().trimmed();
	mFolder->desc 	= mTextDesc->text().trimmed();
	mFolder->stamp 	= QDateTime::currentDateTime().toTime_t();
	mFolder->flags 	= 0;
	mFolder->status = 1;

	if(mId == 0)
	{
		if(mFolder->insert())
		{
			emit folderChanged();
			close();
		}
		else
		{
			toastUp("Unable to save folder!");
		}
	}
	else
	{
		if(mFolder->update())
		{
			emit folderChanged();
			close();
		}
		else
		{
			toastUp("Unable to update folder!");
		}
	}

}

void RecorderFolderEdit::close()
{
	recorder->mNav->pop();
}

void RecorderFolderEdit::remove()
{
	if(!confirm(recorder->mAppName, "All recordings in this folder will be deleted!\n\nAre you sure you want to delete folder?")) return;
	{
		if(mFolder->remove(mFolder->id))
		{
			RecorderFile *file = new RecorderFile(recorder->mSda);
			file->removeFolderFiles(mFolder->id);

			emit folderChanged();
			close();
		}
		else
		{
			toastDown("Unable to delete folder!");
		}
	}
}



