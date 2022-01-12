#include "Recorder.hpp"
#include "RecorderMain.hpp"
#include "RecorderEdit.hpp"
#include "RecorderSettings.hpp"
#include "RecorderFileList.hpp"
#include "RecorderFolderList.hpp"
#include "settings.hpp"
#include "utils.hpp"

RecorderMain::RecorderMain()
{
	mAction = ACTION_READY;
	mRecorder = NULL;
	mTimer = NULL;
	mLed = NULL;
	mEntry = NULL;
	mNavigation = true;

	mCount = 0;
	mCounter = 0;
	mInterval = 250;
	mFilePath 	= QDir::homePath() + "/" + "temp.wav";
}

void RecorderMain::open()
{
	QmlDocument *qml = loadQml("asset:///main.qml");
	if (qml != NULL)
	{
		mPage = qml->createRootObject<Page>();
		if (mPage)
		{
			mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title(recorder->mAppName).visibility(getUI() == 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden));

			mActionTitle = (getSequence() == 0 ? "Stop" : "Pause");

			mImageTheme		 = mPage->findChild<ImageView*>("themeImage");

			mContainerTitle	= mPage->findChild<Container*>("titleContainer");
			mContainerEdit 	= mPage->findChild<Container*>("editContainer");
			mContainerNav 	= mPage->findChild<Container*>("navContainer");

			mLabelTime = mPage->findChild<Label*>("timeLabel");
			mLabelSize = mPage->findChild<Label*>("sizeLabel");
			mLabelStatus = mPage->findChild<Label*>("statusLabel");
			mLabelTips = mPage->findChild<Label*>("tipsLabel");

			mImageAction = mPage->findChild<ImageView*>("actionImage");
			mImageList = mPage->findChild<ImageView*>("listImage");
			mImageFolder = mPage->findChild<ImageView*>("folderImage");
//			mImagePlay = mPage->findChild<ImageView*>("playImage");
			mImageStop = mPage->findChild<ImageView*>("stopImage");
			mImageCancel = mPage->findChild<ImageView*>("cancelImage");
			mImageSettings = mPage->findChild<ImageView*>("settingsImage");

			QObject::connect(mImageAction, SIGNAL(touch(bb::cascades::TouchEvent*)), this, SLOT(onTouchAction(bb::cascades::TouchEvent*)));
			QObject::connect(mImageList, SIGNAL(touch(bb::cascades::TouchEvent*)), this, SLOT(onTouchList(bb::cascades::TouchEvent*)));
			QObject::connect(mImageFolder, SIGNAL(touch(bb::cascades::TouchEvent*)), this, SLOT(onTouchFolder(bb::cascades::TouchEvent*)));
			QObject::connect(mImageStop, SIGNAL(touch(bb::cascades::TouchEvent*)), this, SLOT(onTouchStop(bb::cascades::TouchEvent*)));
//			QObject::connect(mImagePlay, SIGNAL(touch(bb::cascades::TouchEvent*)), this, SLOT(onTouchPlay(bb::cascades::TouchEvent*)));
			QObject::connect(mImageCancel, SIGNAL(touch(bb::cascades::TouchEvent*)), this, SLOT(onTouchCancel(bb::cascades::TouchEvent*)));
			QObject::connect(mImageSettings, SIGNAL(touch(bb::cascades::TouchEvent*)), this, SLOT(onTouchSettings(bb::cascades::TouchEvent*)));

			QObject::connect(recorder, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));

			if(getRunCount() > 1000)	//TODO
			{
				mLabelTips->setVisible(false);
			}

			onSettingsChanged();

			stopRecordingUI();

//			mImagePlay->setVisible(false);
			mLabelTips->setText("touch the circle to record");

			//connect recordings only after here
			recorder->mNav->push(mPage);
		}
	}
}

