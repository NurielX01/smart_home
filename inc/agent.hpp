#ifndef _AGENT_HPP_
#define _AGENT_HPP_
#include "server.hpp" //Server header
#include "event.hpp" //Event header
#include "event_id.hpp" //Event Id
#include <string> //std::string
#include <ctime> //std::time_t, std::asctime, std::local_time


namespace advcpp
{

class  MessageHandler;
using std::string;
using std::vector;
class Agent
{
public:
    //ctor, dtor
    Agent(string a_id, string a_type, string a_selfLocation, vector<EventId>& a_eventInterest, string a_eventType);
    ~Agent() = default;

    //avoid using
    Agent(const Agent& a_other) = delete;
    Agent& operator=(const Agent& a_other) = delete;

    //class operators
    bool operator==(const Agent& a_other) const;

    //class methods
    void PublishEvent(Event a_event, Server* a_server);
    void ReceiveUpdate(Event a_event, MessageHandler* a_handler);

    // class get methods
    string GetId() const;
    string GetLocation() const;
    string GetType() const;
    EventId GetEventId() const;
    vector<EventId> GetEventInterest() const;

public:
    Event ParseEvent(/*string*/) const;
    
private:
    string m_id;
    string m_type;
    string m_selfLocation;
    EventId m_eventId;
    vector<EventId> m_eventInterest;
};

}


#endif //AGENT_HPP_

