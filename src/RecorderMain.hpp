#ifndef RecorderMain_HPP_
#define RecorderMain_HPP_

#include <QObject>
#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>

#include <QFile>
#include <QFileInfo>

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/strm.h>
#include <sys/stat.h>
#include <mm/renderer.h>
#include <mm/renderer/events.h>
#include <bps/audiomixer.h>
#include <bps/mmrenderer.h>
#include <audio/audio_manager_routing.h>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Container>
#include <bb/cascades/Page>
#include <bb/cascades/Label>
#include <bb/cascades/ImageView>
#include <bb/cascades/ActionItem>

#include <bb/cascades/TitleBar>
#include <bb/cascades/TitleBarScrollBehavior>

#include <bb/device/Led>
#include <bb/device/LedColor>
#include <bb/device/SdCardInfo>
#include <bb/device/SdCardState>
#include <bb/device/VibrationController>

#include <bb/multimedia/SystemSound>
#include <bb/multimedia/AudioRecorder>
#include <bb/multimedia/MediaError>
#include <bb/multimedia/MediaPlayer>
#include <bb/multimedia/MediaState>

#include "sql/RecorderFile.hpp"

using namespace bb::cascades;
using namespace bb::device;
using namespace bb::multimedia;

#define FORMAT_AMR			0
#define FORMAT_M4A			1
#define FORMAT_WAV			2

#define CHANNEL_16_MONO		0
#define CHANNEL_16_STEREO	1
#define CHANNEL_32_MONO		2
#define CHANNEL_32_STEREO	3

#define SAMPLING_8000		0
#define SAMPLING_11000		1
#define SAMPLING_16000		2
#define SAMPLING_22500		3
#define SAMPLING_32000		4
#define SAMPLING_44100		5
#define SAMPLING_48000		6

#define SEQUENCE_PAUSE		0
#define SEQUENCE_STOP		1

#define STORE_PRIVATE		0
#define STORE_DEVICE		1
#define STORE_SDCARD		2

class RecorderMain: public QObject
{
	Q_OBJECT

	public:
		RecorderMain();
		virtual ~RecorderMain() {}
		void open();

		void action();
		void list();
		void folder();
		void settings();
		void stop();
		void cancel();
		void play();

		void startRecording();
		void pauseRecording();
		void resumeRecording();
		void stopRecording();

		void cancelRecording();

		void startRecordingUI();
		void pauseRecordingUI();
		void resumeRecordingUI();
		void stopRecordingUI();

		bool startRecordingAudio();
		bool pauseRecordingAudio();
		bool resumeRecordingAudio();
		bool stopRecordingAudio();

		void startTimer();
		void stopTimer();

		void startSound();
		void stopSound();

		void startVibrate();
		void stopVibrate();

		void startLed();
		void stopLed();

		LedColor::Type getLedColor(int led);
		int 	getFrequency(int sampling);
		int 	getDepth(int channel);
		int 	getChannels(int channel);
		void	setBB10(bool bb10);

		void	setNavigation(bool state);
	private slots:
		void onList();
		void onFolder();
		void onStop();
		void onCancel();
		void onTouchAction	(bb::cascades::TouchEvent *);
		void onTouchList	(bb::cascades::TouchEvent *);
		void onTouchFolder	(bb::cascades::TouchEvent *);
//		void onTouchPlay	(bb::cascades::TouchEvent *);
		void onTouchStop	(bb::cascades::TouchEvent *);
		void onTouchCancel	(bb::cascades::TouchEvent *);
		void onTouchSettings(bb::cascades::TouchEvent *);
		void onTimerUpdate	();
		void onSettingsChanged();
		void onEditChanged();
	signals:
		void recordingChanged(int, long);

	private:
		Page				*mPage;
		ImageView			*mImageTheme;
		Container			*mContainerEdit;
		Container			*mContainerNav;
		Container			*mContainerTitle;

		Label				*mLabelTime;
		Label				*mLabelSize;
		Label				*mLabelStatus;
		Label				*mLabelTips;

		ImageView			*mImageAction;
		ImageView			*mImageList;
		ImageView			*mImageFolder;
//		ImageView			*mImagePlay;
		ImageView			*mImageStop;
		ImageView			*mImageCancel;
		ImageView			*mImageSettings;

		int					mAction;
		long				mInterval;
		long				mCounter;
		long				mCount;
		QString				mFileName;
		QString				mFileExt;
		QString				mFilePath;

		Led					*mLed;
		QTimer				*mTimer;
		AudioRecorder 		*mRecorder;
		RecorderFile 		*mEntry;

		bool				mNavigation;
		QString				mActionTitle;

		QFileInfo			mFileInfo;
};

#endif /* RecorderMain_HPP_ */
