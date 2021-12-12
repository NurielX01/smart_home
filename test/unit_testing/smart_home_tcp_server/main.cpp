#include "mu_test.h"
#include "server_socket.hpp" //ServerSocket header
#include "socket.hpp" //socket header
#include "selector.hpp" //Selector header
// #include "json.hpp" // json
// using json = nlohmann::json; // json
using namespace advcpp;


BEGIN_TEST(simple_test_listen_accept_receive_message)
{
    ServerSocket server;
    server.Listen(2);
    auto clientSock =  server.Accept();
    
    Socket clientSocket(clientSock);
    clientSocket.Send("connection successfull");

    string receivedData;
    clientSocket.Receive(receivedData);

    std::cout << receivedData << std::endl;

    ASSERT_PASS();
}
END_TEST


BEGIN_SUITE(不耻下问)


TEST(simple_test_listen_accept_receive_message)


END_SUITE
