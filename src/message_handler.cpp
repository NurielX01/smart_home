#include <iostream> //std::cout
#include "message_handler.hpp" //MessageHandler header
#include "incoder.hpp" //Incoder header
#include "message_decoder.hpp" //MessageDecoder header
#include "socket_container.hpp" //SocketContainer header
#include "agent_socket_container.hpp" //AgentSocketContainer header
#include "agent.hpp" //Agent header


namespace advcpp
{

MessageHandler::MessageHandler(SocketContainer* a_socketContainer, AgentSocketContainer* a_agentAndSocketsContainer, Server* a_server)
: m_socketContainer(a_socketContainer)
, m_agentAndSocketsContainer(a_agentAndSocketsContainer)
, m_server(a_server) {}

bool MessageHandler::Handle(string a_rawMessage, int a_socketDescriptor) //TODO - template handeler to receive decode type
{
    MessageDecoder decoder(a_rawMessage);
        
    auto requestType = decoder.FindInMessage<char>("op");
    switch (requestType)
    {
        case 'c':
        {
            std::cout << "MessageHandler: connection request" << std::endl;
            auto agentId = decoder.FindInMessage<string>("id");
            return ConnectAgent(agentId, a_socketDescriptor);
            break;
        }

        case 'e':
        {
            std::cout << "MessageHandler: event received" << std::endl;
            auto parsedMessage = decoder.Decode();
            return MoveEventToAgent(parsedMessage, a_socketDescriptor);
            break;
        }

        default:
        {
            std::cout << "MessageHandler: default case" << std::endl;
            return false;
        }
    }

    return true;
}

bool MessageHandler::MoveEventFromAgent(Event a_event, string a_agentId)
{
    auto agentSocket = m_agentAndSocketsContainer->GetSock(a_agentId);

    Socket resultSocket;
    auto findResult = m_socketContainer->Find(agentSocket, resultSocket);
    if(!findResult)
    {
        return false;
    }

    Incoder incoder;
    auto rawMessage = incoder.Incode(a_event);
    resultSocket.Send(rawMessage);
    return true;
}

bool MessageHandler::ConnectAgent(string a_agentId, int a_socketDescriptor)
{
    return m_agentAndSocketsContainer->Add(a_agentId, a_socketDescriptor);
}

bool MessageHandler::MoveEventToAgent(json a_message, int a_socketDescriptor)
{
    Agent* agent;
    try
    {
        std::cout << "Message Handler: moving event to agent, sock: " << a_socketDescriptor << std::endl;
        agent = m_agentAndSocketsContainer->FindAgent(a_socketDescriptor);
    }
    catch(...)
    {
        return false;
    }
    
    auto timeStamp = a_message.find("ts")->get<string>();
    auto type = a_message.find("type")->get<string>();
    auto payload = a_message.find("pl")->get<string>();
    auto location = a_message.find("loc")->get<string>();

    Event eventToPublish(timeStamp, type, payload, location);
    agent->PublishEvent(eventToPublish, m_server);

    return true;
}

}

