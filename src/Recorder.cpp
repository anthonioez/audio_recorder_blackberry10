#include "Recorder.hpp"
#include "RecorderMain.hpp"
#include "RecorderSetup.hpp"
#include "RecorderLogin.hpp"
#include "RecorderFrame.hpp"
#include "RecorderSettings.hpp"

#include "pc/PromptControl.hpp"

#include "settings.hpp"
#include "utils.hpp"

Recorder 		*recorder;

Recorder::Recorder(bb::cascades::Application *app) : QObject(app)
{
	mApp 			= app;
	mAppName 		= "Recorder+";
	mAppPrvPath 	= QDir::homePath();
	mAppDevPath 	= "/accounts/1000/shared";
	mAppMemPath 	= "/accounts/1000/removable/sdcard";
	mAppFolder  	= "recorder+";

	mInvoke 		= new InvokeManager(this);

	// Listen to incoming invocation requests
	connect(mInvoke, SIGNAL(invoked(const bb::system::InvokeRequest&)), this, SLOT(onHandleInvoke(const bb::system::InvokeRequest&)));
	connect(mInvoke, SIGNAL(cardResizeRequested(const bb::system::CardResizeMessage&)), this, SLOT(onResized(const bb::system::CardResizeMessage&)));
	connect(mInvoke, SIGNAL(cardPooled(const bb::system::CardDoneMessage&)), this, SLOT(onPooled(const bb::system::CardDoneMessage&)));

	// Initialize properties with default values
	switch (mInvoke->startupMode())
	{
		case ApplicationStartupMode::LaunchApplication:
			mStart = true;
			initApp();
			break;
		case ApplicationStartupMode::InvokeApplication:
			break;
		case ApplicationStartupMode::InvokeCard:
			mStart = false;
			initCard();
			break;
		case ApplicationStartupMode::InvokeViewer:
			break;
	}
}

void Recorder::initCard()
{
	mNav = NavigationPane::create();
	mNav->setBackButtonsVisible(false);
	mNav->setPeekEnabled(true);
	mApp->setScene(mNav);
}

void Recorder::startCard()
{
	initDB();

	QString str;
	str = "\nSOURCE: " 	+ QString::fromLatin1("%1 (%2)").arg(mRequest.source().installId()).arg(mRequest.source().groupId());
	str += "\nTARGET: " + mRequest.target();
	str += "\nACTION: " + mRequest.action();
	str += "\nMIME: " 	+ mRequest.mimeType();
	str += "\nURI: " 	+ mRequest.uri().toString();
	str += "\nDATA: " 	+ QString::fromUtf8(mRequest.data());

//	qDebug() << "invocation: " << str;

	QString uri = mRequest.uri().toString();
	QString data = QString::fromUtf8(mRequest.data());
	QString mime = mRequest.mimeType();
/*
	if(uri.trimmed().isEmpty())
	{
		if(getShare() == SHARE_TITLE)
			addRecorder(data, QString(""));
		else
			addRecorder(QString(""), data);
	}
	else
	{
		if(data.trimmed().isEmpty())
		{
			if(getShare() == SHARE_TITLE)
				addRecorder(uri, QString(""));
			else
				addRecorder(QString(""), uri);
		}
		else
		{
			addRecorder(uri, data);
		}
	}
*/
}

void Recorder::initApp()
{
	mNav = NavigationPane::create();
	mNav->setBackButtonsVisible(false);
	mNav->setPeekEnabled(true);
	mApp->setScene(mNav);
	mApp->setAutoExit(false);

	initDB();

	initBBM();

	initMenu();

	QObject::connect(mApp, 		SIGNAL(fullscreen()), 	this, SLOT(onFullscreen()));
	QObject::connect(mApp, 		SIGNAL(thumbnail()), 	this, SLOT(onMinimize()));
	QObject::connect(mApp, 		SIGNAL(manualExit()), 	this, SLOT(onExit()));
}

void Recorder::startApp()
{
	mFrame = new RecorderFrame();
	QObject::connect(this, SIGNAL(recordingChanged(int, long)), mFrame, SLOT(onRecordingChanged(int, long)));
	QObject::connect(this, SIGNAL(playingChanged(int, long)), mFrame, SLOT(onPlayingChanged(int, long)));
	mFrame->start();

	if(getRunCount() == 0)
	{
		RecorderSetup *setup = new RecorderSetup(true);
		QObject::connect(setup, SIGNAL(passwordCanceled()), this, SLOT(onLogin()));
		QObject::connect(setup, SIGNAL(passwordChanged()), this, SLOT(onStart()));
		setup->open();
	}
	else
	{
		onStart();
	}
}

