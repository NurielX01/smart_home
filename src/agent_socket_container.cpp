#include "agent_socket_container.hpp" //AgentSocketContainer header
#include "agent.hpp" //Agent header


namespace advcpp
{

AgentSocketContainer::AgentSocketContainer(vector<Agent*>& a_agentList)
{
    size_t agentAmount = a_agentList.size();
    for(size_t i = 0 ; i < agentAmount ; ++i)
    {
        auto p = pair<Agent*, int>(a_agentList[i], 0);
        m_container.push_back(p);
    }
}

bool AgentSocketContainer::Add(string a_agentId, int a_socket)
{
    size_t amount = m_container.size();
    for(size_t i = 0 ; i < amount ; ++i)
    {
        auto id = m_container[i].first->GetId();
        if(id == a_agentId)
        {
            auto& socket = m_container[i].second;
            socket = a_socket;
            return true;
        }
    }

    return false;
}

int AgentSocketContainer::GetSock(string a_agentId) const
{
    auto amount = m_container.size();
    for(size_t i = 0 ; i < amount ; ++i)
    {
        auto id = m_container[i].first->GetId();
        if(id == a_agentId)
        {
            return m_container[i].second;
        }
    }

    return -1;
}

Agent* AgentSocketContainer::FindAgent(int a_socket)
{
    auto amount = m_container.size();
    for(size_t i = 0 ; i < amount ; ++i)
    {
        auto agentSock = m_container[i].second;
        if(a_socket == agentSock)
        {
            return m_container[i].first;
        }
    }

    int e = 0;
    throw e;
}

}

