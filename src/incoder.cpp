#include "incoder.hpp" //Incoder header
#include "json.hpp" //json


namespace advcpp
{

using json = nlohmann::json;
string Incoder::Incode(Event a_event) const
{
    json j2;
    int messageSize = 47;

    messageSize += a_event.GetTimeStamp().size();
    messageSize += a_event.GetEventType().size();
    messageSize += a_event.GetDataPayload().size();
    messageSize += a_event.GetLocation().size();
    
    j2["size"] = messageSize;
    j2["op"] = 'e';
    j2["ts"] = a_event.GetTimeStamp();
    j2["type"] = a_event.GetEventType();
    j2["pl"] = a_event.GetDataPayload();
    j2["loc"] = a_event.GetLocation();

    return j2.dump();
}

}
