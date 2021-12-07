#include <iostream> //std::cout
#include "agent.hpp" //Agent header
#include "task_event_routing.hpp" //TaskEventRouting header
#include "message_handler.hpp" // Message handler


namespace advcpp
{

Agent::Agent(string a_id, string a_type, string a_selfLocation, vector<EventId>& a_eventInterest, string a_eventType)
: m_id(a_id)
, m_type(a_type)
, m_selfLocation(a_selfLocation)
, m_eventId(a_selfLocation, a_eventType)
, m_eventInterest(a_eventInterest) {}

void Agent::PublishEvent(Event a_event, Server* a_server)
{
    auto task = std::make_shared<TaskEventRouting>(a_event, a_server);
    a_server->AddEvent(task);
    std::cout << "Agent ID " << m_id << ": event published" << std::endl; 
}

void Agent::ReceiveUpdate(Event a_event, MessageHandler* a_handler)
{
    a_handler->MoveEventFromAgent(a_event, GetId());
}

string Agent::GetId() const
{
    return m_id;
}

string Agent::GetLocation() const
{
    return m_selfLocation;
}

string Agent::GetType() const
{
    return m_type;
}

EventId Agent::GetEventId() const
{
    return m_eventId;
}

vector<EventId> Agent::GetEventInterest() const
{
    return m_eventInterest;
}

Event Agent::ParseEvent(/* event data payload */) const
{
    std::time_t result = std::time(nullptr);
    string timeStamp = std::asctime(std::localtime(&result));
    auto location = GetLocation();
    auto eventType = GetEventId().GetType();
    auto eventLocation = GetEventId().GetLocation();

    return Event(timeStamp, eventType, "data payload test", eventLocation);
}

bool Agent::operator==(const Agent& a_other) const
{
    return m_id == a_other.m_id;
}

}

