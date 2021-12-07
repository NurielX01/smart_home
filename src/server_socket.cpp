#include <netinet/in.h> //socket
#include <sys/socket.h> //socket, bind
#include <string.h> //memset
#include <arpa/inet.h> //htons
#include <fcntl.h> //no blocking
#include <unistd.h> //no blocking
#include <stdexcept> //std::runtime_error
#include "server_socket.hpp" //ServerSocket header


namespace advcpp
{

ServerSocket::ServerSocket()
: m_serverSocketDescriptor(socket(AF_INET, SOCK_STREAM, 0))  /* IPV4 with TCP Protocol*/
{
    if(0 > m_serverSocketDescriptor)
    {
        throw std::runtime_error("socket(...) had failed");
    }

    int optval = 1; 

    if(0 > setsockopt(m_serverSocketDescriptor, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))) // if port closed - imidiate return the port to the pull
    { 
        throw std::runtime_error("setsockopt(...) had failed");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(1025); // 1025 - port descriptor

    if(0 > bind(m_serverSocketDescriptor, (struct sockaddr*)&sin, sizeof(sin))) // reserve port and IP to the server
    { 
        throw std::runtime_error("bind(...) had failed");
    }
}

int ServerSocket::Accept() const
{
    struct sockaddr_in clientSin;
    socklen_t addrLen = sizeof(clientSin);
    auto clientSocketDescriptor = accept(m_serverSocketDescriptor, (struct sockaddr*)&clientSin, &addrLen);
    
    if(0 > clientSocketDescriptor)
    {
        throw std::runtime_error("accept(...) had failed");
    }

    return clientSocketDescriptor;
}

void ServerSocket::Listen(int a_capacity) const
{
    if(0 > listen(m_serverSocketDescriptor, a_capacity)) // set socket to listener
    {  
        throw std::runtime_error("listen(...) had failed");
    }
}

int ServerSocket::GetSocket() const
{
    return m_serverSocketDescriptor;
}

}

