#ifndef SERVER_SOCKET_HPP_
#define SERVER_SOCKET_HPP_


// TODO - change all throws to errno / perror 
namespace advcpp
{
    
class ServerSocket
{
public:
    // ctor, dtor
    ServerSocket();
    ~ServerSocket() = default;

    // class methods
    void Listen(int a_capacity) const;
    int Accept() const;
    int GetSocket() const;

private:
    int m_serverSocketDescriptor;

};

}


#endif //SERVER_SOCKET_HPP_