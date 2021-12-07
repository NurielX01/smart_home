#include "message_decoder.hpp" //MessageDecoder header
#include <iostream> //std::cout


namespace advcpp
{

MessageDecoder::MessageDecoder(string a_rawMessage)
{
    try
    {
        m_message = json::parse(a_rawMessage.data());
    }
    catch(...)
    {
        json j;
        j["size"] = 20;
        j["op"] = 'f'; 
        m_message = j;
    }
}

json MessageDecoder::Decode() const
{
    return m_message;
}

int MessageDecoder::MessageSize() const
{
    auto result = m_message.find("size");
    auto getResult = result->get<int>();
    std::cout << getResult << std::endl;
    return getResult;
}

}

