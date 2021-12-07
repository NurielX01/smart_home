#ifndef SELECTOR_HPP_
#define SELECTOR_HPP_
#include "socket_container.hpp" //SocketContainer header
#include "message_handler.hpp" //MessageHandler header


namespace advcpp
{

class Selector
{
public:
    // ctor, dtor
    Selector(SocketContainer* a_socketContainer, MessageHandler* a_messageHandler);
    ~Selector() = default;

private:
    SocketContainer* m_socketContainer;
    MessageHandler* m_messageHandler;
};

}


#endif //SELECTOR_HPP_