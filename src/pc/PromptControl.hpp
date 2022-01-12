#ifndef PromptControl_HPP_
#define PromptControl_HPP_


#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeTarget>

#define REVIEWCONTROL_RUNCOUNT		"review_control_runcount"
#define REVIEWCONTROL_RATED			"review_control_rated"
#define REVIEWCONTROL_SUPPORTED		"review_control_supported"
#define REVIEWCONTROL_PROMPTINDEX	"review_control_promptindex"
#define REVIEWCONTROL_ACTIVE		"review_control_active"
#define REVIEWCONTROL_MORED			"review_control_more"

using namespace bb::system;

class Q_CORE_EXPORT PromptControl: public QObject
{
	Q_OBJECT
	public:
		PromptControl(const QString &t, const QString &u, int freq);

		void 		run();

		void		rate();
		void		rateDialog();
		bool		isRated();
		void		rated(const bool &state);

		void		support();
		void		supportDialog();
		bool		isSupported();
		void		supported(const bool &state);

		void		more();
		void		moreDialog();
		bool		isMored();
		void		mored(const bool &state);

		int			runCount();
		void 		runCount(const int &index);

		void		reset();
	private:
		QString				title;
		QString				uri;
		int					freq;
};

#endif /* PromptControl_HPP_ */
