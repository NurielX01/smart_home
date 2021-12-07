#include <algorithm> //std::find
#include "socket_container.hpp" //SocketContainer header


namespace advcpp
{
    
SocketContainer::SocketContainer(size_t a_capacity)
: m_capacity(a_capacity)
{
    m_socketContainer.reserve(a_capacity);
}

int SocketContainer::GetCapacity() const
{
    return m_capacity;
}

void SocketContainer::Add(int a_socket)
{
    Socket clientSocket(a_socket);
    clientSocket.Send("connection successfull");
    m_socketContainer.emplace_back(Socket(a_socket));
}

void SocketContainer::Remove(int a_socket)
{
    std::remove(m_socketContainer.begin(), m_socketContainer.end(), a_socket);
}

bool SocketContainer::Find(int a_socket, Socket& a_resultSocket)
{
    auto result = std::find(m_socketContainer.begin(), m_socketContainer.end(), a_socket);
    if(m_socketContainer.end() == result)
    {
        return false;
    }

    a_resultSocket = *result;
    return true;
}

}

