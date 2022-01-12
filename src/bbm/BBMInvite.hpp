#ifndef BBMInvite_HPP_
#define BBMInvite_HPP_

#include <QtCore/QObject>
#include <bb/platform/bbm/Context>
#include <bb/platform/bbm/MessageService>

using namespace bb::platform::bbm;

class BBMInvite: public QObject
{
Q_OBJECT


public:
	BBMInvite(bb::platform::bbm::Context *context);
	~BBMInvite();

	Q_INVOKABLE bool sendInvite();

private:
	MessageService * m_messageService;
	Context* m_context;

};

#endif /* BBMInvite_HPP_ */
