#include <iostream> //std::cerr
#include <algorithm> //std::for_each
#include "group_thread.hpp" //GroupThread header
#include "mutex_guard.hpp" //MutexGuard header


namespace advcpp
{

template<typename Policy>
GroupThread<Policy>::GroupThread(std::shared_ptr<Callable> a_command, size_t a_threadAmount)
: m_command(a_command)
{
    m_threadContainer.reserve(a_threadAmount);
    if(a_threadAmount != Add(a_threadAmount))
    {
        throw std::runtime_error("GroupThread ctor failed to add all threads");
    }
}

template<typename Policy>
size_t GroupThread<Policy>::Add(size_t a_thisAmount)
{   
    size_t actuallyAdded = 0;
    MutexGuard addMutex;

    for(size_t i = 0 ; i < a_thisAmount ; ++i)
    {
        try
        {
            actuallyAdded++;
            m_threadContainer.emplace_back(std::make_shared<Thread<Policy>>(m_command));
        }
        catch(...)
        {
            actuallyAdded--;  
        }
    }
    return actuallyAdded;
} 

template<typename Policy>
size_t GroupThread<Policy>::Remove(size_t a_thisMuchThreads)
{   
    MutexGuard removeMutex;
    size_t oldAmount = m_threadContainer.size();

    auto begin = m_threadContainer.begin();
    auto end = m_threadContainer.end();

    auto newEnd = std::remove_if(begin, end, [](std::shared_ptr<Thread<Policy>> a_currentThreadPtr) {return a_currentThreadPtr->IsDone();});
    m_threadContainer.erase(newEnd, end);

    auto actuallyRemoved = oldAmount - m_threadContainer.size();
    if(actuallyRemoved >= a_thisMuchThreads)
    {
        return actuallyRemoved;
    }

    auto leftToRemove = a_thisMuchThreads - actuallyRemoved;
    while(begin != (begin + leftToRemove) && begin != newEnd )
    {
        begin->get()->Cancel();
    }

    return a_thisMuchThreads;
}

template<typename Policy>
size_t GroupThread<Policy>::HowManyAtWork()
{   
    MutexGuard howManyWorkingMutex;
    auto begin = m_threadContainer.begin();
    auto end = m_threadContainer.end();
    return std::count_if(begin, end, [](std::shared_ptr<Thread<Policy>> a_currentThreadPtr) {return !a_currentThreadPtr->IsDone();});
}

template<typename Policy>
size_t GroupThread<Policy>::HowManyInTotal()
{
    MutexGuard howManyMutex;
    return m_threadContainer.size();
}

}

