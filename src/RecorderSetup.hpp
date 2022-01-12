#ifndef RecorderSetup_HPP_
#define RecorderSetup_HPP_

#include <QObject>
#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Page>
#include <bb/cascades/ImageView>
#include <bb/cascades/Container>
#include <bb/cascades/Label>
#include <bb/cascades/TitleBar>
#include <bb/cascades/ActionItem>

#include <bb/cascades/TouchEvent>
#include <bb/cascades/Container>

#include <bb/cascades/Label>
#include <bb/cascades/TextField>
#include <bb/cascades/Sheet>

using namespace bb::cascades;

class RecorderSetup : public QObject
{
	Q_OBJECT

	public:
		RecorderSetup(bool);
		virtual ~RecorderSetup() {}
		void open();
		void cancel();
		void save();
		void close();

		void setBB10(bool);

	private slots:
		void onTouchSave(bb::cascades::TouchEvent* event);
		void onTouchCancel(bb::cascades::TouchEvent* event);
		void onSave();
		void onCancel();
	signals:
		void passwordChanged();
		void passwordCanceled();

	private:
		Application 	*mApp;
		Sheet			*mSheet;
		Page			*mPage;

		ImageView		*mImageTheme;

		Container		*mContainerTitle;
		Container		*mContainerNav;

		TextField 		*mTextPassword;
		TextField 		*mTextConfirmPassword;
		TextField 		*mTextQuestion;
		TextField 		*mTextAnswer;

		ImageView 		*mImageSave;
		ImageView 		*mImageCancel;

		bool			mMain;
};

#endif /* RecorderSetup_HPP_ */
