#include "mu_test.h"
#include "thread_pool.hpp" //ThreadPool header
#include "semaphore.hpp" //Semaphore header
#include <memory> //std::shared_ptr, std::make_shared


using namespace advcpp;


class ReportingTasks : public Callable
{
public:
    virtual bool IsDone() = 0;
};


class Task : public ReportingTasks
{
    Semaphore semaphore;
public:
    bool IsDone()
    {
        semaphore.Wait();
        return true;
    }

    void Execute()
    {
        semaphore.Post();
    }
};


class TaskThrowsException : public ReportingTasks
{
    Semaphore semaphore;
public:
    bool IsDone()
    {
        semaphore.Wait();
        return true;
    }

    void Execute()
    {
        semaphore.Post();
        throw std::runtime_error("Task throws exception");
    }   
};


class Consume : public Callable
{
    Semaphore semaphore;
public:
    bool IsDone()
    {
        semaphore.Wait();
        return true;
    }

    void Execute()
    {
        semaphore.Post();
    }     
};


class TaskCount : public Callable
{
    Semaphore semaphore;
public:
    bool IsDone()
    {
        semaphore.Wait();
        return true;
    }

    int GetCount()
    {
        return m_count;
    }

    void Execute()
    {
        semaphore.Post();
        ++m_count;
    }
private:
    int m_count = 0;
};


const int cap = 42;
ThreadPool fixedPool(cap, 1);
BEGIN_TEST(tp_basic_submit_test)
{
    std::shared_ptr<Task> task (new Task());
    fixedPool.Submit(task);

    ASSERT_THAT(task->IsDone());
    ASSERT_EQUAL(fixedPool.NumCurrentTasks(), 0);
}
END_TEST


ThreadPool fixedPool2(cap, 1);
BEGIN_TEST(tp_basic_submit_check_throw_test)
{
    std::shared_ptr<TaskThrowsException> task(new TaskThrowsException());
    fixedPool2.Submit(task);
    
    ASSERT_THAT(task->IsDone());
    ASSERT_EQUAL(fixedPool2.NumCurrentTasks(), 0);
    ASSERT_EQUAL(fixedPool2.NumCurrentThreads(), 1);
}
END_TEST

ThreadPool fixedPool3(cap, 1);
BEGIN_TEST(tp_run_normal_tasks_after_exception_task)
{
    std::shared_ptr<TaskThrowsException> task1(new TaskThrowsException());
    std::shared_ptr<Task> task2(new Task());

    fixedPool3.Submit(task1);
    fixedPool3.Submit(task2);

    ASSERT_THAT(task1->IsDone());
    ASSERT_THAT(task2->IsDone());
    
    ASSERT_EQUAL(fixedPool3.NumCurrentThreads(), 1);
    ASSERT_EQUAL(fixedPool3.NumCurrentTasks(), 0);
}
END_TEST


ThreadPool fixedPool4(cap, 1);
BEGIN_TEST(tp_run_many_tasks)
{
    using std::vector;
    using std::shared_ptr;

    vector<shared_ptr<ReportingTasks>> tasks;
    const int ntasks = cap * 2;
    tasks.reserve(ntasks);

    for(int i = 0; i < ntasks ; ++i)
    {
        tasks.emplace_back(new Task());
        fixedPool4.Submit(tasks.back());
    }

    for(int i = 0 ; i < ntasks ; ++i)
    {
        ASSERT_THAT(tasks[i]->IsDone());
    }

    ASSERT_EQUAL(fixedPool4.NumCurrentTasks(), 0);
    ASSERT_EQUAL(fixedPool4.NumCurrentThreads(), 1);
}
END_TEST

ThreadPool fixedPool5(cap, 0);
BEGIN_TEST(tp_add_thread_to_no_thread_tp)
{
    ASSERT_EQUAL(fixedPool5.NumCurrentThreads(), 0);
    ASSERT_EQUAL(fixedPool5.NumCurrentTasks(), 0);

    std::shared_ptr<Task> task(new Task());
    fixedPool5.Submit(task);

    ASSERT_EQUAL(fixedPool5.NumCurrentThreads(), 0);
    ASSERT_EQUAL(fixedPool5.NumCurrentTasks(),1);

    fixedPool5.addThreads(1);

    ASSERT_THAT(task->IsDone());
    ASSERT_EQUAL(fixedPool5.NumCurrentTasks(), 0);
    ASSERT_EQUAL(fixedPool5.NumCurrentThreads(), 1);
}
END_TEST


BEGIN_TEST(tp_shut_down_single_thread_test)
{
    ThreadPool fixedPool6(cap, 0);
    std::shared_ptr<Task> task(new Task());
    
    fixedPool6.Submit(task);
    fixedPool6.addThreads(1);

    ASSERT_THAT(task->IsDone());
    ASSERT_EQUAL(fixedPool6.NumCurrentTasks(), 0);
    ASSERT_EQUAL(fixedPool6.NumCurrentThreads(), 1);
    
    fixedPool6.ShutDown();
    ASSERT_EQUAL(fixedPool6.NumCurrentTasks(), 1);
}
END_TEST


