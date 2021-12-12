#include <cassert> //assert
#include <iostream> //std::cerr


namespace advcpp
{

template <typename Policy>
Thread<Policy>::Thread(std::shared_ptr<Callable> a_command)
: m_command(a_command)
, m_syncPointPtr(std::make_shared<SyncPoint>())
, m_semaphore(0, 0)
{
    assert(0 != a_command.get());
    int result = pthread_create(&m_thread, NULL, ActionFunc, this);
    if(result != 0) {
        throw std::runtime_error("pthread_create failed");
    }

    m_semaphore.Wait();
}

template <typename Policy>
Thread<Policy>::~Thread()
{   
    Policy()(*this);
}

template <typename Policy>
void* Thread<Policy>::ActionFunc(void* a_arg)
{
    assert(0 != a_arg);

    Thread* currentTheread = static_cast<Thread*>(a_arg);
    std::shared_ptr<Callable> freshCommand = currentTheread->m_command;
    std::shared_ptr<SyncPoint> syncPointPtr = currentTheread->m_syncPointPtr;

    currentTheread->m_semaphore.Post();
    try
    {
        freshCommand->Execute();
    }
    catch(const std::exception& e)
    {
        syncPointPtr->SetException(std::current_exception()); //catch exception and store it in shared SyncPoint ptr
    }
    syncPointPtr->SetFlag();
    
    return 0;
}

template <typename Policy>
void Thread<Policy>::Join() {
    if(!m_alraedyStartedPolicy.IsOn()) //checking if already started any kind of policy
    {   
        m_alraedyStartedPolicy.Set();
        if(!m_threadJoind.IsOn() && !m_threadDetached.IsOn())
        {
            int result = pthread_join(m_thread, 0);
            if(result != 0) {
                throw std::runtime_error("pthread_join had failed");
            }
            m_threadJoind.Set();
        }
        else
        {
            throw std::runtime_error("thread already assigned join policy");
        }
    }
}

template <typename Policy>
void Thread<Policy>::Detach()
{
    if(!m_alraedyStartedPolicy.TrySet())
    {
        return;
    }

    if(!m_threadDetached.IsOn() && !m_threadJoind.IsOn())
    {
        int result = pthread_detach(m_thread);
        if(result != 0)
        {
            throw std::runtime_error("pthread_detach had failed");
        }
        m_threadDetached.Set();
    }
    else
    {
        throw std::runtime_error("thread already assigned with detach policy");
    }
}

template <typename Policy>
void Thread<Policy>::Cancel()
{
    if(m_threadCanceled.IsOn())
    {
        return;
    }
    
    int result = pthread_cancel(m_thread);
    if(result != 0)
    {
        throw std::runtime_error("pthread_cancel had failed");
    }

    m_threadCanceled.Set();
    if(!m_threadJoind.IsOn())
    {
        Join();
    }
}

// If an exception was thrown during secondary thread execution, it will be stored at the shared SyncPoint object,
// And will be thrown to the user once IsDone() is provoked.
template <typename Policy>
bool Thread<Policy>::IsDone() const
{   
    return m_syncPointPtr->GetFlag();
}

template <typename Policy>
bool Thread<Policy>::IsJoined() const
{
    return m_threadJoind.IsOn();
}

template <typename Policy>
bool Thread<Policy>::IsDetached() const
{
    return m_threadDetached.IsOn();
}

template <typename Policy>
bool Thread<Policy>::IsCanceled() const
{
    return m_threadCanceled.IsOn();
}


}

