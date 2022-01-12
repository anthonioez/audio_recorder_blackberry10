#include "Recorder.hpp"
#include "RecorderEdit.hpp"
#include "settings.hpp"
#include "utils.hpp"

RecorderEdit::RecorderEdit(bool asSheet)
{
	mAsSheet = asSheet;
	mAction = ACTION_READY;
}

void RecorderEdit::open(RecorderFile *file, bool e)
{
	mEdit = e;
	mEditMode = e;
	mEntry = file;
	if(file == NULL)
	{
		toastDown("Recording not found!");

		close();
		return;
	}

	QmlDocument *qml = loadQml("asset:///edit.qml");
	if(qml)
	{
		qml->setParent(this);

		mPage = qml->createRootObject<Page>();
		if(mPage)
		{
			mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title("Edit").visibility(getUI() == 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden));

			mActionAction 	= ActionItem::create().title("Edit"	).image(Image("asset:///images/edit.png")	).onTriggered(this, SLOT(onAction()));
			mActionPlay		= ActionItem::create().title("Play"	).image(Image("asset:///images/play.png")	).onTriggered(this, SLOT(onPlay()));
			mActionShare 	= ActionItem::create().title("Share").image(Image("asset:///images/share.png")	).onTriggered(this, SLOT(onShare()));

			mActionDelete 	= DeleteActionItem::create().title("Delete"	).image(Image("asset:///images/delete.png")	).onTriggered(this, SLOT(onDelete()));

			mPage->addAction(mActionPlay, ActionBarPlacement::OnBar);

			mPage->addAction(mActionAction, ActionBarPlacement::OnBar);
			mPage->addAction(mActionDelete, ActionBarPlacement::InOverflow);
			mPage->addAction(mActionShare, ActionBarPlacement::InOverflow);

			mContainerTitle	= mPage->findChild<Container*>("titleContainer");
			mContainerNav	= mPage->findChild<Container*>("navContainer");

			mImageTheme		= mPage->findChild<ImageView*>("themeImage");

			mContainerEdit	= mPage->findChild<Container*>("editContainer");
			mContainerView	= mPage->findChild<Container*>("viewContainer");
			mContainerSpeed	= mPage->findChild<Container*>("speedContainer");

			mLabelTitle		= mPage->findChild<Label*>("titleLabel");
//			mLabelStatus	= mPage->findChild<Label*>("statusLabel");
			mLabelBody		= mPage->findChild<Label*>("bodyLabel");

			mLabelSpeed 	= mPage->findChild<Label*>("speedLabel");

			mTextTitle		= mPage->findChild<TextField*>("titleText");
			mTextBody		= mPage->findChild<TextArea*>("bodyText");

			mLabelStart		= mPage->findChild<Label*>("startLabel");
			mLabelEnd		= mPage->findChild<Label*>("endLabel");

			mSliderSeek		= mPage->findChild<Slider*>("seekSlider");
			mSliderSpeed	= mPage->findChild<Slider*>("speedSlider");
			mSliderSpeed->setRange(1.0, 5);
			mSliderSpeed->setValue(1.0);

			QObject::connect(mSliderSpeed, SIGNAL(valueChanged(float)), this, SLOT(onSpeedSliderChanged(float)));
			QObject::connect(mSliderSpeed, SIGNAL(immediateValueChanged(float)), this, SLOT(onSpeedSliderImmediateChanged(float)));

			QObject::connect(mTextBody, SIGNAL(textChanging(const QString)), this, SLOT(onTextChanging(const QString)));

			mImageAction	= mPage->findChild<ImageView*>("actionImage");
			mImageDelete	= mPage->findChild<ImageView*>("deleteImage");

			mImagePlay		= mPage->findChild<ImageView*>("playImage");
			mImageShare		= mPage->findChild<ImageView*>("shareImage");
			mImageClose		= mPage->findChild<ImageView*>("closeImage");

			QObject::connect(mImageAction,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchAction(bb::cascades::TouchEvent*)));
			QObject::connect(mImageDelete,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchDelete(bb::cascades::TouchEvent*)));

			QObject::connect(mImagePlay,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchPlay(bb::cascades::TouchEvent*)));
			QObject::connect(mImageShare,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchShare(bb::cascades::TouchEvent*)));
			QObject::connect(mImageClose,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchClose(bb::cascades::TouchEvent*)));

			QObject::connect(recorder, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));

			mCounter = 0;
			setSliderPosition(mCounter);
			setSliderDuration(mEntry->duration);
			QObject::connect(mSliderSeek,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchSlider(bb::cascades::TouchEvent*)));

			onSettingsChanged();

			mTextTitle->setText(mEntry->title);
			mTextBody->setText(mEntry->desc);

			mLabelTitle->setText(mEntry->title);
			mLabelBody->setText(mEntry->desc);

			QObject::connect(this, SIGNAL(playingChanged(int, long)), recorder, SLOT(onPlayingChanged(int, long)));

			if(mAsSheet)
			{
				mSheet = Sheet::create();
				mSheet->setContent(mPage);
				QObject::connect(mSheet, SIGNAL(closed()), this, SLOT(onSheetClosed()));
				mSheet->open();
			}
			else
			{
				QObject::connect(recorder->mNav, SIGNAL(popTransitionEnded(bb::cascades::Page*)), this, SLOT(onPopped(bb::cascades::Page*)));
				recorder->mNav->push(mPage);
			}

			mImageDelete->setEnabled(mEntry->id > 0);
			mImageDelete->setOpacity(mEntry->id > 0 ? 1.0 : 0);

			if(mEdit)
			{
				edit();
			}
			else
			{
				view();

				play();
			}
		}
	}
}