void Recorder::onStart()
{
	QString pass = getPassword();
	if(getPassworded() == 1 && !pass.isEmpty())
	{
		RecorderLogin *login = new RecorderLogin();
		QObject::connect(login, SIGNAL(loggedin()), this, SLOT(onLogin()));
		login->open();
	}
	else
	{
		onLogin();
	}
}

void Recorder::onLogin()
{
	mApp->setScene(mNav);

	mMain = new RecorderMain();
	QObject::connect(mMain, SIGNAL(recordingChanged(int, long)), this, SLOT(onRecordingChanged(int, long)));
	mMain->open();

	if(getRunCount() == 0)
	{
		alert(recorder->mAppName, "For comments, suggestions and bug reports, \nkindly send an email to miciniti@gmail.com");
	}

	if(getRunCount() == 0 || (getRunCount() % 10) == 0)
	{
		if(getRunCount() < 50)
		{
			toastDown("For settings, swipe down from the top of this screen.");
		}
	}

	setRunCount(getRunCount() + 1);

	PromptControl *rc = new PromptControl(recorder->mAppName, "appworld://content/36615893", 25);
	rc->run();
}

void Recorder::initBBM()
{
	const QUuid uuid(QLatin1String("7325c13a-ff8b-412a-8713-ca28b8127c93"));

	mBBMreg = new BBMReg(uuid, mApp);
	mBBMinvite = new BBMInvite(&mBBMreg->context());
}

bool Recorder::initDB()
{
    mAppDbPath = QDir::homePath() + "/" + "recorderplus.db";

	mSda = new SqlDataAccess(mAppDbPath);

	QFile file(mAppDbPath);

	if (!file.exists() || file.size() == 0)
	{
		if(file.open(QIODevice::ReadWrite))
		{
			XmlDataAccess xda;
			QString path = QDir::currentPath() + "/app/native/assets/xml/sql.xml";

			QVariant root = xda.load(path, "/sql");

			if(!xda.hasError())
			{
				QVariantMap map = root.value<QVariantMap>();

				QVariantList statements = map["statement"].value<QVariantList>();

				int count = 0;
				for(int i = 0; i < statements.size(); i++)
				{
					QString statement = statements.at(i).toString().trimmed();
					if(statement.length() == 0) continue;
					QVariant result = mSda->execute(statement);
					if(!mSda->hasError())
					{
						count++;
					}
				}
			}

			file.close();
			return true;
		}
		else
		{
			qDebug() << "error: " << file.errorString() << file.error();
		}
	}
	return false;
}

void Recorder::quitDB()
{
	QSqlDatabase conn = mSda->connection();
	if(conn.isOpen())
	{
		conn.commit();
		conn.close();
	}
}

void Recorder::initMenu()
{
	Menu *menu = new Menu;

	mMenuSettings 	= SettingsActionItem::create().title("Settings"	).image( Image("asset:///images/settings.png") 	).onTriggered(this, SLOT(onSettings()));
	menu->setSettingsAction(mMenuSettings);

	menu->addAction(ActionItem::create().title("BBM Invite"		).image( Image("asset:///images/bbm.png") 		).onTriggered(this, SLOT(onInvite())));
	menu->addAction(ActionItem::create().title("Rate this app"	).image( Image("asset:///images/rate.png") 		).onTriggered(this, SLOT(onRate())));
	menu->addAction(ActionItem::create().title("More Apps"		).image( Image("asset:///images/more.png") 		).onTriggered(this, SLOT(onMore())));
	mApp->setMenu(menu);

}

void Recorder::addRecorder(const QString &title, const QString &content)
{
	mCardTitle = title;
	mCardContent = content;
/*
	RecorderFolderSelector *card = new RecorderFolderSelector();
	QObject::connect(card, SIGNAL(folderSelected(long)), this, SLOT(onFolderSelected(long)));
	QObject::connect(card, SIGNAL(folderCanceled()), this, SLOT(onFolderCanceled()));
	card->open(0);
	*/
}

void Recorder::cardDone(const QString& status, const QString& msg)
{
	qDebug() << "cardDone: " << status << msg;

	if(msg.size() > 0)
	{
		alert(mAppName, msg);
	}

	CardDoneMessage message;
	message.setData(msg);
	message.setDataType("text/plain");
	message.setReason(status + ":" + msg);
	mInvoke->sendCardDone(message);
}

