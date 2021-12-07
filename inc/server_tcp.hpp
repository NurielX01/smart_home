#ifndef SERVER_TCP_HPP_
#define SERVER_TCP_HPP_
#include "selector.hpp" //Selector header
#include "message_handler.hpp" //MessageHandler header
#include "agent_socket_container.hpp" //AgentSocketContainer header
#include <vector> //std::vector 


namespace advcpp
{

using std::vector;

//fwd declarations
class Agent;
class Server;

class ServerTcp {
public:
    // ctor, dtor
    ServerTcp(size_t a_capacity, vector<Agent*>& a_agentContiner, Server* a_server);
    ~ServerTcp() = default;

    // class methods
    void Run();
    MessageHandler* GetMessageHandler();

private:
    AgentSocketContainer m_agentSocketsContainer; //TODO - unite with SocketContainer
    SocketContainer m_socketContainer;  
    MessageHandler m_messageHandler;
};

}


#endif // SERVER_TCP_HPP_