void RecorderEdit::setBB10(bool bb10)
{
	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mPage->setActionBarVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);

	mContainerNav->setVisible(bb10 ? false : true);

	recorder->mNav->setBackButtonsVisible(bb10 ? true : false);
}

void RecorderEdit::edit()
{
	mEdit = true;
	OrientationSupport *support = OrientationSupport::instance();
	support->setSupportedDisplayOrientation(SupportedDisplayOrientation::DisplayPortrait);

	mLabelTitle->setText(mEntry->id == 0 ? "Save" : "Edit");
	mTextTitle->requestFocus();
	mImageAction->setImage(Image("asset:///images/yes.png"));
	mActionAction->setImage(Image("asset:///images/yes.png"));
	mActionAction->setTitle("Save");

	mContainerEdit->setVisible(true);
	mContainerView->setVisible(false);
}

void RecorderEdit::view()
{
	mEdit = false;
	OrientationSupport *support = OrientationSupport::instance();
	support->setSupportedDisplayOrientation(SupportedDisplayOrientation::All);

	mLabelTitle->setText(mEntry->title);
	mLabelBody->setText(mEntry->desc);
	mImageAction->setImage(Image("asset:///images/edit.png"));
	mActionAction->setImage(Image("asset:///images/edit.png"));
	mActionAction->setTitle("Edit");

	mContainerEdit->setVisible(false);
	mContainerView->setVisible(true);
}

void RecorderEdit::action()
{
	if(mEdit)
	{
		save(mEditMode);
	}
	else
	{
		edit();
	}
}

void RecorderEdit::play()
{
	if(mAction == ACTION_PLAYING)
	{
		pausePlaying();
	}
	else if(mAction == ACTION_PAUSED)
	{
		resumePlaying();
	}
	else
	{
		startPlaying();
	}
}

void RecorderEdit::share()
{
	if(mEdit)
	{
		if(mTextTitle->text().trimmed().size() == 0)
		{
			toastUp("Enter the title!");
			mTextTitle->requestFocus();
		}

		mEntry->title 	= mTextTitle->text().trimmed();
		mEntry->desc 	= mTextBody->text().trimmed();
	}

	QString title 	= mEntry->title;
	QString desc 	= mEntry->desc;
	QString path 	= mEntry->path;
	path  = "file://" + path;

	recorder->share(title, desc, path);
}

void RecorderEdit::popped()
{
	if(mAction == ACTION_PLAYING || mAction == ACTION_PAUSED)
	{
		stopPlaying();
	}

	OrientationSupport *support = OrientationSupport::instance();
	support->setSupportedDisplayOrientation(SupportedDisplayOrientation::All);

	emit editClosed();
}

void RecorderEdit::onAction()
{
	action();
}

void RecorderEdit::onPlay()
{
	play();
}

void RecorderEdit::onShare()
{
	share();
}

void RecorderEdit::onDelete()
{
	remove();
}

void RecorderEdit::onSheetClosed()
{
	popped();
}

void RecorderEdit::onPopped(bb::cascades::Page *page)
{
	if(page != NULL && page == mPage)
	{
		popped();
	}
}

void RecorderEdit::onSettingsChanged()
{
	setAppTheme(mImageTheme, getThemes());

	mContainerSpeed->setVisible(getShowSpeed());

	setBB10(getUI() == 0);
}

void RecorderEdit::onSubmitted(bb::cascades::AbstractTextControl *submitter)
{
	Q_UNUSED(submitter)

	save(mEditMode);
}

void RecorderEdit::onTextChanging(const QString text)
{
	Q_UNUSED(text)
}

void RecorderEdit::onTouchAction(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageAction->setOpacity(0.5);
		mImageAction->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageAction->setOpacity(1.0);
		mImageAction->setEnabled(true);

		if(event->isUp())
		{
			action();
		}
	}
}

void RecorderEdit::onTouchDelete(bb::cascades::TouchEvent* event)
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

