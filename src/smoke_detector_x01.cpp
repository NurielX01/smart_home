#include "smoke_detector_x01.hpp" //SmokeDetectorX01 header


namespace advcpp
{

SmokeDetectorX01::SmokeDetectorX01(string a_id, string a_type, string a_selfLocation, vector<EventId>& a_eventInterest, string a_eventType)
: Agent(a_id, a_type, a_selfLocation, a_eventInterest, a_eventType){}

}

