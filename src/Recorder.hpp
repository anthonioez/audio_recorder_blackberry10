#ifndef Recorder_HPP_
#define Recorder_HPP_

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QUrl>
#include <QFile>
#include <QIODevice>
#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>

#include <bb/platform/HomeScreen>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Application>
#include <bb/cascades/Page>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Tab>
#include <bb/cascades/Page>
#include <bb/cascades/Menu>
#include <bb/cascades/ActionItem>
#include <bb/cascades/HelpActionItem>
#include <bb/cascades/SettingsActionItem>
#include <bb/cascades/TitleBar>
#include <bb/cascades/ChromeVisibility>
#include <bb/cascades/OrientationSupport>
#include <bb/cascades/SupportedDisplayOrientation>
#include <bb/cascades/InvokeQuery>
#include <bb/cascades/Invocation>


#include <bb/platform/HomeScreen>


#include <bb/data/XmlDataAccess>
#include <bb/data/SqlDataAccess>
#include <bb/data/JsonDataAccess>


#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeTarget>
#include <bb/system/CardDoneMessage>
#include <bb/system/CardResizeMessage>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>

#include "RecorderFrame.hpp"
#include "RecorderMain.hpp"

#include "sql/RecorderFolder.hpp"

#include "bbm/BBMReg.hpp"
#include "bbm/BBMInvite.hpp"

#define ACTION_READY		0
#define ACTION_RECORDING	1
#define ACTION_PAUSED		2
#define ACTION_RESUMED		3
#define ACTION_CANCELED		4
#define ACTION_STOPPED		5
#define ACTION_PLAYING		6

using namespace bb::cascades;
using namespace bb::platform;
using namespace bb::data;
using namespace bb::system;


class Recorder : public QObject
{
	Q_OBJECT
	public:
		Recorder(bb::cascades::Application *app);
		virtual 	~Recorder(){}

		void		initBBM(void);
		bool		initDB(void);
	    void 		quitDB(void);

	    void		initMenu();
	    void 		initApp(void);
	    void 		initCard(void);

	    void 		startApp(void);
		void		setPageTitle(bb::cascades::Page* page);

		void 		minimize();
	    void 		settings();

	    void 		cardDone(const QString& status, const QString& msg);
	    void 		addRecorder(const QString &title, const QString &content);
	    void 		share(const QString &title, const QString &desc, const QString &path);

	private slots:
		void onLogin();
		void onStart();
		void onRecordingChanged(int, long);
		void onPlayingChanged(int, long);
		void onSettings();
		void onSettingsClosed();
		void onSettingsChanged();
		void onLockStateChanged(bb::platform::DeviceLockState::Type newState);

		void onFullscreen();
		void onMinimize();

		void onInvite();
		void onRate();
		void onMore();
		void onExit();
		void onShareArmed();

		void startCard();
		void onHandleInvoke(const bb::system::InvokeRequest& request);
		void onPooled(const bb::system::CardDoneMessage& doneMessage);
		void onResized(const bb::system::CardResizeMessage&);

	signals:
		void settingsChanged();
		void recordingChanged(int, long);
		void playingChanged(int, long);

	public:
		Application 		*mApp;
		SqlDataAccess 		*mSda;
		NavigationPane		*mNav;

		SettingsActionItem 	*mMenuSettings;

	    QString				mAppName;
		QString				mAppDbPath;
		QString				mAppPrvPath;
		QString				mAppDevPath;
		QString				mAppMemPath;
		QString				mAppFolder;

		QTimer 				*mTimer;
		BBMReg 				*mBBMreg;
		BBMInvite			*mBBMinvite;

		InvokeManager		*mInvoke;
		InvokeRequest		mRequest;

		RecorderMain		*mMain;
		RecorderFrame 		*mFrame;

		bool				mFullscreen;
		bool				mStart;
		QString				mCardTitle;
		QString				mCardContent;
};

extern Recorder 		*recorder;

#endif /* Recorder_HPP_ */
