#ifndef EVENT_ID_HPP_
#define EVENT_ID_HPP_
#include <string> //std::string


namespace advcpp
{

using std::string;
class EventId
{
public:
    EventId(string a_eventLocation, string a_eventType);
    ~EventId() = default;
    
    string GetLocation() const;
    string GetType() const;

private:
    string m_location;
    string m_type;
};

}


#endif // EVENT_ID_HPP_