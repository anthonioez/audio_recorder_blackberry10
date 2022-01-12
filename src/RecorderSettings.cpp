#include "Recorder.hpp"
#include "RecorderSettings.hpp"
#include "RecorderSetup.hpp"
#include "RecorderPassword.hpp"
#include "RecorderRecovery.hpp"

#include "settings.hpp"
#include "utils.hpp"

RecorderSettings::RecorderSettings()
{

}

void RecorderSettings::open()
{
	QmlDocument *qml = loadQml("asset:///settings.qml");
	if (qml)
	{
		mPage = qml->createRootObject<Page>();
		if (mPage)
		{
			mPage->setTitleBar(TitleBar::create(TitleBarScrollBehavior::Sticky, TitleBarKind::Default).title("Settings").visibility(getUI() == 0 ? ChromeVisibility::Visible : ChromeVisibility::Hidden));

			mImageTheme		 	= mPage->findChild<ImageView*>("themeImage");

			mContainerTitle		= mPage->findChild<Container*>("titleContainer");
			mContainerNav		= mPage->findChild<Container*>("navContainer");
			mContainerUI		= mPage->findChild<Container*>("uiContainer");

			mImageSave		 	= mPage->findChild<ImageView*>("saveImage");
			mImageCancel	 	= mPage->findChild<ImageView*>("cancelImage");

			mDropFormat			= mPage->findChild<DropDown*>("formatDrop");
			mDropSequence		= mPage->findChild<DropDown*>("sequenceDrop");
			mDropStore			= mPage->findChild<DropDown*>("storeDrop");

			mDropSound			= mPage->findChild<DropDown*>("soundDrop");
			mDropVibrate		= mPage->findChild<DropDown*>("vibrateDrop");
			mDropLed			= mPage->findChild<DropDown*>("ledDrop");

			mDropSort			= mPage->findChild<DropDown*>("sortDrop");
			mDropOrder			= mPage->findChild<DropDown*>("orderDrop");

			mDropPlayer			= mPage->findChild<DropDown*>("playerDrop");
			mDropSpeed			= mPage->findChild<DropDown*>("speedDrop");

			mDropSave			= mPage->findChild<DropDown*>("saveDrop");
			mDropCancel			= mPage->findChild<DropDown*>("cancelDrop");

			mDropUI				= mPage->findChild<DropDown*>("uiDrop");
			mDropThemes			= mPage->findChild<DropDown*>("themesDrop");


			mDropPassword		= mPage->findChild<DropDown*>("passwordDrop");
			mButtonPassword		= mPage->findChild<Button*>("passwordButton");
			mButtonRecovery		= mPage->findChild<Button*>("recoveryButton");

			QObject::connect(mImageSave,	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchSave(bb::cascades::TouchEvent*)));
			QObject::connect(mImageCancel, 	SIGNAL(touch(bb::cascades::TouchEvent*)), 	this, SLOT(onTouchCancel(bb::cascades::TouchEvent*)));

			QObject::connect(mDropUI, 		SIGNAL(selectedIndexChanged(int)), 			this, SLOT(onUIChanged(int)));
			QObject::connect(mDropThemes, 	SIGNAL(selectedIndexChanged(int)), 			this, SLOT(onThemeChanged(int)));
			QObject::connect(mDropPlayer, 	SIGNAL(selectedIndexChanged(int)), 			this, SLOT(onPlayerChanged(int)));
			QObject::connect(mDropPassword,	SIGNAL(selectedIndexChanged(int)), 			this, SLOT(onPasswordedChanged(int)));

			QObject::connect(mButtonPassword, 	SIGNAL(clicked()), 			this, SLOT(onPassword()));
			QObject::connect(mButtonRecovery, 	SIGNAL(clicked()), 			this, SLOT(onRecovery()));

			mContainerUI->setVisible(getRunCount() > 25);	//TODO limit

			if(getPassworded() == 1)
			{
				setStore(0);
			}
			else
			{
				if(getStore() == 0)
				{
					setStore(1);
				}
			}

			mDropFormat->setSelectedIndex(getFormat());
			mDropSequence->setSelectedIndex(getSequence());
			mDropStore->setSelectedIndex(getStore());

			mDropSound->setSelectedIndex(getSound());
			mDropVibrate->setSelectedIndex(getVibrate());
			mDropLed->setSelectedIndex(getLed());

			mDropSort->setSelectedIndex(getSort());
			mDropOrder->setSelectedIndex(getOrder());

			mDropPlayer->setSelectedIndex(getInternalPlayer() ? 0 : 1);
			mDropSpeed->setSelectedIndex(getShowSpeed() ? 1 : 0);
			mDropSave->setSelectedIndex(getSavePrompt() ? 1 : 0);
			mDropCancel->setSelectedIndex(getCancelPrompt() ? 1 : 0);
			mDropUI->setSelectedIndex(getUI());
			mDropThemes->setSelectedIndex(getThemes());

			mDropPassword->setSelectedIndex(getPassworded());

			mPage->addAction(ActionItem::create().title("Save").image(Image("asset:///images/yes.png")).onTriggered(this, SLOT(onSave())), ActionBarPlacement::OnBar);

			onUIChanged(getUI());
			onThemeChanged(getThemes());
			onPasswordedChanged(getPassworded());

			QObject::connect(recorder->mNav, 	SIGNAL(popTransitionEnded(bb::cascades::Page *)), this, SLOT(onPopped(bb::cascades::Page *)));
			recorder->mNav->push(mPage);

			mRetries = 0;
		}
	}
	else
	{
		emit settingsClosed();
	}
}

