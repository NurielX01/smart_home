#include "task_event_routing.hpp" //TaskEventRouting header


namespace advcpp
{

TaskEventRouting::TaskEventRouting(Event& a_event, Server* a_server)
: m_event(a_event)
, m_server(a_server){}

void TaskEventRouting::Execute()
{
    m_server->RouteEvent(m_event);
}

}
