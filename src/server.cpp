#include "server.hpp" //Server header
#include "agent.hpp" //Agent header
#include "smoke_detector_x01.hpp" //SmokeDetectorX01 header
#include "sprinkler_x01.hpp" //SprinklerX01 header
#include "server_tcp.hpp" //ServerTcp header


namespace advcpp
{

Server::Server(size_t a_eventCapacity, int a_clientCapacity,  size_t a_numThreads)
: m_agentsContainer( CreateAgents() )
, m_subscribers(m_agentsContainer) 
, m_eventsTp(a_eventCapacity, a_numThreads)
{
    SubscribeAgents();
    ServerTcp serverTcp(a_clientCapacity, GetAgents(), this);
    m_handler = serverTcp.GetMessageHandler();
    serverTcp.Run();
}

Server::~Server()
{
    size_t agentAmount = m_agentsContainer.size();
    for(size_t i = 0 ; i < agentAmount ; ++i)
    {
        m_agentsContainer[i]->~Agent();
    }
}

void Server::SubscribeAgents()
{
    size_t agentAmount = m_agentsContainer.size();
    for(size_t i = 0 ; i < agentAmount ; ++i)
    {
        m_subscribers.AddSubscriber(m_agentsContainer[i]);
    }
}

vector<Agent*> Server::CreateAgents()
{
    vector<Agent*> agentsContainer;
    vector<EventId> detectorEventList;
    vector<EventId> sprinklerEventList;

    sprinklerEventList.emplace_back(EventId("BUILDING_01__FLOOR_02__ROOM_03", "SMOKE_DETECTED"));
    agentsContainer.emplace_back(new SmokeDetectorX01("SMOKE_DETECT_01", "SMOKE_DETECTED", "BUILDING_01__FLOOR_02__ROOM_03", detectorEventList, "SMOKE_DETECTED"));
    agentsContainer.emplace_back(new SprinklerX01("SPRINKLER_01", "SPRINKLER", "BUILDING_01__FLOOR_02__ROOM_08", sprinklerEventList, "test_config_data", "SPRINKLER")); 
    return agentsContainer;
}

void Server::RouteEvent(Event a_event)
{   
    std::cout << "server: routing event" << std::endl;

    auto eventLocation = a_event.GetLocation();
    auto eventType = a_event.GetEventType();

    EventId eventId(eventLocation, eventType);
    vector<Agent*> resultSubscriberContainer(1);
    auto resultPair = m_subscribers.FindSubscribers(eventId, resultSubscriberContainer);
    
    if(false == resultPair)
    {   
        return;
    }
    
    auto currentItr = resultSubscriberContainer.begin();
    auto endItr = resultSubscriberContainer.end();

    while(currentItr != endItr)
    {   
        auto agentPtr = *currentItr;
        agentPtr->ReceiveUpdate(a_event, m_handler);
        ++currentItr;
    }
}

bool Server::AddEvent(std::shared_ptr<Callable> a_taskEventRouting)
{
    return m_eventsTp.Submit(a_taskEventRouting);
}

vector<Agent*>& Server::GetAgents()
{
    return m_agentsContainer;
}

ThreadPool& Server::GetThreadPool()
{
    return m_eventsTp;
}

}

