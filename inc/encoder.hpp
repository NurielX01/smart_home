#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_
#include "event.hpp" //EventHeader
#include <string> //std::string


namespace advcpp
{

using std::string;
struct Encoder
{
    Encoder() = default;
    string Encode(Event a_event) const;
};

}


#endif // _ENCODER_HPP_