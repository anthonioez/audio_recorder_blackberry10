#ifndef RecorderLogin_HPP_
#define RecorderLogin_HPP_

#include <QObject>
#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Page>
#include <bb/cascades/Sheet>
#include <bb/cascades/TitleBar>
#include <bb/cascades/Container>
#include <bb/cascades/Label>
#include <bb/cascades/TextField>
#include <bb/cascades/Button>
#include <bb/cascades/ImageView>

using namespace bb::cascades;

class RecorderLogin : public QObject
{
	Q_OBJECT

	public:
		RecorderLogin();
		virtual ~RecorderLogin() {}
		void open();
		void login();
		void cancel();
		void recover();

		void setBB10(bool);

		void setLogin();
		void setRecovery();

	private slots:
		void onLogin();
		void onRecovery();

		void onRecover();
		void onCancel();

	signals:
		void loggedin();

	private:
		Application 	*mApp;
		Page 			*mPage;
		Sheet			*mSheet;

		ImageView		*mImageTheme;
		Label			*mLabelTitle;
		Label			*mLabelQuestion;

		Container		*mContainerLogin;
		Container		*mContainerRecovery;

		TextField 		*mTextPassword;
		TextField 		*mTextAnswer;

		Button			*mButtonLogin;
		Button			*mButtonForgot;

		Button			*mButtonRecover;
		Button			*mButtonCancel;

		int				mLogins;
		int				mRecoveries;
};

#endif /* RecorderLogin_HPP_ */
