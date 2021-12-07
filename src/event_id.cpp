#include "event_id.hpp" //EventId header


namespace advcpp
{

EventId::EventId(string a_eventLocation, string a_eventType)
: m_location(a_eventLocation)
, m_type(a_eventType) {}
    
string EventId::GetLocation() const
{
    return m_location;
}

string EventId::GetType() const
{
    return m_type;
}

}
