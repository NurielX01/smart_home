#ifndef AGENT_SOCKET_CONTAINER_HPP_
#define AGENT_SOCKET_CONTAINER_HPP_
#include <utility> // std::pair
#include <vector> //std::vector
#include <string> //std::string


namespace advcpp
{

class Agent;
using std::pair;
using std::string;
using std::vector;

class AgentSocketContainer
{
public:
    //ctor, dtor
    explicit AgentSocketContainer(vector<Agent*>& a_agentList);
    ~AgentSocketContainer() = default;

    //class methods
    bool Add(string a_agentId, int a_socket);
    Agent* FindAgent(int a_socket);
    int GetSock(string a_agentId) const;

private:
    vector<pair<Agent*, int>> m_container;
};

}


#endif // AGENT_SOCKET_CONTAINER_HPP_