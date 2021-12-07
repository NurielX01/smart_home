#ifndef EVENT_HPP_
#define EVENT_HPP_
#include <string> //std::string


namespace advcpp
{

using std::string;
class Event
{
public:
    //dtor, ctor
    Event(string a_timeStamp, string a_eventType, string a_dataPayload, string a_location);
    ~Event() = default;

    //copy ctor, assignemnt 
    Event(const Event& a_other) = default;
    Event& operator=(const Event& a_other) = default;

    //public methods, operators
    bool operator==(const Event& a_other) const;
    string GetTimeStamp() const;
    string GetEventType() const;
    string GetDataPayload() const;
    string GetLocation() const;

private:
    string m_timeStamp;
    string m_eventType;
    string m_dataPayload;
    string m_location;
};

}


#endif //EVENT_HPP_
