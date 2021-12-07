#include "server_tcp.hpp" //Server header


namespace advcpp
{

ServerTcp::ServerTcp(size_t a_capacity, vector<Agent*>& a_agentContiner, Server* a_server)
: m_agentSocketsContainer(a_agentContiner)
, m_socketContainer(a_capacity)
, m_messageHandler(&m_socketContainer, &m_agentSocketsContainer, a_server) {}

void ServerTcp::Run()
{
    Selector selector(&m_socketContainer, &m_messageHandler);
}

MessageHandler* ServerTcp::GetMessageHandler()
{
    return &m_messageHandler;
}

}

