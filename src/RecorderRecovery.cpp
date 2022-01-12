#include "Recorder.hpp"
#include "RecorderRecovery.hpp"
#include "settings.hpp"
#include "utils.hpp"

RecorderRecovery::RecorderRecovery()
{

}

void RecorderRecovery::open()
{
    QmlDocument *qml = loadQml(QString("asset:///settings_recovery.qml"));
   	if(qml)
   	{
		mPage = qml->createRootObject<Page>();
		if (mPage)
		{
			mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title("Password Recovery").visibility(getUI() == 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden));

			mImageTheme			= mPage->findChild<ImageView*>("themeImage");

			mContainerTitle		= mPage->findChild<Container*>("titleContainer");
			mContainerNav		= mPage->findChild<Container*>("navContainer");

			mTextQuestion		= mPage->findChild<TextField*>("questionText");
			mTextAnswer			= mPage->findChild<TextField*>("answerText");

			mImageSave			= mPage->findChild<ImageView*>("saveImage");
			mImageCancel		= mPage->findChild<ImageView*>("cancelImage");

			QObject::connect(mImageSave,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchSave(bb::cascades::TouchEvent*)));
			QObject::connect(mImageCancel,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchCancel(bb::cascades::TouchEvent*)));

			setAppTheme(mImageTheme, getThemes());

			setBB10(getUI() == 0);

			mRetries = 0;
			mSheet = Sheet::create();
			mSheet->setContent(mPage);
			mSheet->open();
		}
   	}
}

void RecorderRecovery::setBB10(bool bb10)
{
	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mPage->titleBar()->setAcceptAction(ActionItem::create().title("Save").onTriggered(this, SLOT(onSave())));
	mPage->titleBar()->setDismissAction(ActionItem::create().title("Cancel").onTriggered(this, SLOT(onCancel())));

	mPage->setActionBarVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);

	mContainerNav->setVisible(bb10 ? false : true);

	recorder->mNav->setBackButtonsVisible(bb10 ? true : false);
}

void RecorderRecovery::save()
{
	QString question 	= mTextQuestion->text().trimmed();
	QString answer 		= mTextAnswer->text().trimmed();

	if (question.size() < 4)
	{
		toastUp("Enter your recovery question, minimum of 4 characters!");
		mTextQuestion->requestFocus();
		return;
	}

	if (answer.size() < 4)
	{
		toastUp("Enter your recovery answer, minimum of 4 characters!");
		mTextAnswer->requestFocus();
		return;
	}

	QString password = passwordPrompt();
	if(password.isEmpty() || password.isEmpty() || password != getPassword())
	{
		alert(recorder->mAppName, "Incorrect password!");
		if(++mRetries >= 3)
		{
			cancel();
		}
		return;
	}

	setRecoveryQuestion(question);
	setRecoveryAnswer(answer);

	toast("Recovery info changed!");
	emit recoveryChanged();

	cancel();
}

void RecorderRecovery::cancel()
{
	if(mSheet)
	{
		mSheet->close();
	}
}

void RecorderRecovery::onTouchSave(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageSave->setOpacity(0.5);
		mImageSave->setEnabled(true);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageSave->setOpacity(1.0);
		mImageSave->setEnabled(true);

		if(event->isUp())
		{
			save();
		}
	}
}

void RecorderRecovery::onTouchCancel(bb::cascades::TouchEvent* event)
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

		if(event->isUp())
		{
			cancel();
		}
	}
}

void RecorderRecovery::onSave()
{
	save();
}

void RecorderRecovery::onCancel()
{
	cancel();
}



