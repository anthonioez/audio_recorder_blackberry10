#include "Recorder.hpp"
#include "RecorderSetup.hpp"
#include "settings.hpp"
#include "utils.hpp"

RecorderSetup::RecorderSetup(bool main)
{
	mMain = main;
}

void RecorderSetup::open()
{
	QmlDocument *qml = QmlDocument::create("asset:///settings_setup.qml").parent(this);
	if (qml)
	{
		mPage = qml->createRootObject<Page>();
		if (mPage)
		{
			mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title("Setup Password").visibility(getUI() == 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden));

			mImageTheme				= mPage->findChild<ImageView*>("themeImage");

			mContainerTitle			= mPage->findChild<Container*>("titleContainer");
			mContainerNav			= mPage->findChild<Container*>("navContainer");

			mTextPassword 			= mPage->findChild<TextField*>("passwordText");
			mTextConfirmPassword 	= mPage->findChild<TextField*>("passwordConfirmText");

			mTextQuestion			= mPage->findChild<TextField*>("recoveryQuestionText");
			mTextAnswer 			= mPage->findChild<TextField*>("recoveryAnswerText");

			mImageSave				= mPage->findChild<ImageView*>("saveImage");
			mImageCancel			= mPage->findChild<ImageView*>("cancelImage");

			QObject::connect(mImageSave,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchSave(bb::cascades::TouchEvent*)));
			QObject::connect(mImageCancel,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchCancel(bb::cascades::TouchEvent*)));

			setAppTheme(mImageTheme, getThemes());

			setBB10(getUI() == 0);

			mSheet = Sheet::create();
			mSheet->setContent(mPage);
			mSheet->open();
		}
	}
}

void RecorderSetup::setBB10(bool bb10)
{
	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mPage->titleBar()->setAcceptAction(ActionItem::create().title("Save").onTriggered(this, SLOT(onSave())));
	mPage->titleBar()->setDismissAction(ActionItem::create().title(mMain ? "Skip" : "Cancel").onTriggered(this, SLOT(onCancel())));

	mPage->setActionBarVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);

	mContainerNav->setVisible(bb10 ? false : true);

	recorder->mNav->setBackButtonsVisible(bb10 ? true : false);
}

void RecorderSetup::cancel()
{
	close();

	emit passwordCanceled();

}


void RecorderSetup::close()
{
	if(mSheet)
	{
		mSheet->close();
	}
}

void RecorderSetup::save()
{
	QString pass1 		= mTextPassword->text().trimmed();
	QString pass2 		= mTextConfirmPassword->text().trimmed();

	QString question 	= mTextQuestion->text().trimmed();
	QString answer 		= mTextAnswer->text().trimmed();

	if (pass1.isEmpty())
	{
		toastUp("Enter your password!");
		mTextPassword->requestFocus();
		return;
	}

	if (pass2.isEmpty())
	{
		toastUp("Confirm your password!");
		mTextConfirmPassword->requestFocus();
		return;
	}

	if (pass1 != pass2)
	{
		toastUp("The passwords are not the same!");
		return;
	}

	if (question.isEmpty())
	{
		toastUp("Enter your recovery question!");
		mTextQuestion->requestFocus();
		return;
	}

	if (answer.isEmpty())
	{
		toastUp("Enter your recovery answer!");
		mTextAnswer->requestFocus();
		return;
	}

	setPassword(pass1);

	setRecoveryQuestion(question);
	setRecoveryAnswer(answer);

	if(mMain)
	{
		setPassworded(1);
	}

	toastDown("Password setup completed!");

	close();

	emit passwordChanged();

}

void RecorderSetup::onTouchSave(bb::cascades::TouchEvent* event)
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

void RecorderSetup::onTouchCancel(bb::cascades::TouchEvent* event)
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

void RecorderSetup::onSave()
{
	save();
}

void RecorderSetup::onCancel()
{
	cancel();
}