void RecorderMain::setNavigation(bool state)
{
	mNavigation = state;

	if(getUI() == 0)
	{
		mPage->removeAllActions();
		if(state)
		{
			mPage->addAction(ActionItem::create().title("Folders").image(Image("asset:///images/folder.png")).onTriggered(this, SLOT(onFolder())), ActionBarPlacement::OnBar);
			mPage->addAction(ActionItem::create().title("Recordings").image(Image("asset:///images/open.png")).onTriggered(this, SLOT(onList())), ActionBarPlacement::OnBar);
		}
		else
		{
			mPage->addAction(ActionItem::create().title("Cancel").image(Image("asset:///images/no.png")).onTriggered(this, SLOT(onCancel())), ActionBarPlacement::OnBar);
			mPage->addAction(ActionItem::create().title(mActionTitle).image(mImageStop->image()).onTriggered(this, SLOT(onStop())), ActionBarPlacement::OnBar);
		}

		mPage->addAction(ActionItem::create().title("BBM Invite"	).image(Image("asset:///images/bbm.png")).onTriggered(recorder, SLOT(onInvite())), ActionBarPlacement::InOverflow);
		mPage->addAction(ActionItem::create().title("Rate this app"	).image(Image("asset:///images/rate.png")).onTriggered(recorder, SLOT(onRate())), ActionBarPlacement::InOverflow);
		mPage->addAction(ActionItem::create().title("More apps"		).image(Image("asset:///images/more.png")).onTriggered(recorder, SLOT(onMore())), ActionBarPlacement::InOverflow);

		mContainerNav->setVisible(false);
		mContainerEdit->setVisible(false);
	}
	else
	{
		mContainerNav->setVisible(mNavigation);
		mContainerEdit->setVisible(!mNavigation);
	}
}

void RecorderMain::setBB10(bool bb10)
{
	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);
	mPage->setActionBarVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);

	if(bb10)
	{
		mContainerEdit->setVisible(false);
		mContainerNav->setVisible(false);
	}
	else
	{
		setNavigation(mNavigation);
	}

	recorder->mNav->setBackButtonsVisible(bb10 ? true : false);
}

void RecorderMain::onSettingsChanged()
{
	setAppTheme(mImageTheme, getThemes());
	setBB10(getUI() == 0);

	setNavigation(mNavigation);

	mImageStop->setImage(getSequence() == 0 ? Image("asset:///images/stop.png") : Image("asset:///images/pause.png"));

}

void RecorderMain::onEditChanged()
{
//	toastDown("Recording saved!");
//	mImagePlay->setVisible(true);
}

void RecorderMain::onTimerUpdate()
{
	qDebug() << "onTimerUpdate" << mCounter;

	if(mAction == ACTION_RECORDING)
	{
		mCounter += mInterval;
		mLabelTime->setText(getDurationFormat(mCounter, false));

		int c = mCounter / 1000;

		mLabelStatus->setOpacity((c % 2) ? 1.0 : 0);

		if(++mCount >= (1000 / mInterval))
		{
			mCount = 0;

			mFileInfo.refresh();
			if(mFileInfo.exists())
			{
				mLabelSize->setText(getByteFormat(mFileInfo.size(), 2));
			}
			else
			{
				mLabelSize->setText("");
			}
		}

		emit recordingChanged(mAction, mCounter);
	}
	else
	{
		mLabelStatus->setOpacity(1.0);
	}

}

void RecorderMain::onStop()
{
	stop();
}

void RecorderMain::onCancel()
{
	cancel();
}


void RecorderMain::onTouchAction(bb::cascades::TouchEvent* event)
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

		if (event->isUp())
		{
			action();
		}
	}
}

void RecorderMain::onTouchList(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageList->setOpacity(0.5);
		mImageList->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageList->setOpacity(1.0);
		mImageList->setEnabled(true);

		if (event->isUp())
		{
			list();
		}
	}
}

void RecorderMain::onTouchFolder(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageFolder->setOpacity(0.5);
		mImageFolder->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageFolder->setOpacity(1.0);
		mImageFolder->setEnabled(true);

		if (event->isUp())
		{
			folder();
		}
	}
}

