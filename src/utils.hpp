#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <QString>
#include <QTime>
#include <QDateTime>
#include <QObject>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Label>
#include <bb/cascades/Container>
#include <bb/cascades/ImageView>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/GroupDataModel>

#include <bb/system/SystemToast>
#include <bb/system/SystemUiPosition>

#include <bb/system/SystemDialog>
#include <bb/system/SystemUiButton>
#include <bb/system/SystemUiResult>
#include <bb/system/SystemUiModality>
#include <bb/system/SystemUiInputMode>
#include <bb/system/SystemPrompt>

#include <bb/platform/Notification>
#include <bb/platform/NotificationDialog>

using namespace bb::cascades;
using namespace bb::system;
using namespace bb::platform;


#define KB				(1024)
#define MB				(KB * KB)
#define GB				(KB * KB * KB)
#define TB				(KB * KB * KB * KB)

QmlDocument* 	loadQml(QString title);

void 			notify(const QString &title, const QString &msg);
void			notifyDialog(const QString &title, const QString &msg);

bool 			confirm(const QString &title, const QString &msg);
void			toast(const QString &msg);
void			toastUp(const QString &msg);
void			toastDown(const QString &msg);
void			alert(const QString &title, const QString &msg);

void			setAppTheme(ImageView *image, int theme);

bool 			listCompare(const QVariant &left, const QVariant &right);

QString 		getBodyForListing(const QString &);
long			getAutoSaveInterval(int index);

QString			getTimeFormat(qlonglong value);
QString			getDurationFormat(qlonglong value, bool);
QString			getByteFormat(qlonglong value, int prec);

void			updateListDataModel(QListDataModel<QVariant> *ldm, QVariantList &tempList);
void			updateGroupDataModel(GroupDataModel *gdm, QVariantList &tempList);

QString passwordPrompt();

#endif /* UTILS_HPP_ */