void RecorderSettings::setBB10(bool bb10)
{
	mPage->titleBar()->setVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mPage->setActionBarVisibility(bb10 ? ChromeVisibility::Visible : ChromeVisibility::Hidden);

	mContainerTitle->setVisible(bb10 ? false : true);

	mContainerNav->setVisible(bb10 ? false : true);

	recorder->mNav->setBackButtonsVisible(bb10 ? true : false);
}

void RecorderSettings::cancel()
{
	recorder->mNav->pop();
}

void RecorderSettings::onSave()
{
	save();
}

void RecorderSettings::save()
{
	QString pass = getPassword();
	if(mDropPassword->selectedIndex() == 1)	//passworded
	{
		if(pass.isEmpty())
		{
			alert(recorder->mAppName, "Please setup your password!");
			mButtonPassword->requestFocus();
			return;
		}
	}
	else
	{
		if(getPassworded() == 1)
		{
			if(confirm(recorder->mAppName, "All your secure recordings will now be accessible!\n\nDo you want to continue?"))
			{
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
			}
			else
			{
				mDropPassword->setSelectedIndex(1);
				return;
			}
		}
	}

	setFormat(mDropFormat->selectedIndex());
	setSequence(mDropSequence->selectedIndex());
	setStore(mDropStore->selectedIndex());

	setSound(mDropSound->selectedIndex());
	setVibrate(mDropVibrate->selectedIndex());
	setLed(mDropLed->selectedIndex());

	setSort(mDropSort->selectedIndex());
	setOrder(mDropOrder->selectedIndex());

	setShowSpeed(mDropSpeed->selectedIndex() == 1 ? true : false);
	setInternalPlayer(mDropPlayer->selectedIndex() == 0 ? true : false);
	setSavePrompt(mDropSave->selectedIndex() == 1 ? true : false);
	setCancelPrompt(mDropCancel->selectedIndex() == 1 ? true : false);
	setUI(mDropUI->selectedIndex());
	setThemes(mDropThemes->selectedIndex());
	setPassworded(mDropPassword->selectedIndex());

	if(getPassworded() == 1)
	{
		setStore(0);
	}
	else
	{
		if(getStore() == 0)
		{
			setStore(1);
		}
	}

	toastDown("Settings saved!");

	cancel();

	emit settingsChanged();
}

void RecorderSettings::onThemeChanged(int theme)
{
	setAppTheme(mImageTheme, theme);
}

void RecorderSettings::onUIChanged(int ui)
{
	setBB10(ui == 0);
}

void RecorderSettings::onPlayerChanged(int player)
{
	mDropSpeed->setEnabled(player == 0 ? true : false);
}

void RecorderSettings::onPasswordedChanged(int index)
{
	QString pass = getPassword();
	mButtonPassword->setText(pass.isEmpty() ? "Setup Password" : "Change Password");

	if(index == 1)	//passworded
	{
		mButtonPassword->setEnabled(true);
		mButtonRecovery->setEnabled(getPassword().isEmpty() ? false : true);

		mDropStore->setSelectedIndex(0);
		mDropStore->at(0)->setEnabled(true);
		mDropStore->setEnabled(false);
	}
	else			//not passworded
	{
		mButtonPassword->setEnabled(false);
		mButtonRecovery->setEnabled(false);

		if(mDropStore->selectedIndex() == 0)
			mDropStore->setSelectedIndex(1);

		mDropStore->at(0)->setEnabled(false);
		mDropStore->setEnabled(true);
	}
}

void RecorderSettings::onPassword()
{
	QString pass = getPassword();
	if(pass.isEmpty())
	{
		RecorderSetup *setup = new RecorderSetup(false);
		QObject::connect(setup,	SIGNAL(passwordChanged()), 	this, SLOT(onPasswordChanged()));
		setup->open();
	}
	else
	{
		RecorderPassword *pass = new RecorderPassword();
		QObject::connect(pass,	SIGNAL(passwordChanged()), 	this, SLOT(onPasswordChanged()));
		pass->open();
	}
}

void RecorderSettings::onRecovery()
{
	RecorderRecovery *recovery = new RecorderRecovery();
	QObject::connect(recovery,	SIGNAL(recoveryChanged()), 	this, SLOT(onRecoveryChanged()));
	recovery->open();
}

void RecorderSettings::onPasswordChanged()
{
	onPasswordedChanged(mDropPassword->selectedIndex());
}

void RecorderSettings::onRecoveryChanged()
{
	onPasswordedChanged(mDropPassword->selectedIndex());
}

void RecorderSettings::onTouchSave(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageSave->setOpacity(0.5);
		mImageSave->setEnabled(false);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageSave->setOpacity(1.5);
		mImageSave->setEnabled(true);

		if(event->isUp())
		{
			save();
		}
	}
}

void RecorderSettings::onTouchCancel(bb::cascades::TouchEvent* event)
{
	if (event->isDown())
	{
		mImageCancel->setOpacity(0.5);
		mImageCancel->setEnabled(false);
	}
	else if (event->isUp() || event->isCancel())
	{
		mImageCancel->setOpacity(1.5);
		mImageCancel->setEnabled(true);

		if(event->isUp())
		{
			cancel();
		}
	}
}

void RecorderSettings::onPopped(bb::cascades::Page *page)
{
	if(page == mPage)
	{
		setBB10(getUI() == 0);

		emit settingsClosed();
	}
}
