#ifndef MESSAGE_HANDLER_HPP_
#define MESSAGE_HANDLER_HPP_
#include "event.hpp" //EventHeader
#include <string> //std::string
#include "json.hpp" //json


namespace advcpp
{

using json = nlohmann::json;
using std::vector;

//fwd declarations
using std::string;
class SocketContainer;
class AgentSocketContainer;
class Server;

class MessageHandler
{
public:
    // ctor, dtor
    MessageHandler(SocketContainer* a_socketContainer, AgentSocketContainer* a_agentAndSocketsContainer, Server* a_server);
    ~MessageHandler() = default;
    
    // class methods
    bool Handle(string a_rawMessage, int a_socketDescriptor);
    bool MoveEventFromAgent(Event a_event, string a_agentId);

private:
    bool ConnectAgent(string a_agentId, int a_socketDescriptor);
    bool MoveEventToAgent(json a_message, int a_socketDescriptor); // TODO - avoid exposing json

private:
    SocketContainer* m_socketContainer;
    AgentSocketContainer* m_agentAndSocketsContainer;
    Server* m_server;
};

}


#endif // MESSAGE_HANDLER_HPP_