#ifndef RecorderFrame_HPP_
#define RecorderFrame_HPP_

#include <QObject>
#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Page>
#include <bb/cascades/SceneCover>
#include <bb/cascades/Container>
#include <bb/cascades/Label>
#include <bb/cascades/ImageView>

using namespace bb::cascades;

class RecorderFrame: public SceneCover
{
	Q_OBJECT

	public:
		RecorderFrame();
		virtual ~RecorderFrame() {}
		void 	start();
		void 	updateCover(int, long, bool);

	private slots:
		void	thumbnail();
		void 	onRecordingChanged(int state, long pos);
		void 	onPlayingChanged(int state, long pos);

	signals:

	private:
		Container	*mContainerBg;
		Label		*mLabelTitle;
		Label		*mLabelStatus;
		ImageView	*mImageStatus;
};

#endif /* RecorderFrame_HPP_ */
