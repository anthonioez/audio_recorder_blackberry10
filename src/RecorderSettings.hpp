#ifndef RecorderSettings_HPP_
#define RecorderSettings_HPP_

#include <QObject>
#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Color>

#include <bb/cascades/Container>
#include <bb/cascades/Label>
#include <bb/cascades/Page>
#include <bb/cascades/CheckBox>
#include <bb/cascades/Slider>
#include <bb/cascades/DropDown>
#include <bb/cascades/ImageView>
#include <bb/cascades/TitleBar>
#include <bb/cascades/ChromeVisibility>
#include <bb/cascades/ActionItem>
#include <bb/cascades/ActionBarPlacement>
#include <bb/cascades/Button>


using namespace bb::cascades;

class RecorderSettings : public QObject
{
	Q_OBJECT

	public:
		RecorderSettings();
		virtual ~RecorderSettings() {}
		void open();
		void save();
		void cancel();
		void setBB10(bool);

	private slots:
		void onPopped(bb::cascades::Page *page);
		void onTouchSave(bb::cascades::TouchEvent* touchEvent);
		void onTouchCancel(bb::cascades::TouchEvent* touchEvent);

		void onPlayerChanged(int);
		void onThemeChanged(int);
		void onUIChanged(int);
		void onPasswordedChanged(int);

		void onPassword();
		void onRecovery();
		void onPasswordChanged();
		void onRecoveryChanged();

		void onSave();
	signals:
		void settingsChanged();
		void settingsClosed();

	private:
		Page 				*mPage;
		Container			*mContainerNav;
		Container			*mContainerTitle;
		Container			*mContainerUI;

		ImageView			*mImageTheme;
		ImageView			*mImageSave;
		ImageView			*mImageCancel;

		DropDown			*mDropFormat;
		DropDown			*mDropSequence;
		DropDown			*mDropStore;

		DropDown			*mDropSound;
		DropDown			*mDropVibrate;
		DropDown			*mDropLed;

		DropDown			*mDropSort;
		DropDown			*mDropOrder;

		DropDown			*mDropPlayer;
		DropDown			*mDropSpeed;
		DropDown			*mDropSave;
		DropDown			*mDropCancel;
		DropDown			*mDropUI;
		DropDown			*mDropThemes;
		DropDown			*mDropPassword;
		Button				*mButtonPassword;
		Button				*mButtonRecovery;

		int					mRetries;
};

#endif /* RecorderSettings_HPP_ */