void RecorderMain::onTouchStop(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageStop->setOpacity(0.5);
		mImageStop->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageStop->setOpacity(1.0);
		mImageStop->setEnabled(true);

		if (event->isUp())
		{
			stop();
		}
	}
}
/*
void RecorderMain::onTouchPlay(bb::cascades::TouchEvent* event)
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

		if (event->isUp())
		{
			play();
		}
	}
}
*/
void RecorderMain::onTouchCancel(bb::cascades::TouchEvent* event)
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

		if (event->isUp())
		{
			cancel();
		}
	}
}

void RecorderMain::onTouchSettings(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageSettings->setOpacity(0.5);
		mImageSettings->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageSettings->setOpacity(1.0);
		mImageSettings->setEnabled(true);

		if (event->isUp())
		{
			settings();
		}
	}
}

void RecorderMain::onList()
{
	list();
}

void RecorderMain::onFolder()
{
	folder();
}

void RecorderMain::action()
{
	if (mAction == ACTION_READY)
	{
		startRecording();
	}
	else if (mAction == ACTION_RECORDING)
	{
		if(getSequence() == 0)
			pauseRecording();
		else
			stopRecording();
	}
	else if (mAction == ACTION_PAUSED)
	{
		resumeRecording();
	}
}

void RecorderMain::list()
{
	RecorderFileList *list = new RecorderFileList();
	list->open(0);
}

void RecorderMain::folder()
{
	RecorderFolderList *fld = new RecorderFolderList();
	fld->open();
}

void RecorderMain::settings()
{
	recorder->settings();
}

void RecorderMain::stop()
{
	if(getSequence() == 0)
	{
		stopRecording();
	}
	else
	{
		if(mAction == ACTION_PAUSED)
			stopRecording();
		else
			pauseRecording();
	}
}

void RecorderMain::cancel()
{
	if(getCancelPrompt())
	{
		if(confirm(recorder->mAppName, "Are you sure you want to cancel this recording?"))
		{
			cancelRecording();
		}
	}
	else
	{
		cancelRecording();

		toastDown("Recording canceled!");
	}
}

void RecorderMain::play()
{
	if(mEntry != NULL)
	{
		RecorderEdit *edit = new RecorderEdit(false);
		QObject::connect(edit, SIGNAL(editClosed()), this, SLOT(onEditChanged()));	//TODO
		edit->open(mEntry, false);
	}
}