void RecorderEdit::onTouchShare(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageShare->setOpacity(0.5);
		mImageShare->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageShare->setOpacity(1.0);
		mImageShare->setEnabled(true);

		if(event->isUp())
		{
			share();
		}
	}
}

void RecorderEdit::onTouchPlay(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImagePlay->setOpacity(0.5);
		mImagePlay->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImagePlay->setOpacity(1.0);
		mImagePlay->setEnabled(true);

		if(event->isUp())
		{
			play();
		}
	}
}

void RecorderEdit::onTouchClose(bb::cascades::TouchEvent* event)
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

void RecorderEdit::onTouchSlider(bb::cascades::TouchEvent* event)
{
	qDebug() << "**************************************************************";
	unsigned int value = mSliderSeek->value();
	unsigned int ivalue = mSliderSeek->immediateValue();

	if (event->isDown())
	{
		qDebug() << "slider touch down";
	}
	else if (event->isMove())
	{
		qDebug() << "slider touch move" << value << ivalue;

	}
	else if (event->isUp())
	{
		qDebug() << "slider touch up" << value << ivalue;

		if(mAction == ACTION_PLAYING)
		{
			mPlayer->seekTime(ivalue);
		}
		else if(mAction == ACTION_PAUSED)
		{
			mPlayer->seekTime(ivalue);
			resumePlaying();
		}
		else
		{
			startPlaying();
			mPlayer->seekTime(ivalue);
		}
	}
}

void RecorderEdit::onSpeedSliderImmediateChanged(float value)
{
	qDebug() << "speed: " << value;

//	QString str = QString::number((double)value, 'f', 1);
//	if(str == "1.0") str = "normal";
//	mLabelSpeed->setText(str);

}

void RecorderEdit::onSpeedSliderChanged(float value)
{
//	onSpeedSliderImmediateChanged(value);

	if(mAction == ACTION_PLAYING)
	{
		speedPlayingAudio((double)value);
	}
}

void RecorderEdit::onPlayerUpdate(bb::multimedia::MediaState::Type state)
{
	qDebug() << "playing state: " << state;
	if(state == MediaState::Stopped)
	{
		stopPlaying();
	}
}

void RecorderEdit::onPositionChanged(unsigned int position)
{
	qDebug() << "position changed: " << position;
	mCounter = position;

	if(mAction == ACTION_PLAYING)
	{
		setSliderPosition(position);
		emit playingChanged(mAction, mCounter);
	}
}

void RecorderEdit::onDurationChanged(unsigned int duration)
{
	qDebug() << "duration changed: " << duration;

	setSliderDuration(duration);	//TODO update entry with new duration
}

void RecorderEdit::setSliderPosition(long pos)
{
	mSliderSeek->setValue(pos);
	mLabelStart->setText(getDurationFormat(pos, false));
}

void RecorderEdit::setSliderDuration(long duration)
{
	mDuration = duration;
	mSliderSeek->setRange(0, mDuration);
	mLabelEnd->setText(getDurationFormat(mDuration, false));
}

void RecorderEdit::close()
{
	if(mAsSheet)
	{
		if(mSheet)
		{
			mSheet->close();
		}
	}
	else
	{
		recorder->mNav->pop();
	}
}

bool RecorderEdit::save(bool exit)
{
	if(mTextTitle->text().trimmed().size() == 0)
	{
		toastUp("Enter the title!");
		mTextTitle->requestFocus();
		return false;
	}

	mEntry->title 	= mTextTitle->text().trimmed();
	mEntry->desc 	= mTextBody->text().trimmed();
	mEntry->flags 	= 0;
	mEntry->status 	= 1;

	bool ret = false;

	if(mEntry->id == 0)
	{
		ret = mEntry->insert();
	}
	else
	{
		ret = mEntry->update();
	}

	if(ret)
	{
		emit editChanged();

		toastDown("Recording saved!");

		if(exit)
		{
			close();
		}
		else
		{
			mEntry->id = -1;
			view();

			setBB10(getUI() == 0);
		}

		return true;
	}
	else
	{
		if(exit)
		{
			alert(recorder->mAppName, "Unable to save recording in database!");
		}
	}

	return false;
}

void RecorderEdit::remove()
{
	if(confirm(recorder->mAppName, "Are you sure you want to delete this recording?"))
	{
		if(mEntry->remove(mEntry->id))
		{
			QFile file(mEntry->path);
			if(file.exists())
			{
				if(!file.remove())
				{
					alert(recorder->mAppName, "Unable to delete recording file!");	//TODO alert if not on secure folder
				}
			}

			emit editChanged();

			close();
		}
		else
		{
			alert(recorder->mAppName, "Unable to delete recording!");
		}
	}
}

