#ifndef RecorderEdit_HPP_
#define RecorderEdit_HPP_

#include <QObject>
#include <QMutex>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/AbstractTextControl>
#include <bb/cascades/Container>
#include <bb/cascades/Page>
#include <bb/cascades/Label>
#include <bb/cascades/TextField>
#include <bb/cascades/TextArea>
#include <bb/cascades/Label>
#include <bb/cascades/Sheet>
#include <bb/cascades/ImageView>
#include <bb/cascades/Slider>
#include <bb/cascades/ActionItem>
#include <bb/cascades/DeleteActionItem>
#include <bb/cascades/ActionBarPlacement>
#include <bb/cascades/SupportedDisplayOrientation>
#include <bb/cascades/TouchEvent>

#include <bb/multimedia/AudioRecorder>
#include <bb/multimedia/MediaError>
#include <bb/multimedia/MediaPlayer>
#include <bb/multimedia/MediaState>

#include "sql/RecorderFile.hpp"

using namespace bb::cascades;
using namespace bb::multimedia;

class RecorderEdit: public QObject {
Q_OBJECT
public:
	RecorderEdit(bool);
	virtual 	~RecorderEdit() {	}
	void		open(RecorderFile *file, bool edit);
	bool		save(bool exit);
	void		remove();
	void		close();
	void		edit();
	void		view();
	void		action();
	void		play();
	void		share();

	void		popped();

	void		setBB10(bool bb10);

	void startPlaying();
	void pausePlaying();
	void resumePlaying();
	void stopPlaying();

	void startPlayingUI();
	void pausePlayingUI();
	void resumePlayingUI();
	void stopPlayingUI();

	bool startPlayingAudio();
	bool pausePlayingAudio();
	bool speedPlayingAudio(float);
	bool resumePlayingAudio();
	bool stopPlayingAudio();
	void setSliderPosition(long pos);
	void setSliderDuration(long duration);

private slots:
	void onAction();
	void onPlay();
	void onShare();
	void onDelete();

	void onSubmitted(bb::cascades::AbstractTextControl *submitter);
	void onTextChanging(const QString);

	void onPositionChanged(unsigned int duration);
	void onDurationChanged(unsigned int duration);

	void onSpeedSliderChanged(float value);
	void onSpeedSliderImmediateChanged(float value);
	void onPlayerUpdate(bb::multimedia::MediaState::Type state);

	void onTouchAction(bb::cascades::TouchEvent* touchEvent);
	void onTouchDelete(bb::cascades::TouchEvent* touchEvent);
	void onTouchPlay(bb::cascades::TouchEvent* touchEvent);
	void onTouchShare(bb::cascades::TouchEvent* touchEvent);
	void onTouchClose(bb::cascades::TouchEvent* touchEvent);
	void onTouchSlider(bb::cascades::TouchEvent* event);

	void onPopped(bb::cascades::Page *page);
	void onSheetClosed();

	void onSettingsChanged();

signals:
	void editChanged();
	void editClosed();
	void playingChanged(int, long);

private:
	Sheet			*mSheet;
	Page			*mPage;
	ImageView		*mImageTheme;

	Container		*mContainerTitle;
	Container		*mContainerNav;

	Container		*mContainerView;
	Container		*mContainerEdit;
	Container		*mContainerSpeed;

	Label			*mLabelTitle;
	Label			*mLabelBody;
	Label			*mLabelSpeed;

	TextField		*mTextTitle;
	TextArea		*mTextBody;

	Slider			*mSliderSpeed;

	Slider			*mSliderSeek;
	Label			*mLabelStart;
	Label			*mLabelEnd;

	ImageView		*mImageAction;
	ImageView		*mImageDelete;

	ImageView		*mImageShare;
	ImageView		*mImagePlay;
	ImageView		*mImageClose;

	RecorderFile	*mEntry;
	MediaPlayer		*mPlayer;

	bool			mEdit;
	bool			mEditMode;
	bool			mAsSheet;

	long			mCounter;
	long			mDuration;

	int				mAction;
	QMutex			mSeek;

	ActionItem			*mActionAction;
	ActionItem			*mActionPlay;
	ActionItem			*mActionShare;
	DeleteActionItem	*mActionDelete;
};

#endif /* RecorderEdit_HPP_ */
