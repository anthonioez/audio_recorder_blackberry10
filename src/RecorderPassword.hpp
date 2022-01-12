#ifndef RecorderPassword_HPP_
#define RecorderPassword_HPP_

#include <QObject>
#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/ActionItem>
#include <bb/cascades/Page>
#include <bb/cascades/Sheet>
#include <bb/cascades/TextField>
#include <bb/cascades/Button>
#include <bb/cascades/ImageView>

using namespace bb::cascades;

class RecorderPassword : public QObject
{
	Q_OBJECT

	public:
		RecorderPassword();
		virtual ~RecorderPassword() {}
		void 	open();
		void 	cancel();
		void 	save();

		void 	setBB10(bool);

	private slots:
		void onTouchSave(bb::cascades::TouchEvent* event);
		void onTouchCancel(bb::cascades::TouchEvent* event);
		void onSave();
		void onCancel();
	signals:
		void passwordChanged();

	private:
		Page			*mPage;
		Sheet			*mSheet;

		Container		*mContainerTitle;
		Container		*mContainerNav;

		ImageView		*mImageTheme;

		TextField 		*mTextPassword;
		TextField 		*mTextPasswordNew;
		TextField 		*mTextPasswordNew2;

		ImageView		*mImageSave;
		ImageView		*mImageCancel;

		int				mRetries;
};

#endif /* RecorderPassword_HPP_ */
