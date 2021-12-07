#ifndef TASK_EVENT_ROUTING_HPP_
#define TASK_EVENT_ROUTING_HPP_
#include "event.hpp" //Event header
#include "server.hpp" //Server header
#include "callable.hpp" //Callable header


namespace advcpp
{
    
class TaskEventRouting : public Callable
{
public:
    TaskEventRouting(Event& a_event, Server* a_server);
    ~TaskEventRouting() = default;
    void Execute();

private:
    Event m_event;
    Server* m_server;
};

}


#endif // TASK_EVENT_ROUTING_HPP_
