#ifndef THREAD_HPP_
#define THREAD_HPP_
#include "callable.hpp" //Callable header
#include "semaphore.hpp" //Semaphore header
#include "sync_point.hpp" //SyncPoint header
#include "atomic_value.hpp" //AtomicValue header
#include <pthread.h> //thread functions
#include <unistd.h> //sleep
#include <memory> //shared_ptr
#include <string> //std::string
#include <cassert> //assert


namespace advcpp
{

// Policys fwd declaration to be invoked in thred's dtor
struct JoinPolicy;
struct DetachPolicy;
struct CancelPolicy;
struct AssersionPolicy;

template <typename Policy>
class Thread
{
public:
    //ctor, dtor
    explicit Thread(std::shared_ptr<Callable> a_command);
    ~Thread();

    //avoid using
    Thread() = delete;
    Thread(const Thread& a_other) = delete;
    Thread& operator=(const Thread&) = delete;

    //class methods
    void Join();
    void Detach();
    void Cancel();
    bool IsDone() const;
    bool IsJoined() const;
    bool IsDetached() const;
    bool IsCanceled() const;

private:
    static void* ActionFunc(void* a_arg);

private:
    std::shared_ptr<Callable> m_command;
    std::shared_ptr<SyncPoint> m_syncPointPtr;
    pthread_t m_thread;
    Semaphore m_semaphore;
    AtomicValue<bool> m_threadCanceled;
    AtomicValue<bool> m_threadJoind;
    AtomicValue<bool> m_threadDetached;
    AtomicValue<bool> m_alraedyStartedPolicy;
};


// Policys
struct JoinPolicy
{
    void operator()(Thread<JoinPolicy>& a_thread)
    {
        a_thread.Join();
    }
};

struct DetachPolicy
{
    void operator()(Thread<DetachPolicy>& a_thread)
    {
        a_thread.Detach();
    }
};

struct CancelPolicy
{
    void operator()(Thread<CancelPolicy>& a_thread)
    {
        a_thread.Cancel();
    }
};

struct AssersionPolicy
{
    void operator()(Thread<AssersionPolicy>& a_thread)
    {
        assert(a_thread.IsJoined() || a_thread.IsDetached() || a_thread.IsCanceled());
    }
};

}


#include "thread.hxx"
#endif // THREAD_HPP_

