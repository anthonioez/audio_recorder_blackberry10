#include "settings.hpp"
#include "utils.hpp"

QmlDocument * loadQml(QString title)
{
	QmlDocument *qml = QmlDocument::create(title);

	if (qml && !qml->hasErrors())
	{
	   	return qml;
	}
	return NULL;
}

bool confirm(const QString &title, const QString &msg)
{
	SystemDialog *dialog = new SystemDialog("Yes", "No");
    dialog->setTitle(title);
    dialog->setBody(msg);

    if(dialog->exec() == SystemUiResult::ConfirmButtonSelection)
    	return true;
    else
    	return false;
}

void notify(const QString &title, const QString &msg)
{
	Notification* notif = new Notification();
	notif->setTitle(title);
	notif->setBody(msg);
	notif->notify();
}

void notifyDialog(const QString &title, const QString &msg)
{
	NotificationDialog* dialog = new NotificationDialog();
    dialog->setTitle(title);
    dialog->setBody(msg);
    dialog->appendButton(new SystemUiButton("OK"));
	dialog->show();
}

void alert(const QString &title, const QString &msg)
{
	SystemDialog *dialog = new SystemDialog("OK");
    dialog->setTitle(title);
    dialog->setBody(msg);
	dialog->exec();
}

void toast(const QString &msg)
{
	SystemToast *toast = new SystemToast();
	toast->setPosition(SystemUiPosition::TopCenter);
	toast->setBody(msg);
	toast->show();
}

void toastUp(const QString &msg)
{
	SystemToast *toast = new SystemToast();
	toast->setPosition(SystemUiPosition::TopCenter);
	toast->setBody(msg);
	toast->show();
}

void toastDown(const QString &msg)
{
	SystemToast *toast = new SystemToast();
	toast->setPosition(SystemUiPosition::BottomCenter);
	toast->setBody(msg);
	toast->show();
}

void setAppTheme(ImageView *image, int theme)
{
	if(!image) return;

	QString asset;
	if(theme == 0)
		asset = "asset:///images/black.png";
	else if(theme == 1)
		asset =  "asset:///images/red.png";
	else if(theme == 2)
		asset = "asset:///images/green.png";
	else if(theme == 3)
		asset = "asset:///images/blue.png";
	else if(theme == 4)
		asset = "asset:///images/magenta.png";
	else if(theme == 5)
		asset = "asset:///images/yellow.png";
	else if(theme == 6)
		asset = "asset:///images/cyan.png";
	else
		return;

	image->setImage(Image(QUrl(asset)));
}


bool listCompare(const QVariant &left, const QVariant &right)
{
	QVariantMap lmap = left.toMap();
	QVariantMap rmap = right.toMap();

	long ltime = lmap["stamp"].toLongLong();
	long rtime = rmap["stamp"].toLongLong();

//	qDebug() << "compare: " << QDateTime::fromTime_t(ltime).toString(" ddd dd MMM, yyyy hh:mm A") << QDateTime::fromTime_t(rtime).toString(" ddd dd MMM, yyyy hh:mm A");
	return (ltime < rtime);
}

QString getBodyForListing(const QString &in)
{
	QString tmp = in.trimmed();

	QStringList list = tmp.split("\n");
	if(list.size() > 0)
		return list.at(0);
	else
		return tmp.left(100);
}

long getAutoSaveInterval(int index)
{
	switch(index)
	{
//		case 0: return 10 * 1000;
		case 1: return 1 * 60 * 1000;
		case 2: return 2 * 60 * 1000;
		case 3: return 5 * 60 * 1000;
		case 4: return 10 * 60 * 1000;
		default: return 0;
	}
}


QString	getDurationFormat(qlonglong value, bool hour)
{
	QTime time = QTime(0, 0, 0, 0).addMSecs(value);

	if(time.hour() == 0 && !hour)
		return time.toString("mm:ss");
	else
		return time.toString("hh:mm:ss");
}

QString	getTimeFormat(qlonglong value)
{
	QDateTime datetime = QDateTime::fromTime_t(value);
	return datetime.toString("d MMM yyyy, hh:mm ap");
}

void updateGroupDataModel(GroupDataModel *mDataModel, QVariantList &tempList)
{
	mDataModel->clear();
	mDataModel->insertList(tempList);
}

void updateListDataModel(QListDataModel<QVariant> *mDataModel, QVariantList &tempList)
{
	int curSize = mDataModel->size();
	int newSize = tempList.size();

	if(curSize > newSize)
	{
		int diff = curSize - newSize;
		for(int i = 0; i < diff; i++)
		{
			mDataModel->removeAt(0);
		}
	}

	curSize = mDataModel->size();

	for(int i = 0; i < newSize; i++)
	{
		QVariantMap entry = tempList.at(i).value<QVariantMap>();

		if(i >= curSize)
			mDataModel->append(entry);
		else
			mDataModel->replace(i, entry);
	}
}

QString	getByteFormat(qlonglong value, int prec)
{
	QString str = QString::number(value);

	double fvalue = (float)value;
	qlonglong v = (qlonglong)abs(fvalue);
	qlonglong tb = GB;
	tb *= KB;

	/*if(v >= tb)
	{
		fvalue = fvalue / (float)(tb);
		str = QString::number(fvalue, 'f', prec) + "TB";
	}
	else */
	if(v >= GB)
	{
		fvalue = fvalue / (float)(GB);
		str = QString::number(fvalue, 'f', prec) + "GB";
	}
	else if(v >= MB)
	{
		fvalue = fvalue / (float)(MB);
		str = QString::number(fvalue, 'f', prec) + "MB";
	}
	else if(v >= KB)
	{
		fvalue = fvalue / (float)(KB);
		str = QString::number(fvalue, 'f', prec) + "KB";
	}
	else
	{
		str = QString::number(fvalue, 'f', prec) + "B";
	}
	return str;
}

QString passwordPrompt()
{
	SystemPrompt *prompt = new SystemPrompt();
    prompt->setTitle("Password");
    prompt->setDismissAutomatically(true);
    prompt->inputField()->setDefaultText("");
    prompt->inputField()->setEmptyText("Enter your current password!");
    prompt->inputField()->setInputMode(SystemUiInputMode::Password);

	if(prompt->exec() == SystemUiResult::ConfirmButtonSelection)
	{
    	QString text = prompt->inputFieldTextEntry();
    	return text;
	}
    else
    {
        prompt->deleteLater();
        return NULL;
    }
}
