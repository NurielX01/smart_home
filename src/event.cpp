#include "event.hpp" //Event header


namespace advcpp
{

Event::Event(string a_timeStamp, string a_eventType, string a_dataPayload, string a_location)
: m_timeStamp(a_timeStamp)
, m_eventType(a_eventType)
, m_dataPayload(a_dataPayload)
, m_location(a_location) {}

bool Event::operator==(const Event& a_other) const
{
    if(a_other.m_eventType == m_eventType && a_other.m_location == m_location)
    {
        return true;
    }
    return false;
}

string Event::GetTimeStamp() const
{
    return m_timeStamp;
}

string Event::GetEventType() const
{
    return m_eventType;
}

string Event::GetDataPayload() const
{
    return m_dataPayload;
}

string Event::GetLocation() const
{
    return m_location;
}

}