BEGIN_TEST(tp_shut_down_single_thread_multiple_tasks_test)
{
    using std::vector;
    using std::shared_ptr;

    ThreadPool fixedPool(cap,1);
    vector<shared_ptr<Task>> tasks;
    const int ntasks = cap * 2;
    tasks.reserve(ntasks);

    for(int i = 0; i < ntasks ; ++i)
    {
        tasks.emplace_back(new Task());
        fixedPool.Submit(tasks.back());
    }

    for(int i = 0 ; i < ntasks ; ++i)
    {
        ASSERT_THAT(tasks[i]->IsDone());
    }

    fixedPool.ShutDown();
    ASSERT_EQUAL(fixedPool.NumCurrentTasks(), 0);
}
END_TEST


BEGIN_TEST(tp_shut_down_multiple_threads_and_tasks)
{
    using std::vector;
    using std::shared_ptr;

    ThreadPool fixedPool(cap, 4);
    vector<shared_ptr<Task>> tasks;
    const int ntasks = cap * 2;
    tasks.reserve(ntasks);

    for(int i = 0; i < ntasks ; ++i)
    {
        tasks.emplace_back(new Task());
        fixedPool.Submit(tasks.back());
    }

    for(int i = 0 ; i < ntasks ; ++i)
    {
        ASSERT_THAT(tasks[i]->IsDone());
    }

    fixedPool.ShutDown();
    ASSERT_EQUAL(fixedPool.NumCurrentTasks(), 0);   
}
END_TEST


BEGIN_TEST(tp_immidiete_shut_down_single_thread_and_task)
{
    ThreadPool fixedPool(cap, 0);
    std::shared_ptr<Task> task(new Task());
    
    fixedPool.Submit(task);
    ASSERT_EQUAL(fixedPool.NumCurrentTasks(), 1);

    fixedPool.addThreads(1);

    ASSERT_THAT(task->IsDone());
    ASSERT_EQUAL(fixedPool.NumCurrentTasks(), 0);
    ASSERT_EQUAL(fixedPool.NumCurrentThreads(), 1);
    
    fixedPool.ShutDownImmediately();
    ASSERT_EQUAL(fixedPool.NumCurrentThreads(), 0);
}
END_TEST


BEGIN_TEST(tp_immidiete_shut_down_single_thread_multiple_tasks)
{
    using std::vector;
    using std::shared_ptr;

    ThreadPool fixedPool(cap, 1);
    vector<shared_ptr<Task>> tasks;
    const int ntasks = cap * 5;
    tasks.reserve(ntasks);

    for(int i = 0; i < ntasks ; ++i)
    {
        tasks.emplace_back(new Task());
        fixedPool.Submit(tasks.back());
    }   

    fixedPool.ShutDownImmediately();
    ASSERT_NOT_EQUAL(fixedPool.NumCurrentTasks(), 0);
    ASSERT_EQUAL(fixedPool.NumCurrentThreads(), 0);
}
END_TEST


BEGIN_TEST(tp_immidiete_shut_down_multiple_thread_multiple_tasks)
{
    using std::vector;
    using std::shared_ptr;
    const int N_TASKS = 1000000;

    ThreadPool fixedPool(N_TASKS, 0);
    shared_ptr<TaskCount> taskCount(new TaskCount);

    for(int i = 0; i < N_TASKS ; ++i)
    {
        fixedPool.Submit(taskCount);
    }   

    fixedPool.addThreads(20);
    fixedPool.ShutDownImmediately();

    ASSERT_NOT_EQUAL(taskCount->GetCount(), N_TASKS);
    ASSERT_EQUAL(fixedPool.NumCurrentThreads(), 0);
}
END_TEST


BEGIN_TEST(tp_dtor_test)

using std::vector;
using std::shared_ptr;

const int N_TASKS = 1000000;
shared_ptr<TaskCount> taskCount(new TaskCount);

{
    ThreadPool fixedPool(N_TASKS, 0);
    shared_ptr<TaskCount> taskCount(new TaskCount);

    for(int i = 0; i < N_TASKS ; ++i)
    {
        fixedPool.Submit(taskCount);
    } 

    fixedPool.addThreads(20);
}

ASSERT_NOT_EQUAL(taskCount->GetCount(), N_TASKS);
ASSERT_EQUAL(fixedPool.NumCurrentThreads(), 0);

END_TEST


BEGIN_SUITE(不耻下问)
    
    // TEST(tp_basic_submit_test)
    // TEST(tp_basic_submit_check_throw_test)
    // TEST(tp_run_normal_tasks_after_exception_task)
    // TEST(tp_run_many_tasks)
    // TEST(tp_add_thread_to_no_thread_tp)
    // TEST(tp_shut_down_single_thread_multiple_tasks_test)
    // TEST(tp_shut_down_multiple_threads_and_tasks)
    // TEST(tp_immidiete_shut_down_single_thread_and_task)
    // TEST(tp_immidiete_shut_down_single_thread_and_task)
    // TEST(tp_immidiete_shut_down_single_thread_multiple_tasks)
    // TEST(tp_immidiete_shut_down_multiple_thread_multiple_tasks)
    TEST(tp_dtor_test)

END_SUITE
