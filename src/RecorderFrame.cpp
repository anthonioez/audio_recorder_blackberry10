#include "Recorder.hpp"
#include "RecorderFrame.hpp"
#include "settings.hpp"
#include "utils.hpp"

RecorderFrame::RecorderFrame() : SceneCover(this)
{
}

void RecorderFrame::start()
{
	QmlDocument *qml = QmlDocument::create("asset:///cover.qml").parent(this);
   	if(qml)
   	{
   		mContainerBg = qml->createRootObject<Container>();
		if(mContainerBg)
		{
			mImageStatus	= mContainerBg->findChild<ImageView*>("statusImage");
			mLabelStatus 	= mContainerBg->findChild<Label*>("statusLabel");
			mLabelTitle		= mContainerBg->findChild<Label*>("titleLabel");

			mLabelStatus->setText("");
			mLabelTitle->setText("");

			setContent(mContainerBg);

			connect(Application::instance(), SIGNAL(thumbnail()), this, SLOT(thumbnail()));
			Application::instance()->setCover(this);
		}
   	}
}

void RecorderFrame::thumbnail()
{
	updateCover(ACTION_READY, 0, false);
}

void RecorderFrame::onRecordingChanged(int state, long pos)
{
	updateCover(state, pos, true);
}
void RecorderFrame::onPlayingChanged(int state, long pos)
{
	updateCover(state, pos, false);
}

void RecorderFrame::updateCover(int state, long pos, bool recording)
{
	float scale = 0.75f;
	switch(state)
	{
		case ACTION_PLAYING:
			mImageStatus->setScale(scale);
			mImageStatus->setImage(Image("asset:///images/play_big.png"));

			mLabelStatus->setText(getDurationFormat(pos, false));
			mLabelTitle->setText("Playing");
			break;
		case ACTION_RECORDING:
			mImageStatus->setScale(scale);
			mImageStatus->setImage(Image(getSequence() == 0 ? "asset:///images/pause_big.png" : "asset:///images/stop_big.png"));

			mLabelStatus->setText(getDurationFormat(pos, false));
			mLabelTitle->setText("Recording");
			break;
		case ACTION_PAUSED:
			mImageStatus->setScale(scale);
			mImageStatus->setImage(Image(recording ? "asset:///images/record_big.png" : "asset:///images/pause_big.png"));

			mLabelTitle->setText("Paused");
			break;
		case ACTION_RESUMED:
			mImageStatus->setScale(scale);
			mImageStatus->setImage(Image(recording ? "asset:///images/pause_big.png" : "asset:///images/play_big.png"));

			mLabelTitle->setText(recording ? "Recording" : "Playing");
			break;
		case ACTION_READY:
		case ACTION_CANCELED:
		case ACTION_STOPPED:
		default:
			mImageStatus->setImage(Image("asset:///images/icon_big.png"));
			mImageStatus->setScale(1.0);

			mLabelStatus->setText("");
			mLabelTitle->setText("");
			break;
	}
}

