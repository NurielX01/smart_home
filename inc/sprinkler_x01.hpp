#ifndef SPRINKLER_X01_HPP_
#define SPRINKLER_X01_HPP_
#include "agent.hpp" //agent header


namespace advcpp
{

class SprinklerX01 : public Agent
{
public:
    // ctor, dtor
    SprinklerX01(string a_id, string a_type, string a_selfLocation, vector<EventId>& a_eventInterest, string a_configData, string a_eventType);
    ~SprinklerX01() = default;

private:
    string m_configData;
};

}


#endif //SPRINKLER_X01_HPP_