void RecorderMain::startRecording()
{
	mCount = 0;
	mCounter = 0;
	mFileName = QDateTime::currentDateTime().toString("MMM d hh mm ss ap");
	mFileName = "recording_" + mFileName.replace(" ", "_").toLower();

	int format = getFormat();
	if(format == FORMAT_AMR)
		mFileExt = "amr";
	else if(format == FORMAT_M4A)
		mFileExt = "m4a";
	else
		mFileExt = "wav";

	int store = getStore();
	if(store == STORE_SDCARD)
	{
		SdCardInfo *info = new SdCardInfo(this);
		if(info->state() != SdCardState::Mounted)
		{
			store = STORE_DEVICE;
			toastDown("Media card not available, using device instead!");
		}
	}

	QString path;
	if(store == STORE_DEVICE)
		path = recorder->mAppDevPath + "/voice/" + recorder->mAppFolder;
	else if(store == STORE_SDCARD)
		path = recorder->mAppMemPath + "/voice/" + recorder->mAppFolder;
	else
		path = recorder->mAppPrvPath + "/" + recorder->mAppFolder;

	mFilePath = path +  + "/" + mFileName + "." + mFileExt;

	QDir dir = QDir(path);
	dir.mkpath(path);
	if(!dir.exists())
	{
		alert(recorder->mAppName, QString("Unable to create recording folder!\n%1").arg(store == STORE_SDCARD ? "Please check your media card!" : "Please check the settings!"));
		return;
	}

	//TODO
/*
	$ ls /dev/snd
	bluetoothc       defaultc         headphonep       masterc          pcmC0D0c         pcmC0D4c         pcmC0D6p         pcmPreferredc    ttyp
	bluetoothp       defaultp         headsetc         masterp          pcmC0D0p         pcmC0D4p         pcmC0D7c         pcmPreferredp    voice_abec
	btscoc           echoc            headsetp         mixerC0D0        pcmC0D1p         pcmC0D5c         pcmC0D8c         speakerp         voice_abep
	btscop           handsetc         lineoutp         modem_mcbspc     pcmC0D2p         pcmC0D5p         pcmC0D8p         tonesp           voicec
	controlC0        handsetp         loggerc          modem_mcbspp     pcmC0D3p         pcmC0D6c         pcmC0D9c         ttyc             voicep

	https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
	aac: 8 KBps, 11.025 KBps, 12 KBps, 16 KBps, 22.05 KBps, 32 KBps, 44.1 KBps and 48 KBps
	amr: 4.75 KBps, 5.15 KBps, 5.9 KBps, 6.7 KBps, 7.4 KBps, 7.95 KBps, 10.2 KBps, and 12.2 KBps
	m4a: 32KHz, 44.1KHz, and 48KHz
	wav: 8 kHz, 16 kHz, 22.05 kHz, 32 kHz, 44.1 kHz, and 48 kHz with 8-bit and 16-bit depths
*/

	mFileInfo = QFileInfo(mFilePath);

	if(startRecordingAudio())
	{
		mAction = ACTION_RECORDING;

		startRecordingUI();

		startTimer();

		startLed();
		startSound();
		startVibrate();

		emit recordingChanged(mAction, mCounter);
	}
	else
	{
		alert(recorder->mAppName, "An error occurred!\nUnable to start recording!");

		stopRecordingAudio();
	}
}

void RecorderMain::pauseRecording()
{
	qDebug() << "pauseRecording";

	if(pauseRecordingAudio())
	{
		qDebug() << "pauseRecording paused";

		mAction = ACTION_PAUSED;

		stopTimer();

		pauseRecordingUI();

		stopLed();

		emit recordingChanged(mAction, mCounter);
	}
}

void RecorderMain::resumeRecording()
{
	qDebug() << "resumeRecording";

	if(resumeRecordingAudio())
	{
		qDebug() << "resumeRecording resumed";

		mAction = ACTION_RECORDING;

		resumeRecordingUI();

		startTimer();

		startLed();

		emit recordingChanged(ACTION_RESUMED, mCounter);
	}
}

void RecorderMain::stopRecording()
{
	qDebug() << "stopRecording";

	mAction = ACTION_READY;

	stopTimer();

	stopRecordingUI();
	stopRecordingAudio();

	stopLed();
	stopSound();
	stopVibrate();

	emit recordingChanged(ACTION_STOPPED, mCounter);

	QFileInfo fileinfo(mFilePath);
	if(!fileinfo.exists())
	{
		alert(recorder->mAppName, "Sorry, nothing was recorded!");
		return;
	}

	RecorderFolder *folder = new RecorderFolder(recorder->mSda);

	long currentFolder = getCurrentFolder();
	if(currentFolder > 0)
	{
		if(!folder->get(currentFolder))
		{
			currentFolder = 0;
		}
	}

	mEntry = new RecorderFile(recorder->mSda);
	mEntry->id 		= 0;
	mEntry->folder 	= currentFolder;
	mEntry->title = "Recording " + QString::number(getRecordCount());
	mEntry->desc = "";
	mEntry->path = mFilePath;
	mEntry->size = mFileInfo.size();
	mEntry->duration = mCounter;
	mEntry->stamp = QDateTime::currentDateTime().toTime_t();

	setRecordCount(getRecordCount() + 1);

	if(getSavePrompt())
	{
		RecorderEdit *edit = new RecorderEdit(true);
		QObject::connect(edit, SIGNAL(editChanged()), this, SLOT(onEditChanged()));
		edit->open(mEntry, true);
	}
	else
	{
		if(mEntry->insert())
		{
			if(currentFolder > 0)
			{
				toastDown("Recording saved in '" + folder->title + "' folder!");
			}
			else
			{
				toastDown("Recording saved!");
			}
		}
		else
		{
			alert(recorder->mAppName, "Unable to create entry in database!");

			if(getStore() == STORE_PRIVATE)
			{
				QFile file(mFilePath);
				if(file.exists())
				{
					file.remove();
				}
			}
		}
	}
}

