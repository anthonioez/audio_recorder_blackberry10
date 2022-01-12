#include "Recorder.hpp"
#include "RecorderPassword.hpp"
#include "settings.hpp"
#include "utils.hpp"

RecorderPassword::RecorderPassword()
{

}

void RecorderPassword::open()
{
    QmlDocument *qml = loadQml(QString("asset:///settings_password.qml"));
   	if(qml)
   	{
		mPage = qml->createRootObject<Page>();
		if (mPage)
		{
			mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title("Change Password").visibility(getUI() == 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden));

			mImageTheme			= mPage->findChild<ImageView*>("themeImage");

			mContainerTitle		= mPage->findChild<Container*>("titleContainer");
			mContainerNav		= mPage->findChild<Container*>("navContainer");

			mTextPassword 		= mPage->findChild<TextField*>("passwordText");
			mTextPasswordNew 	= mPage->findChild<TextField*>("passwordNewText");
			mTextPasswordNew2 	= mPage->findChild<TextField*>("passwordNew2Text");

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

void RecorderPassword::setBB10(bool bb10)
{
	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mPage->titleBar()->setAcceptAction(ActionItem::create().title("Save").onTriggered(this, SLOT(onSave())));
	mPage->titleBar()->setDismissAction(ActionItem::create().title("Cancel").onTriggered(this, SLOT(onCancel())));

	mPage->setActionBarVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);

	mContainerNav->setVisible(bb10 ? false : true);

	recorder->mNav->setBackButtonsVisible(bb10 ? true : false);
}

void RecorderPassword::save()
{
	QString pass 		= mTextPassword->text().trimmed();
	QString passNew 	= mTextPasswordNew->text().trimmed();
	QString passNew2 	= mTextPasswordNew2->text().trimmed();

	if (pass.size() < 4)
	{
		toastUp("Enter your current password, minimum of 4 characters!");
		mTextPassword->requestFocus();
		return;
	}

	if (passNew.size() < 4)
	{
		toastUp("Enter your new password, minimum of 4 characters!");
		mTextPasswordNew->requestFocus();
		return;
	}

	if (passNew2.size() < 4)
	{
		toastUp("Confirm your new password, minimum of 4 characters!");
		mTextPasswordNew2->requestFocus();
		return;
	}

	if(passNew != passNew2)
	{
		toastUp("The passwords are not the same!");
		mTextPasswordNew2->requestFocus();
		return;
	}

	QString password = getPassword();
	if(password != pass)
	{
		alert(recorder->mAppName, "Incorrect password!");

		if(++mRetries >= 3)
		{
			cancel();
		}
		else
		{
			mTextPassword->requestFocus();
			mTextPassword->setText("");
			mTextPasswordNew->setText("");
			mTextPasswordNew2->setText("");
		}
		return;
	}

	setPassword(passNew);

	toast("Password changed!");

	emit passwordChanged();

	cancel();
}

void RecorderPassword::cancel()
{
	if(mSheet)
	{
		mSheet->close();
	}
}

void RecorderPassword::onTouchSave(bb::cascades::TouchEvent* event)
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

void RecorderPassword::onTouchCancel(bb::cascades::TouchEvent* event)
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

void RecorderPassword::onSave()
{
	save();
}

void RecorderPassword::onCancel()
{
	cancel();
}

