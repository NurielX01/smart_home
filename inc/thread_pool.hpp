#ifndef THREAD_POOL_HPP_
#define THREAD_POOL_HPP_
#include <cstddef> //size_t
#include <memory> //std::shared_ptr
#include "block_bounded_q.hpp" //BlockBoundedQ header
#include "callable.hpp" //Callable header
#include "group_thread.hpp" //GroupThread header
#include "mutex_guard.hpp" //MutexGuard header


namespace advcpp
{

//TODO - template this class to use any type of queue requested (example cyclic queue);
//TODO - write queue requirements
class ThreadPool
{       
public:
    // TODO LATER - add default values to ctor - amount of threads
    // as the amount of cores (calc by function)
    ThreadPool(size_t a_queueCapacity, size_t a_numThreads);
    ~ThreadPool();

    bool Submit(std::shared_ptr<Callable> a_task);
    void addThreads(size_t a_numThreads);
    size_t RemoveThreads(size_t a_numThreads);
    void ShutDown();
    void ShutDownImmediately();

    size_t NumCurrentTasks() const;
    size_t NumCurrentThreads();

private:
    struct Poison
    {
        Poison() = default;
    };

    struct KillThreadTask : public Callable
    {
        KillThreadTask() = default;
        void Execute() override;
    };

private:
    void RunCallable();
    bool DoTask();

private:
    AtomicValue<bool> m_shutDown;
    BlockBoundedQ<std::shared_ptr<Callable>> m_tasksQueue;
    GroupThread<JoinPolicy> m_groupThread;
};

}


#endif //THREAD_POOL_HPP_