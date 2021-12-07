#ifndef SOCKET_CONTAINER_HPP_
#define SOCKET_CONTAINER_HPP_
#include <vector> //std::vector
#include "socket.hpp" //Socket header


namespace advcpp
{

using std::vector;
class SocketContainer
{
public:
    // ctor, dtor
    explicit SocketContainer(size_t a_capacity);
    ~SocketContainer() = default;

    // class methods
    void Add(int a_socket);
    void Remove(int a_socket);
    bool Find(int a_socket, Socket& a_resultSocket);
    int GetCapacity() const;

private:
    int m_capacity;
    vector<Socket> m_socketContainer;
};

}


#endif //SOCKET_CONTAINER_HPP_