void Recorder::setPageTitle(Page *page)
{
	if(page) page->setTitleBar(TitleBar::create().visibility(ChromeVisibility::Visible).title(mAppName));
}

void Recorder::minimize()
{
	mApp->minimize();
}

void Recorder::onHandleInvoke(const bb::system::InvokeRequest& request)
{
	mRequest = request;

	QTimer::singleShot(50, this, SLOT(startCard()));
}

void Recorder::onPooled(const bb::system::CardDoneMessage& msg)
{
	qDebug() << "onPooled:" << "reason: " << msg.reason() << "data: " << msg.data();
}

void Recorder::onResized(const bb::system::CardResizeMessage&)
{
	qDebug() << "onResized";
}

void Recorder::onLockStateChanged(bb::platform::DeviceLockState::Type newState)
{
    if (newState == bb::platform::DeviceLockState::Unlocked)
    {
    }
    else if (newState == bb::platform::DeviceLockState::ScreenLocked)
    {
    }
    else if (newState == bb::platform::DeviceLockState::PasswordLocked)
    {
    }
    else
    {
    }
}

void Recorder::onRecordingChanged(int state, long pos)
{
	switch(state)
	{
		case ACTION_READY:
		case ACTION_CANCELED:
		case ACTION_STOPPED:
			mMenuSettings->setEnabled(true);
			break;
		case ACTION_RECORDING:
		case ACTION_PAUSED:
		case ACTION_RESUMED:
			mMenuSettings->setEnabled(false);
			break;
	}

	emit recordingChanged(state, pos);
}

void Recorder::onPlayingChanged(int state, long pos)
{
	switch(state)
	{
		case ACTION_READY:
		case ACTION_CANCELED:
		case ACTION_STOPPED:
//			mMenuSettings->setEnabled(true);
			break;
		case ACTION_PAUSED:
		case ACTION_RESUMED:
		case ACTION_PLAYING:
//			mMenuSettings->setEnabled(false);
			break;
	}

	emit playingChanged(state, pos);
}

void Recorder::settings()
{
	mMenuSettings->setEnabled(false);

	RecorderSettings *settings = new RecorderSettings();

	QObject::connect(settings, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));
	QObject::connect(settings, SIGNAL(settingsClosed()), this, SLOT(onSettingsClosed()));
	settings->open();

}

void Recorder::onSettings()
{
	settings();
}

void Recorder::onSettingsChanged()
{
	emit settingsChanged();
}

void Recorder::onSettingsClosed()
{
	mMenuSettings->setEnabled(true);
}

void Recorder::onFullscreen()
{
	mFullscreen = true;

	if(mStart)
	{
	}
}

void Recorder::onMinimize()
{
	mFullscreen = false;
}

void Recorder::onInvite()
{
	if(mBBMinvite)
	{
		if(mBBMinvite->sendInvite())
		{
			return;
		}
	}

	initBBM();
}

void Recorder::onMore()
{
	InvokeRequest cardRequest;
	cardRequest.setAction("bb.action.OPEN");
	cardRequest.setTarget("sys.appworld");
	cardRequest.setUri("appworld://vendor/37262");
	InvokeManager* invokeManager = new InvokeManager();
	invokeManager->invoke(cardRequest);
}

void Recorder::onRate()
{
	InvokeRequest cardRequest;
	cardRequest.setAction("bb.action.OPEN");
	cardRequest.setTarget("sys.appworld");
	cardRequest.setUri("appworld://content/36615893");
	InvokeManager* invokeManager = new InvokeManager();
	invokeManager->invoke(cardRequest);
}

void Recorder::onExit()
{
	mApp->exit();
}


void Recorder::onShareArmed()
{
	Invocation *invocation = qobject_cast<Invocation *>(sender());
	invocation->trigger("bb.action.SHARE");
}

void Recorder::share(const QString &title, const QString &desc, const QString &path)
{
	QString data = "";
	data += title;
	data += "\n\n";
	data += desc;

	qDebug() << "invoke share: " << path;

	QVariantMap map;
	map["title"] = title + "\n" + desc;

	InvokeQuery *query = InvokeQuery::create();
	query->setInvokeActionId("bb.action.SHARE");
	query->setUri(path);
	query->setData(data.toUtf8());
	query->setMetadata(map);
	//		query->setMimeType("text/plain");

	Invocation *invocation = Invocation::create(query).parent(this);
	QObject::connect(invocation, SIGNAL(armed()), this, SLOT(onShareArmed()));
	QObject::connect(invocation, SIGNAL(finished()), invocation, SLOT(deleteLater()));
}
