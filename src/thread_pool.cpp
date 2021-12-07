#include <vector> //std::vector
#include "thread_pool.hpp" //thread_pool header
#include "void_method_void_adapt.hpp" //VoidMethodVoidAdapter header


namespace advcpp
{

using std::make_shared;
using Adapter = VoidMethodVoidAdapt<ThreadPool&, void(ThreadPool::*)()>;

//ctor, dtor
ThreadPool::ThreadPool(size_t a_queueCapacity, size_t a_numThreads)
: m_tasksQueue(a_queueCapacity)
, m_groupThread(make_shared<Adapter>(*this, &ThreadPool::RunCallable), a_numThreads) {}

ThreadPool::~ThreadPool()
{
    ShutDownImmediately();
}


//public methods
size_t ThreadPool::RemoveThreads(size_t a_numThreads)
{
    MutexGuard removeThreadsMutex;
    return m_groupThread.Remove(a_numThreads);
}

bool ThreadPool::Submit(std::shared_ptr<Callable> a_task)
{ 
    MutexGuard doTaskMutex;

    if(m_shutDown.IsOn())
    {
        return false; // thread pool is in shut down, will not add additional tasks
    }

    return m_tasksQueue.Enqueue(a_task, false);
}

void ThreadPool::ShutDown()
{
    MutexGuard shutDownMutex;
    m_shutDown.Set();

    size_t workingThreads = m_groupThread.HowManyAtWork();
    
    for(size_t i = 0 ; i < workingThreads ; ++i)
    {
        auto killTask = std::make_shared<KillThreadTask>();
        m_tasksQueue.Enqueue(killTask, false);
    }

    while(0 < NumCurrentTasks());
    auto result = m_groupThread.HowManyInTotal();
    m_groupThread.Remove(result);
}

void ThreadPool::ShutDownImmediately()
{
    MutexGuard shutDownImmediatelyMutex;
    
    m_shutDown.Set();

    size_t workingThreads = m_groupThread.HowManyAtWork();

    for(size_t i = 0 ; i < workingThreads ; ++i)
    {
        auto killTask = std::make_shared<KillThreadTask>();
        m_tasksQueue.Enqueue(killTask, true);
    }

    while(0 < NumCurrentThreads()); //TODO - find more efficient way
}

size_t ThreadPool::NumCurrentTasks() const
{
    MutexGuard NumCurrentTasksMutex;
    return m_tasksQueue.GetSize();
}

size_t ThreadPool::NumCurrentThreads()
{
    MutexGuard NumCurrentThreadsMutex;
    return m_groupThread.HowManyAtWork();
}

void ThreadPool::addThreads(size_t a_numThreads)
{
    MutexGuard addThreadsMutex;
    try
    {
        m_groupThread.Add(a_numThreads);
    }
    catch(...)
    {
        throw;
    }
}


//private methods
void ThreadPool::RunCallable()
{
    while(true)
    {
        try
        {   
            if(DoTask())
            {
                break;
            }
        }
        catch(...)
        {
            //TODO - write to log
        }
    }    
}

bool ThreadPool::DoTask()
{
    std::shared_ptr<Callable> nextTask;
    try
    {
        if(m_tasksQueue.Dequeue(nextTask))
        {
            nextTask->Execute();
        }
    }
    catch(const Poison& p)
    {   
        return true;
    }
    catch(...)
    {
        throw;
    }

    return false;
}


// inner class KillThreadTask
void ThreadPool::KillThreadTask::Execute()
{
    ThreadPool::Poison p;
    throw p;
}


}

