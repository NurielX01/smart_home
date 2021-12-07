#ifndef SOCKET_HPP_
#define SOCKET_HPP_
#include <string> //std::string


namespace advcpp // TODO - change all throws to errno / perror 
{
    
using std::string;
class Socket
{
public:
    // ctor, dtor
    explicit Socket(int a_socketDescriptor);
    ~Socket() = default;
    Socket();

    // class methods
    int Send(string a_message) const;
    int Receive(string& a_receivedData) const;
    int GetDescriptor() const;

    // class operators
    bool operator==(int a_otherSocket) const;
    bool operator!=(int a_otherSocket) const;

private:
    int m_socketDescriptor;

};

} 


#endif //SOCKET_HPP_