void RecorderMain::cancelRecording()
{
	qDebug() << "cancelRecording";

	mAction = ACTION_READY;

	stopTimer();

	stopRecordingUI();
	stopRecordingAudio();

	stopLed();
	stopSound();
	stopVibrate();

	QFile file(mFilePath);
	if(file.exists())
	{
		file.remove();
	}

//	mImagePlay->setVisible(false);

	emit recordingChanged(ACTION_CANCELED, mCounter);
}

void RecorderMain::startRecordingUI()
{
	mImageAction->setImage(getSequence() == 0 ? Image("asset:///images/pause_big.png") : Image("asset:///images/stop_big.png"));
	mLabelTips->setText(getSequence() == 0 ? "touch again to pause" : "touch again to stop");


	mLabelStatus->setText("Recording");
	mLabelStatus->setOpacity(1.0);

	mActionTitle = (getSequence() == 0 ? "Stop" : "Pause");

	mImageStop->setImage(getSequence() == 0 ? Image("asset:///images/stop.png") : Image("asset:///images/pause.png"));
	mImageStop->setVisible(true);

	setNavigation(false);
}

void RecorderMain::resumeRecordingUI()
{
	mLabelTips->setText("touch again to pause");

	mImageAction->setImage(Image(getSequence() == 0 ? "asset:///images/pause_big.png" : "asset:///images/stop_big.png"));
	mLabelStatus->setText("Recording");
	mLabelStatus->setOpacity(1.0);

	mActionTitle = getSequence() == 0 ? "Stop" : "Pause";

	mImageStop->setImage(getSequence() == 0 ? Image("asset:///images/stop.png") : Image("asset:///images/pause.png"));
	mImageStop->setVisible(true);

	setNavigation(false);
}

void RecorderMain::pauseRecordingUI()
{
	mLabelTips->setText("touch again to resume");

	mImageAction->setImage(Image("asset:///images/record_big.png"));

	mLabelStatus->setText("Paused");
	mLabelStatus->setOpacity(1.0);

	mActionTitle = (getSequence() == 0 ? (mAction == ACTION_PAUSED ? "Stop" : "Pause") : "Stop");

	mImageStop->setImage(Image(getSequence() == 0 ? (mAction == ACTION_PAUSED ? "asset:///images/stop.png" : "asset:///images/pause.png") : "asset:///images/stop.png"));
	mImageStop->setVisible(true);

	setNavigation(false);
}

void RecorderMain::stopRecordingUI()
{
	mLabelTips->setText("touch the circle to record");

	mImageAction->setImage(Image("asset:///images/record_big.png"));
	mLabelStatus->setText("");
	mLabelTime->setText("");
	mLabelSize->setText("");
	mImageStop->setVisible(false);

	setNavigation(true);
}

bool RecorderMain::startRecordingAudio()
{
	bool ret = false;

	qDebug() << "startRecordingAudio: "  << mFilePath;

	mRecorder = new AudioRecorder(this);
	mRecorder->setOutputUrl(QUrl("file://" + mFilePath));

	MediaError::Type merr = mRecorder->record();
	if(merr == MediaError::None)
	{
		ret = true;
	}
	else
	{
		qDebug() << "startRecordingAudio failed";
	}
	return ret;
}

bool RecorderMain::pauseRecordingAudio()
{
	bool ret = false;
	qDebug() << "pauseRecordingAudio";
	if(mRecorder != NULL)
	{
		MediaError::Type merr = mRecorder->pause();
		if(merr == MediaError::None)
		{
			ret = true;
		}
		else
		{
			qDebug() << "pauseRecordingAudio failed";
		}
	}
	else
	{
		qDebug() << "pauseRecordingAudio recorder null";
	}

	return ret;
}

