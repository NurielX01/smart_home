#ifndef SMOKE_DETECTOR_X01_HPP_
#define SMOKE_DETECTOR_X01_HPP_
#include "agent.hpp" //Agent header


namespace advcpp
{

using std::vector;
class SmokeDetectorX01 : public Agent
{
public:
    // ctor, dtor
    SmokeDetectorX01(string a_id, string a_type, string a_selfLocation, vector<EventId>& a_eventInterest, string a_eventType);
    ~SmokeDetectorX01() = default;
};

}


#endif // SMOKE_DETECTOR_X01_HPP_