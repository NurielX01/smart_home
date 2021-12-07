#include "mu_test.h" //Unit testing header
#include "agent.hpp" //Agent header
#include "smoke_detector_x01.hpp" //SmokeDetectorX01 header
#include "subscribers.hpp" //Subscribers header
#include "event_id.hpp" //EventId header
#include "server.hpp" //Server header
#include "server_tcp.hpp" //ServerTcp header
#include "message_decoder.hpp" //MessageDecoder header
#include "json.hpp" //json header
#include <string> //String header
#include <iostream> //std::cout, endl
using namespace advcpp;


BEGIN_TEST(server_simple_test_send_and_receive_event)
{
    const size_t EVENT_CAPACITY = 1;
    const size_t THREAD_CAPACITY = 1;
    const size_t CLIENT_CAPACITY = 2;

    Server server(EVENT_CAPACITY, CLIENT_CAPACITY, THREAD_CAPACITY);
    ASSERT_PASS();
}
END_TEST


BEGIN_SUITE(不耻下问)
    
TEST(server_simple_test_send_and_receive_event)

END_SUITE