bool RecorderMain::resumeRecordingAudio()
{
	bool ret = false;
	qDebug() << "resumeRecordingAudio";
	if(mRecorder != NULL)
	{
		MediaError::Type merr = mRecorder->record();
		if(merr == MediaError::None)
		{
			ret = true;
		}
		else
		{
			qDebug() << "resumeRecordingAudio failed";
		}
	}
	else
	{
		qDebug() << "resumeRecordingAudio recorder null";
	}
	return ret;
}

bool RecorderMain::stopRecordingAudio()
{
	bool ret = false;
	qDebug() << "stopRecordingAudio";

	if(mRecorder != NULL)
	{
		MediaError::Type merr = mRecorder->reset();
		if(merr == MediaError::None)
		{
			ret = true;
		}
		else
		{
			qDebug() << "stopRecordingAudio failed";
		}
	}
	else
	{
		qDebug() << "stopRecordingAudio recorder null";
	}

	return ret;
}

void RecorderMain::startTimer()
{
	mTimer = new QTimer();
	QObject::connect(mTimer, SIGNAL(timeout()), this, SLOT(onTimerUpdate()));
	mTimer->start(mInterval);
}

void RecorderMain::stopTimer()
{
	if(mTimer != NULL)
	{
		mTimer->stop();
		mTimer = NULL;
	}
}

void RecorderMain::startSound()
{
	if(getSound() == 1 || getSound() == 3)
	{
		SystemSound::play(SystemSound::RecordingStartEvent);
	}
}

void RecorderMain::stopSound()
{
	if(getSound() == 2 || getSound() == 3)
	{
		SystemSound::play(SystemSound::RecordingStopEvent);
	}
}

void RecorderMain::startVibrate()
{
	if(getVibrate() == 1 || getVibrate() == 3)
	{
		VibrationController *vibrator = new VibrationController();
		vibrator->start(100, 500);
		vibrator->stop();
	}
}

void RecorderMain::stopVibrate()
{
	if(getVibrate() == 2 || getVibrate() == 3)
	{
		VibrationController *vibrator = new VibrationController();
		vibrator->start(100, 500);
		vibrator->stop();
	}
}

void RecorderMain::startLed()
{
	int led = getLed();
	if(led > 0)
	{
		mLed = new Led();
		mLed->setColor(getLedColor(led));
		mLed->flash(-1);
	}
}

void RecorderMain::stopLed()
{
	if(mLed)
	{
		mLed->cancel();
		mLed = NULL;
	}
}

LedColor::Type RecorderMain::getLedColor(int led)
{
	switch(led)
	{
		case 0: return LedColor::None;
		case 1: return LedColor::Red;
		case 2: return LedColor::Green;
		case 3: return LedColor::Blue;
		case 4: return LedColor::Yellow;
		case 5: return LedColor::Cyan;
		case 6: return LedColor::Magenta;
		case 7: return LedColor::White;
		default: return LedColor::None;
	}
}

int RecorderMain::getFrequency(int sampling)
{
	switch(sampling)
	{
		case SAMPLING_8000: return 8000;
		case SAMPLING_11000: return 11000;
		case SAMPLING_16000: return 16000;
		case SAMPLING_22500: return 22500;
		case SAMPLING_32000: return 32000;
		case SAMPLING_44100: return 44100;
		case SAMPLING_48000: return 48000;
		default: return 8000;
	}
}

int RecorderMain::getDepth(int channel)
{
	if(channel == CHANNEL_16_MONO || channel == CHANNEL_16_STEREO)
		return 16;
	else
		return 32;
}

int RecorderMain::getChannels(int channel)
{
	if(channel == CHANNEL_16_STEREO || channel == CHANNEL_32_STEREO)
		return 2;
	else
		return 1;
}
