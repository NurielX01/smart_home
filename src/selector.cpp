#include <sys/select.h> //select
#include <stdio.h> // perror
#include <stdlib.h> //exit
#include <errno.h> //errno
#include <iostream> //styd::cout
#include "selector.hpp" //Selector header
#include "server_socket.hpp" //ServerSocket header
#include "socket.hpp" //Socket header


namespace advcpp
{

Selector::Selector(SocketContainer* a_socketContainer, MessageHandler* a_messageHandler)
: m_socketContainer(a_socketContainer)
, m_messageHandler(a_messageHandler)
{
    ServerSocket serverSocket;
    fd_set currentSockets, readySockets;
    serverSocket.Listen(m_socketContainer->GetCapacity());

    FD_ZERO(&currentSockets);

    auto serverSocketDescriptor = serverSocket.GetSocket();
    FD_SET(serverSocketDescriptor, &currentSockets);

    while(true)
    {
        readySockets = currentSockets;
        if(0 > select(FD_SETSIZE, &readySockets, nullptr, nullptr, nullptr))
        {
            throw errno; //TODO - "try catch" this exception in server_tcp.cpp
            exit(EXIT_FAILURE);
        }

        for(int i = 0 ; i < FD_SETSIZE ; ++i)
        {
            if(FD_ISSET(i, &readySockets))
            {
                if(i == serverSocketDescriptor) // new connection
                {
                    int receivedSocket = serverSocket.Accept();
                    m_socketContainer->Add(receivedSocket);
                    FD_SET(receivedSocket, &currentSockets);
                    std::cout << "selector: new client accepted - soc " << receivedSocket << std::endl;
                }

                // TODO - move the whole bottom section to the handler
                //message from a client socket

                else 
                {
                    Socket clientSocket;
                    auto wasFound = m_socketContainer->Find(i, clientSocket);
                    if(!wasFound)
                    {
                        FD_CLR(i, &currentSockets);
                        continue;
                    }

                    std::cout << "selector: message received from soc: " << clientSocket.GetDescriptor() << std::endl;

                    string message;
                    if(0 == clientSocket.Receive(message))
                    {
                        std::cout << "selector: message received is empty" << std::endl;
                        m_socketContainer->Remove(i);
                        FD_CLR(i, &currentSockets);
                    }

                    auto result = m_messageHandler->Handle(message, i);

                    if(!result)
                    {
                        m_socketContainer->Remove(i);
                        FD_CLR(i, &currentSockets);
                    }
                }
            }
        }
    }
}
 
}

