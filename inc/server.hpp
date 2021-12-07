#ifndef SERVER_HPP_
#define SERVER_HPP_
#include "thread_pool.hpp" //ThreadPool header
#include "subscribers.hpp" //Subscribers header
#include "event.hpp" //Event header
#include "event_id.hpp" //EventId header
#include <cstddef> //size_t
#include <vector> //std::vector
#include <map> //std::map


namespace advcpp
{

using std::vector;
using std::map;
class MessageHandler;
class Agent;
class Server
{
public:
    // ctor, dtor
    Server(size_t a_eventsCapacity, int a_clientCapacity, size_t a_numThreads);
    ~Server();

    // prevent using
    Server(const Server& a_other) = delete;
    Server& operator=(const Server& a_other) = delete;

    // class methods
    void RouteEvent(Event a_event);
    bool AddEvent(std::shared_ptr<Callable> a_taskEventRouting);
    ThreadPool& GetThreadPool();
    vector<Agent*>& GetAgents();

private:
    vector<Agent*> CreateAgents(); //TODO - complete creating agents from .ini and use dynamic library
    void SubscribeAgents();

private:
    vector<Agent*> m_agentsContainer;
    Subscribers m_subscribers; 
    ThreadPool m_eventsTp;
    MessageHandler* m_handler;
};

}


#endif //SERVER_HPP_
