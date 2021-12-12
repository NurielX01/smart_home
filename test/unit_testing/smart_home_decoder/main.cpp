#include "mu_test.h"
#include "message_decoder.hpp" //MessageDecoder header
#include "json.hpp" //json header
#include <string> //String header
#include <iostream>


using namespace advcpp;


BEGIN_TEST(decoder_simple_test)
{
    json j;
    
    j["a"] = 12; 
    j["b"] = "c";
    j["c"] = "smoke_dt133";

    auto rawMessage = j.dump();

    MessageDecoder decoder(rawMessage);
    auto vec = decoder.Decode();

    ASSERT_EQUAL(vec[0], "c");
    ASSERT_EQUAL(vec[1], "smoke_dt133");
    ASSERT_EQUAL(decoder.MessageSize(), 12);
    
}
END_TEST


BEGIN_SUITE(不耻下问)
    

TEST(decoder_simple_test)


END_SUITE
