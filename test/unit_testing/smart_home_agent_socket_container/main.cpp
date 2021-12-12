#include "mu_test.h"
#include "agent.hpp" //Agent header
#include "smoke_detector_x01.hpp" //SmokeDetectorX01 header
#include "subscribers.hpp" //Subscribers header
#include "event_id.hpp" //EventId header
#include "server.hpp" //Server header
#include "message_decoder.hpp" //MessageDecoder header
#include "agent_socket_container.hpp" //AgentSocketContainer header
#include "json.hpp" //json header
#include <string> //String header
#include <iostream>


using namespace advcpp;


BEGIN_TEST(simple_test)
{
    vector<EventId> eventIds;
    eventIds.emplace_back("test", "test");
    vector<Agent*> vectorAgents;
    vectorAgents.emplace_back(new Agent("agent100", "smoke_detector", "test", eventIds, "testtype"));

    AgentSocketContainer cont(vectorAgents);

    auto result = cont.GetSock("agent100");
    ASSERT_EQUAL(result, 0);

    auto added = cont.Add("agent100", 4);
    result = cont.GetSock("agent100");
    ASSERT_EQUAL(result, 4);
    ASSERT_EQUAL(added, true);

    added = cont.Add("agent101", 4);
    ASSERT_EQUAL(added, false);
}
END_TEST


BEGIN_SUITE(不耻下问)
    
TEST(simple_test)

END_SUITE
