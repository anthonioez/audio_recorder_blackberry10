#include "BBMInvite.hpp"

#include <bb/platform/bbm/MessageService>
#include <bb/system/SystemToast>
#include <bps/netstatus.h>

using namespace bb::system;

BBMInvite::BBMInvite(bb::platform::bbm::Context *context) :
		m_messageService(0), m_context(context)
{
}

BBMInvite::~BBMInvite()
{
	delete m_messageService;
}

bool BBMInvite::sendInvite()
{
	bool is_available;
	netstatus_get_availability(&is_available);

	if (is_available)
	{
		if(m_context->isAccessAllowed())
		{
			if (!m_messageService)
			{
				m_messageService = new bb::platform::bbm::MessageService(m_context, this);
			}
			return m_messageService->sendDownloadInvitation();
		}
		else
		{
			SystemToast *toast = new SystemToast(this);
			toast->setBody("No BBM connection, please try again.");
			toast->show();
		}
	}
	else
	{
		SystemToast *toast = new SystemToast(this);
		toast->setBody("No network connection available.");
		toast->show();
		return true;
	}
	return false;
}
