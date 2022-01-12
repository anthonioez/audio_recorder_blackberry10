#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <QString>
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QSettings>
#include <QDebug>

#define SETTINGS_RUNCOUNT			"run_counter"
#define SETTINGS_RECORD_COUNT		"record_count"

#define SETTINGS_QUALITY			"settings_quality"
#define SETTINGS_SEQUENCE			"settings_sequence"
#define SETTINGS_STORE				"settings_store"

#define SETTINGS_SOUND				"settings_sound"
#define SETTINGS_VIBRATE			"settings_vibrate"
#define SETTINGS_LED				"settings_led"

#define SETTINGS_SORT				"settings_sort"
#define SETTINGS_ORDER				"settings_order"

#define SETTINGS_PLAYER				"settings_player"
#define SETTINGS_SHOW_SPEED			"settings_show_speed"

#define SETTINGS_SAVE_PROMPT		"settings_save_prompt"
#define SETTINGS_CANCEL_PROMPT		"settings_cancel_prompt"
#define SETTINGS_UI					"settings_ui"
#define SETTINGS_THEME				"settings_theme"

#define SETTINGS_CURRENT_FOLDER		"settings_current_folder"

#define SETTINGS_PASSWORDED			"settings_passworded"
#define SETTINGS_PASSWORD			"settings_password"
#define SETTINGS_RECOVERY_QUESTION	"settings_recovery_question"
#define SETTINGS_RECOVERY_ANSWER	"settings_recovery_answer"

#define SORT_TITLE		0
#define SORT_DESC		1
#define SORT_DURATION	2
#define SORT_SIZE		3
#define SORT_STAMP		4
#define SORT_RID		5
#define SORT_FID		6

int		getRunCount(void);
void 	setRunCount(const int &index);

int		getRecordCount(void);
void 	setRecordCount(const int &index);

long	getCurrentFolder(void);
void 	setCurrentFolder(const long &index);

int		getFormat(void);
void 	setFormat(const int &index);

int		getSequence(void);
void 	setSequence(const int &index);

int		getStore(void);
void 	setStore(const int &index);

int		getSound(void);
void 	setSound(const int &index);

int		getVibrate(void);
void 	setVibrate(const int &index);

int		getLed(void);
void 	setLed(const int &index);

int		getSort(void);
void 	setSort(const int &index);

bool	getOrder(void);
void 	setOrder(const bool &index);

bool	getShowSpeed(void);
void 	setShowSpeed(const bool &index);

bool	getInternalPlayer(void);
void 	setInternalPlayer(const bool &index);

bool	getSavePrompt(void);
void 	setSavePrompt(const bool &index);

bool	getCancelPrompt(void);
void 	setCancelPrompt(const bool &index);

int		getUI(void);
void 	setUI(const int &index);

int		getThemes(void);
void 	setThemes(const int &index);

int 	getPassworded();
void 	setPassworded(const int &index);


QString getPassword();
void 	setPassword(const QString &index);

QString getRecoveryQuestion();
void 	setRecoveryQuestion(const QString &index);

QString getRecoveryAnswer();
void 	setRecoveryAnswer(const QString &index);

#endif /* SETTINGS_HPP_ */

