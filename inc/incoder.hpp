#ifndef INCODER_HPP_
#define INCODER_HPP_
#include "event.hpp" //EventHeader
#include <string> //std::string


namespace advcpp
{

using std::string;
struct Incoder
{
    Incoder() = default;
    string Incode(Event a_event) const;
};

}


#endif // INCODER_HPP_