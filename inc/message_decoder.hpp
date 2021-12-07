#ifndef MESSAGE_DECODER_HPP_
#define MESSAGE_DECODER_HPP_
#include "json.hpp" //json


namespace advcpp
{

using json = nlohmann::json;
using std::string;
using std::vector;
class MessageDecoder
{
public:
    // ctor, dtor
    MessageDecoder(string a_rawMessage);
    ~MessageDecoder() = default;
    
    // class methods
    json Decode() const;
    int MessageSize() const;

    // class templated methods
    template<typename T>
    T FindInMessage(string a_indexName) const;

private:
    json m_message;
};

template<typename T>
T MessageDecoder::FindInMessage(string a_indexName) const
{
    auto result = m_message.find(a_indexName);
    return result->get<T>();
}

}


#endif // MESSAGE_DECODER_HPP_