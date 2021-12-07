#ifndef HARDWARE_CLIENT_HPP_
#define HARDWARE_CLIENT_HPP_
#include <string> //std::string


namespace advcpp
{

// For local host use ip address: 127.0.0.1
// And socket file descriptor 1025
using std::string;
class HardwareClient
{
public:
    //ctor 
    HardwareClient(int a_connectToFileDescriptor, const char* a_iPaddress);

    //functions
    int SendTo(std::string a_message) const;
    int SendCloseRequest() const;
    int ReceiveFrom(string& a_receivedData) const;

private:
    int m_socket;
};

}


#endif //HARDWARE_CLIENT_HPP_