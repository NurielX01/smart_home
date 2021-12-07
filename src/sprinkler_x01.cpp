#include "sprinkler_x01.hpp" //DeviceAgent header


namespace advcpp
{

SprinklerX01::SprinklerX01(string a_id, string a_type, string a_selfLocation, vector<EventId>& a_eventInterest, string a_configData, string a_eventType)
: Agent(a_id, a_type, a_selfLocation, a_eventInterest, a_eventType)
, m_configData(a_configData) {}

}
