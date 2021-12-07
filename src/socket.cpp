#include <errno.h> //perror
#include <sys/socket.h> //send
#include <unistd.h> //close
#include "socket.hpp" //Socket header


namespace advcpp
{

Socket::Socket(int a_socketDescriptor)
: m_socketDescriptor(a_socketDescriptor) {}


Socket::Socket()
: m_socketDescriptor(0) {}


int Socket::Send(string a_message) const
{
    int dataLen = a_message.length();
    int sentBytes = send(m_socketDescriptor, a_message.data(), dataLen, 0);

    if(sentBytes < 0)
    {
        if(errno != EAGAIN && errno != EWOULDBLOCK) // if failed due to real error
        { 
            return 0;
        }
    }
    
    return sentBytes;    
}

int Socket::Receive(std::string& a_receivedData) const
{
    char buffer[4096] = {0};
    int expectedDataLen = sizeof(buffer);

    int readBytes = recv(m_socketDescriptor, buffer, expectedDataLen, 0);
    if(0 == readBytes) // client closed the connection
    { 
        close(m_socketDescriptor);
        return 0;
    }

    a_receivedData = buffer;
    return readBytes;
}

int Socket::GetDescriptor() const
{
    return m_socketDescriptor;
}

bool Socket::operator==(int a_otherSocket) const
{
    return a_otherSocket == m_socketDescriptor;
}

bool Socket::operator!=(int a_otherSocket) const
{
    return a_otherSocket != m_socketDescriptor;
}

}

