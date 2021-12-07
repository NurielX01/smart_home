#ifndef SUBSCRIBERS_HPP_
#define SUBSCRIBERS_HPP_
#include "event_id.hpp" //EventId header
#include <vector> //std::vector
#include <map> //std::map
#include <string> //std::string


namespace advcpp
{

class Agent;   
using std::string;
using std::map;
using std::vector;
class Subscribers
{
public:
    // ctor, dtor
    Subscribers(vector<Agent*>& a_subscribers);
    ~Subscribers() = default;

    // prevent using
    Subscribers(const Subscribers& a_other) = delete;
    Subscribers& operator=(const Subscribers& a_other) = delete;

    // methods
    size_t AddSubscriber(Agent* a_subscriber); //TODO - devide into more private methods
    bool FindSubscribers(EventId a_eventId, vector<Agent*>& a_resultContainer); //TODO - try change to const& return

    // get methods
    size_t GetContainerSize() const;
    size_t GetContainerSizeInner(string a_location) const;
    size_t GetNumSubscribers(string a_eventLocation, string a_eventType) const; 

private:
    void SearchAndAddEventContainer(map<string, vector<Agent*>>& a_typeContainer, string& a_eventType);
    void AddContainer(string& a_eventType, string& a_eventLocation);
    void CheckDuplicateAndAdd(vector<Agent*>& a_subscribers, Agent* a_subscriber, size_t& a_eventCounter);

private:
    using container = map<string, map<string, vector<Agent*>>>;
    container m_subscriberContainer;
};

}


#endif //SUBSCRIBERS_HPP_