void RecorderEdit::startPlaying()
{
	mCounter = 0;

	if(startPlayingAudio())
	{
		mAction = ACTION_PLAYING;

		startPlayingUI();

		emit playingChanged(mAction, mCounter);
	}
}

void RecorderEdit::resumePlaying()
{
	if(resumePlayingAudio())
	{
		mAction = ACTION_PLAYING;

		resumePlayingUI();

		emit playingChanged(mAction, mCounter);
	}
}

void RecorderEdit::pausePlaying()
{
	if(pausePlayingAudio())
	{
		mAction = ACTION_PAUSED;

		pausePlayingUI();

		emit playingChanged(mAction, mCounter);
	}
}

void RecorderEdit::stopPlaying()
{
	stopPlayingAudio();
	mAction = ACTION_STOPPED;

	stopPlayingUI();

	emit playingChanged(mAction, mCounter);
}

void RecorderEdit::startPlayingUI()
{
	mImagePlay->setImage(Image("asset:///images/pause.png"));
	mActionPlay->setImage(Image("asset:///images/pause.png"));
	mActionPlay->setTitle("Pause");
}

void RecorderEdit::pausePlayingUI()
{
	mImagePlay->setImage(Image("asset:///images/play.png"));

	mActionPlay->setImage(Image("asset:///images/play.png"));
	mActionPlay->setTitle("Play");
}

void RecorderEdit::resumePlayingUI()
{
	mImagePlay->setImage(Image("asset:///images/pause.png"));

	mActionPlay->setImage(Image("asset:///images/pause.png"));
	mActionPlay->setTitle("Pause");
}

void RecorderEdit::stopPlayingUI()
{
	mImagePlay->setImage(Image("asset:///images/play.png"));

	mActionPlay->setImage(Image("asset:///images/play.png"));
	mActionPlay->setTitle("Play");
}

bool RecorderEdit::startPlayingAudio()
{
	bool ret = false;

	qDebug() << "startPlayingAudio: " << mEntry->path;

	mPlayer = new MediaPlayer(this);
	mPlayer->setSourceUrl(QUrl("file://" + mEntry->path));
	mPlayer->setStatusInterval(1000);

	QObject::connect(mPlayer, SIGNAL(mediaStateChanged(bb::multimedia::MediaState::Type)), this, SLOT(onPlayerUpdate(bb::multimedia::MediaState::Type)));
	QObject::connect(mPlayer, SIGNAL(durationChanged(unsigned int)), this, SLOT(onDurationChanged(unsigned int)));
	QObject::connect(mPlayer, SIGNAL(positionChanged (unsigned int)), this, SLOT(onPositionChanged(unsigned int)));

	MediaError::Type merr;
	merr = mPlayer->play();

	qDebug() << "duration: " << mPlayer->duration();

	if(merr == MediaError::None)
	{
		if(getShowSpeed())
		{
			double spd = mSliderSpeed->value();

			qDebug() << "startPlayingAudio: speed: " << spd;
			merr = mPlayer->setSpeed(spd);
		}

		ret = true;
	}
	else
	{
		qDebug() << "startPlayingAudio failed";
	}

	return ret;
}

bool RecorderEdit::pausePlayingAudio()
{
	bool ret = false;
	qDebug() << "pausePlayingAudio";

	MediaError::Type merr = mPlayer->pause();
	if(merr == MediaError::None)
	{
		ret = true;
	}
	else
	{
		qDebug() << "pausePlayingAudio failed";
	}

	return ret;
}

bool RecorderEdit::speedPlayingAudio(float speed)
{
	bool ret = false;
	qDebug() << "speedPlayingAudio";

	QString str = QString::number((double)speed, 'f', 1);
	if(str == "1.0") speed = 1.0;

	MediaError::Type merr = mPlayer->setSpeed(speed);
	if(merr == MediaError::None)
	{
		ret = true;
	}
	else
	{
		qDebug() << "speedPlayingAudio failed";
	}

	return ret;
}

bool RecorderEdit::resumePlayingAudio()
{
	bool ret = false;
	qDebug() << "resumePlayingAudio";

	MediaError::Type merr;
	if(getShowSpeed())
	{
		double spd = mSliderSpeed->value();

		qDebug() << "resumePlayingAudio: speed: " << spd;
		merr = mPlayer->setSpeed(spd);
	}
	else
	{
		merr = mPlayer->play();
	}

	if(merr == MediaError::None)
	{
		ret = true;
	}
	else
	{
		qDebug() << "resumePlayingAudio failed";
	}

	return ret;
}

bool RecorderEdit::stopPlayingAudio()
{
	bool ret = false;
	qDebug() << "stopPlayingAudio";

	MediaError::Type merr = mPlayer->stop();
	if(merr == MediaError::None)
	{
		ret = true;
	}
	else
	{
		qDebug() << "stopPlayingAudio failed";
	}

	return ret;
}

