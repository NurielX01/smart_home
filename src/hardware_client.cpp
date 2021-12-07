#include <string.h> //memset
#include <sys/socket.h> //socket, bind
#include <arpa/inet.h> //htons
#include <stdexcept> //std::runtime_error
#include "hardware_client.hpp" //hardware_client header


namespace advcpp
{

// ctor
HardwareClient::HardwareClient(int a_connectToFileDescriptor, const char* a_iPaddress)
: m_socket(socket(AF_INET, SOCK_STREAM, 0)) // IPV4 with TCP Protocol
{ 
    if(m_socket < 0)
    {
        throw std::runtime_error("client socket had failed");
    }
    
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(a_iPaddress);
    sin.sin_port = htons(a_connectToFileDescriptor); // 1025

    if(connect(m_socket, (struct sockaddr*)&sin, sizeof(sin)) < 0)
    {
        throw std::runtime_error("client connect had failed");
    }
}

// methods
int HardwareClient::SendTo(std::string a_message) const
{
    int sentBytes = send(m_socket, a_message.data(), a_message.length(), 0);
    if(sentBytes < 0)
    {
        throw std::runtime_error("client send had failed");
    }

    return sentBytes;
}

int HardwareClient::SendCloseRequest() const
{
    std::string dataAddr = 0;

    int sentBytes = send(m_socket, dataAddr.data(), dataAddr.length(), 0);
    if(sentBytes < 0)
    {
        throw std::runtime_error("client send close request had failed");
    }

    return sentBytes;
}

int HardwareClient::ReceiveFrom(string& a_receivedData) const
{
    int expectedDataLen = 4096;
    char receivedData[4096];

    int readBytes = recv(m_socket, &receivedData, expectedDataLen, 0);

    if(readBytes < 0)
    {
        throw std::runtime_error("client recv had failed");
    }

    a_receivedData = receivedData;

    return readBytes;
}

}

