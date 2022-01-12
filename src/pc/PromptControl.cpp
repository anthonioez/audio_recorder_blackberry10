#include "PromptControl.hpp"
#include "utils.hpp"

PromptControl::PromptControl(const QString &t, const QString &u, int f)
{
	this->title = t;
	this->freq = f;
	this->uri = u;
}


void PromptControl::run()
{
	int rc = runCount();
	if(rc == 5 || rc == 15 || (rc > 0 && rc < (freq*4) && (rc % freq) == 0))
	{
		if(!isSupported())
		{
			supportDialog();
		}
		else
		{
			if(!isRated())
			{
				rateDialog();
			}
			else
			{
				if(!isMored())
				{
					moreDialog();
				}
			}
		}
	}

	if(rc > 0 && (rc % (freq*5)) == 0)
	{
		mored(false);
	}

	runCount(runCount() + 1);
}


void PromptControl::supportDialog()
{
	if(confirm(title, "Would you like to contact the developer?"))
	{
		support();
	}
	else
	{
		if(!isRated())
		{
			rateDialog();
		}
	}

	supported(true);
}




void PromptControl::rateDialog()
{
	if(confirm(title, "Would you like to rate this app?"))
	{
		rate();
	}
	else
	{
		if(!isMored())
		{
			moreDialog();
		}
	}
}


void PromptControl::moreDialog()
{
	if(confirm(title, "Check out more apps by Miciniti?"))
	{
		more();
	}
}


bool PromptControl::isRated()
{
    QSettings settings;
    bool unit = settings.value(REVIEWCONTROL_RATED, false).toBool();
    return unit;
}


void PromptControl::rated(const bool &state)
{
    QSettings settings;
    settings.setValue(REVIEWCONTROL_RATED, QVariant((bool)state));
}

bool PromptControl::isSupported()
{
    QSettings settings;
    bool unit = settings.value(REVIEWCONTROL_SUPPORTED, false).toBool();
    return unit;
}


void PromptControl::supported(const bool &state)
{
    QSettings settings;
    settings.setValue(REVIEWCONTROL_SUPPORTED, QVariant((bool)state));
}

bool PromptControl::isMored()
{
    QSettings settings;
    bool unit = settings.value(REVIEWCONTROL_MORED, false).toBool();
    return unit;
}


void PromptControl::mored(const bool &state)
{
    QSettings settings;
    settings.setValue(REVIEWCONTROL_MORED, QVariant((bool)state));
}

void PromptControl::support()
{
	InvokeRequest cardRequest;
	cardRequest.setAction("bb.action.OPEN, bb.action.SENDEMAIL");
	cardRequest.setTarget("sys.pim.uib.email.hybridcomposer");
	cardRequest.setUri("mailto:miciniti@gmail.com?subject=Dear%20Developer&body=Can%20you%20please%20add...");
	InvokeManager* invokeManager = new InvokeManager();
	invokeManager->invoke(cardRequest);
}

void PromptControl::rate()
{
	InvokeRequest cardRequest;
	cardRequest.setAction("bb.action.OPEN");
	cardRequest.setTarget("sys.appworld");
	cardRequest.setUri(uri);
	InvokeManager* invokeManager = new InvokeManager();
	invokeManager->invoke(cardRequest);

	rated(true);
}


void PromptControl::more()
{
	InvokeRequest cardRequest;
	cardRequest.setAction("bb.action.OPEN");
	cardRequest.setTarget("sys.appworld");
	cardRequest.setUri("appworld://vendor/37262");
	InvokeManager* invokeManager = new InvokeManager();
	invokeManager->invoke(cardRequest);

	mored(true);
}

int PromptControl::runCount()
{
    QSettings settings;
    int unit = settings.value(REVIEWCONTROL_RUNCOUNT, 0).toInt();
    return unit;
}

void PromptControl::runCount(const int &index)
{
    QSettings settings;
    settings.setValue(REVIEWCONTROL_RUNCOUNT, QVariant((int)index));
}

void PromptControl::reset()
{
	rated(false);
	mored(false);
	supported(false);
	runCount(0);
}
