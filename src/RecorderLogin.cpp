#include "Recorder.hpp"
#include "RecorderLogin.hpp"
#include "settings.hpp"
#include "utils.hpp"

RecorderLogin::RecorderLogin()
{
}

void RecorderLogin::open()
{
	QmlDocument *qml = QmlDocument::create("asset:///login.qml").parent(this);
	if (qml)
	{
		mPage = qml->createRootObject<Page>();
		if (mPage)
		{
			mImageTheme				= mPage->findChild<ImageView*>("themeImage");

			mLabelTitle			= mPage->findChild<Label*>("titleLabel");

			mContainerLogin		= mPage->findChild<Container*>("loginContainer");
			mTextPassword 		= mPage->findChild<TextField*>("passwordText");
			mButtonLogin 		= mPage->findChild<Button*>("loginButton");
			mButtonForgot 		= mPage->findChild<Button*>("forgotButton");


			mContainerRecovery	= mPage->findChild<Container*>("recoveryContainer");
			mLabelQuestion		= mPage->findChild<Label*>("questionLabel");
			mTextAnswer			= mPage->findChild<TextField*>("answerText");
			mButtonRecover		= mPage->findChild<Button*>("recoverButton");
			mButtonCancel 		= mPage->findChild<Button*>("cancelButton");

			QObject::connect(mButtonLogin, SIGNAL(clicked()), this, SLOT(onLogin()));
			QObject::connect(mButtonForgot, SIGNAL(clicked()), this, SLOT(onRecovery()));

			QObject::connect(mButtonRecover, SIGNAL(clicked()), this, SLOT(onRecover()));
			QObject::connect(mButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));


			setAppTheme(mImageTheme, getThemes());

			setLogin();

			setBB10(getUI() == 0);

			mSheet = Sheet::create();
			mSheet->setPeekEnabled(false);
			mSheet->setContent(mPage);
			mSheet->open();

			mLogins = 0;
			mRecoveries = 0;
		}
	}
}

void RecorderLogin::setBB10(bool bb10)
{
	mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title(recorder->mAppName).visibility(ChromeVisibility::Hidden));
	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);
/*
	mPage->titleBar()->setAcceptAction(ActionItem::create().title("Save").onTriggered(this, SLOT(onSave())));
	mPage->titleBar()->setDismissAction(ActionItem::create().title("Cancel").onTriggered(this, SLOT(onCancel())));

	mPage->setActionBarVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);
*/
}

void RecorderLogin::setLogin()
{
	mLabelTitle->setText("Login");
	mTextPassword->setText("");
	mContainerLogin->setVisible(true);
	mContainerRecovery->setVisible(false);
}

void RecorderLogin::setRecovery()
{
	mLabelTitle->setText("Password Recovery!");
	mLabelQuestion->setText(getRecoveryQuestion());
	mTextAnswer->setText("");

	mContainerLogin->setVisible(false);
	mContainerRecovery->setVisible(true);
}

void RecorderLogin::cancel()
{
	if(mSheet)
	{
		mSheet->close();
	}
}

void RecorderLogin::login()
{
	QString pass1 = mTextPassword->text().trimmed();

	if (pass1.isEmpty())
	{
		toastUp("Enter your password!");
		mTextPassword->requestFocus();
		return;
	}

	int total = 5;
	QString pass2 = getPassword();
	if(pass1 == pass2)
	{
		cancel();

		emit loggedin();
	}
	else
	{
		QString msg = "Incorrect password!";
		if(++mLogins >= total)
		{
			alert(recorder->mAppName, "Please restart the app!");

			mContainerLogin->setVisible(false);
			mContainerRecovery->setVisible(false);

//			alert(recorder->mAppName, QString("%1\n%2 will now shutdown!").arg(msg).arg(recorder->mAppName));
//			recorder->mApp->exit(-1);
		}
		else
		{
			alert(QString("%1 %2/%3").arg(recorder->mAppName).arg(mLogins).arg(total), msg);
			mTextPassword->setText("");
			mTextPassword->requestFocus();
		}
	}
}

void RecorderLogin::recover()
{
	QString answer		= mTextAnswer->text().trimmed();

	if (answer.isEmpty())
	{
		toastUp("Enter your security answer!");
		mTextAnswer->requestFocus();
		return;
	}

	int total = 3;
	QString answer2 = getRecoveryAnswer();
	if(answer.toLower() == answer2.toLower())
	{
		setLogin();
//		mTextPassword->setText(getPassword());

		alert(recorder->mAppName, "Your password is '" + getPassword() + "'");
	}
	else
	{
		QString msg = "Incorrect recovery answer!";
		if(++mRecoveries >= total)
		{
			alert(recorder->mAppName, "Please restart the app!");

			mContainerLogin->setVisible(false);
			mContainerRecovery->setVisible(false);

//			alert(recorder->mAppName, QString("%1\n%2 will now shutdown!").arg(msg).arg(recorder->mAppName));
//			recorder->mApp->exit(-1);
		}
		else
		{
			alert(QString("%1 %2/%3").arg(recorder->mAppName).arg(mRecoveries).arg(total), msg);
			mTextAnswer->requestFocus();
		}
	}
}
void RecorderLogin::onLogin()
{
	login();
}

void RecorderLogin::onRecovery()
{
	setRecovery();
}

void RecorderLogin::onRecover()
{
	recover();
}

void RecorderLogin::onCancel()
{
	setLogin();
}

