#include "settings.hpp"

int getRunCount()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_RUNCOUNT, 0).toInt();
    return unit;
}

void setRunCount(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_RUNCOUNT, QVariant((int)index));
}

int getRecordCount()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_RECORD_COUNT, 1).toInt();
    return unit;
}

void setRecordCount(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_RECORD_COUNT, QVariant((int)index));
}

long getCurrentFolder()
{
    QSettings settings;
    long unit = settings.value(SETTINGS_CURRENT_FOLDER, 0).toInt();
    return unit;
}

void setCurrentFolder(const long &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_CURRENT_FOLDER, QVariant((qlonglong)index));
}

int getFormat()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_QUALITY, 2).toInt();
    return unit;
}

void setFormat(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_QUALITY, QVariant((int)index));
}

int getSequence()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_SEQUENCE, 1).toInt();
    return unit;
}

void setSequence(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_SEQUENCE, QVariant((int)index));
}

int getStore()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_STORE, 1).toInt();
    return unit;
}

void setStore(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_STORE, QVariant((int)index));
}

int getSound()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_SOUND, 3).toInt();
    return unit;
}

void setSound(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_SOUND, QVariant((int)index));
}

int getVibrate()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_VIBRATE, 0).toInt();
    return unit;
}

void setVibrate(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_VIBRATE, QVariant((int)index));
}

int getLed()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_LED, 1).toInt();
    return unit;
}

void setLed(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_LED, QVariant((int)index));
}


int getSort()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_SORT, SORT_STAMP).toInt();
    return unit;
}

void setSort(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_SORT, QVariant((int)index));
}


bool getOrder()
{
    QSettings settings;
    bool unit = settings.value(SETTINGS_ORDER, false).toBool();
    return unit;
}

void setOrder(const bool &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_ORDER, QVariant((bool)index));
}

bool getInternalPlayer()
{
    QSettings settings;
    bool unit = settings.value(SETTINGS_PLAYER, true).toBool();
    return unit;
}

void setInternalPlayer(const bool &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_PLAYER, QVariant((bool)index));
}

bool getShowSpeed()
{
    QSettings settings;
    bool unit = settings.value(SETTINGS_SHOW_SPEED, false).toBool();
    return unit;
}

void setShowSpeed(const bool &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_SHOW_SPEED, QVariant((bool)index));
}

bool getSavePrompt()
{
    QSettings settings;
    bool unit = settings.value(SETTINGS_SAVE_PROMPT, 0).toBool();
    return unit;
}

void setSavePrompt(const bool &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_SAVE_PROMPT, QVariant((bool)index));
}

bool getCancelPrompt()
{
    QSettings settings;
    bool unit = settings.value(SETTINGS_CANCEL_PROMPT, 1).toBool();
    return unit;
}

void setCancelPrompt(const bool &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_CANCEL_PROMPT, QVariant((bool)index));
}

int getUI()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_UI, 0).toInt();
    return unit;
}

void setUI(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_UI, QVariant((int)index));
}

int getThemes()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_THEME, 0).toInt();
    return unit;
}

void setThemes(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_THEME, QVariant((int)index));
}


int getPassworded()
{
    QSettings settings;
    int unit = settings.value(SETTINGS_PASSWORDED, 0).toInt();
    return unit;
}

void setPassworded(const int &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_PASSWORDED, QVariant((int)index));
}

QString getPassword()
{
    QSettings settings;
    QString unit = settings.value(SETTINGS_PASSWORD, "").toString();
    return unit;
}

void setPassword(const QString &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_PASSWORD, index);
}


QString getRecoveryQuestion()
{
    QSettings settings;
    QString unit = settings.value(SETTINGS_RECOVERY_QUESTION, "").toString();
    return unit;
}

void setRecoveryQuestion(const QString &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_RECOVERY_QUESTION, index);
}

QString getRecoveryAnswer()
{
    QSettings settings;
    QString unit = settings.value(SETTINGS_RECOVERY_ANSWER, "").toString();
    return unit;
}

void setRecoveryAnswer(const QString &index)
{
    QSettings settings;
    settings.setValue(SETTINGS_RECOVERY_ANSWER, index);
}
