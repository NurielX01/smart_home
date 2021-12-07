#ifndef GROUP_THREAD_HPP_
#define GROUP_THREAD_HPP_
#include <vector> //std::vector
#include <memory> //std::shared_pointer
#include "callable.hpp" //Callable header
#include "thread.hpp" //Thread header


namespace advcpp
{

template<typename Policy>
class GroupThread
{
public:
    //ctor, dtor
    GroupThread(std::shared_ptr<Callable> a_command, size_t a_threadAmount);
    ~GroupThread() = default;

    //avoid using
    GroupThread(const GroupThread& a_other) = delete;
    GroupThread& operator=(const GroupThread& a_other) = delete;

    //public methods
    size_t Add(size_t a_thisAmount); //returning the amount actually added
    size_t Remove(size_t a_thisMuchThreads);
    size_t HowManyAtWork();
    size_t HowManyInTotal();

private:
    std::shared_ptr<Callable> m_command;
    std::vector<std::shared_ptr<Thread<Policy>>> m_threadContainer;
};

}


#include "group_thread.hxx"
#endif //GROUP_THREAD_HPP_
