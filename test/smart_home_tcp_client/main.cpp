#include <string> //std::string
#include <iostream> //std::cout
#include "mu_test.h" //Unit testing header
#include "hardware_client.hpp" //HardwareClient header
#include "json.hpp" //json
using json = nlohmann::json;
using namespace advcpp;
using std::string;


BEGIN_TEST(simple_test_publish_event)
{
    HardwareClient sensor(1025, "127.0.0.1");
    HardwareClient sprinkler(1025, "127.0.0.1");

    string data1;
    string data2;
    sensor.ReceiveFrom(data1);
    sprinkler.ReceiveFrom(data2);

    if(data1 != "connection successfull" || data2 != "connection successfull")
    {
        ASSERT_FAIL("failed");
    }

    json sensorJson1;
    sensorJson1["size"] = 43;
    sensorJson1["op"] = 'c';
    sensorJson1["id"] = "SMOKE_DETECT_01";
    string rawMessage1 = sensorJson1.dump();
    sensor.SendTo(rawMessage1); //sensor sends agent Id

    json sprinklerJson1;
    sprinklerJson1["size"] = 40;
    sprinklerJson1["op"] = 'c';
    sprinklerJson1["id"] = "SPRINKLER_01";
    string rawMessage2 = sprinklerJson1.dump();
    sprinkler.SendTo(rawMessage2); //sprinkler sends agent Id

    json sensorJson2;
    sensorJson2["size"] = 140;
    sensorJson2["op"] = 'e';
    sensorJson2["ts"] = "saturday__07/08//2021__13:20";
    sensorJson2["type"] = "SMOKE_DETECTED";
    sensorJson2["pl"] = "test-payload";
    sensorJson2["loc"] = "BUILDING_01__FLOOR_02__ROOM_03";
    string rawMessage3 = sensorJson2.dump();
    sensor.SendTo(rawMessage3); //sensor sends an event for publishing

    string receivedData;
    sprinkler.ReceiveFrom(receivedData); //subscribed sprinkler receives the event data 
    std::cout << "Sprinkler: " << receivedData << std::endl;

    ASSERT_PASS();
}
END_TEST


BEGIN_SUITE(不耻下问)

TEST(simple_test_publish_event)

END_SUITE
