#include "subscribers.hpp" //Subscribers header
#include "agent.hpp" //agent header
#include <algorithm> //std::find


namespace advcpp
{

Subscribers::Subscribers(vector<Agent*>& a_subscribers)
{
    auto numAgents = a_subscribers.size();    
    for(size_t i = 0 ; i < numAgents ; ++i)
    {
        auto eventId = a_subscribers[i]->GetEventId();
        auto eventLocation = eventId.GetLocation();
        auto eventType = eventId.GetType();
        auto ContainerItr = m_subscriberContainer.find(eventLocation); 

        if(m_subscriberContainer.end() != ContainerItr) // found map #1
        {
            SearchAndAddEventContainer(ContainerItr->second, eventType); // look for inner map, add if not exist
        }
        else // not found map #1
        {
            AddContainer(eventType, eventLocation);
        }
    }
}

size_t Subscribers::AddSubscriber(Agent* a_agent)
{
    size_t eventsSubscribed = 0;
    auto subscriberIntrests = a_agent->GetEventInterest();
    auto iterestAmount = subscriberIntrests.size();

    for(size_t i = 0 ; i < iterestAmount ; ++i)
    {
        auto eventIterestLocation = subscriberIntrests[i].GetLocation();
        auto subscriberEventType = subscriberIntrests[i].GetType();

        auto currentItr = m_subscriberContainer.begin();
        auto endItr = m_subscriberContainer.end();
        while(currentItr != endItr)
        {
            auto result = currentItr->first.find(eventIterestLocation, 0);
            if(result != string::npos)
            {
                try
                {
                    auto& containerType = currentItr->second;
                    auto& foundList = containerType.at(subscriberEventType);
                    CheckDuplicateAndAdd(foundList, a_agent, eventsSubscribed);
                }
                catch(...){}   
            }
            ++currentItr;
        }
    }
    return eventsSubscribed;
}

void Subscribers::CheckDuplicateAndAdd(vector<Agent*>& a_subscribers, Agent* a_subscriber, size_t& a_eventCounter)
{
    auto begin = a_subscribers.begin();
    auto end = a_subscribers.end();
    auto resultItr = std::find(begin, end, a_subscriber);

    if(resultItr == end)
    {
        a_subscribers.push_back(a_subscriber);
        ++a_eventCounter;
    }
}

void Subscribers::SearchAndAddEventContainer(map<string, vector<Agent*>>& a_typeContainer, string& a_eventType)
{
    auto typeItr = a_typeContainer.find(a_eventType);
    if(a_typeContainer.end() == typeItr) // not found map #2
    {   
        vector<Agent*> subscribers;
        a_typeContainer.insert({a_eventType, subscribers});
    }
}

void Subscribers::AddContainer(string& a_eventType, string& a_eventLocation)
{
    map<string, vector<Agent*>> events;
    vector<Agent*> subscribers;
    events.insert({a_eventType, subscribers});
    m_subscriberContainer.insert({a_eventLocation, events});    
}

size_t Subscribers::GetContainerSize() const
{
    return m_subscriberContainer.size();
}

size_t Subscribers::GetContainerSizeInner(string a_location) const
{
    try
    {
        auto result = m_subscriberContainer.at(a_location).size();
        return result;
    }
    catch(...)
    {
        return 0;
    }
}

size_t Subscribers::GetNumSubscribers(string a_eventLocation, string a_eventType) const
{
    try
    {
        auto& result1 = m_subscriberContainer.at(a_eventLocation);
        auto& result2 = result1.at(a_eventType);
        return result2.size();
    }
    catch(...)
    {
        return 0;
    }
}

bool Subscribers::FindSubscribers(EventId a_eventId, vector<Agent*>& a_resultContainer)
{
    auto eventLocation = a_eventId.GetLocation();
    auto eventType = a_eventId.GetType();
    
    try
    {
        auto events = m_subscriberContainer.at(eventLocation);
        a_resultContainer = events.at(eventType);
        return true;
    }
    
    catch(...)
    {
        return false;
    }
}

}

