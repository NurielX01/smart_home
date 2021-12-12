#include "mu_test.h"
#include "counter.hpp" //Counter header
#include "group_thread.hpp" //GroupThread header
#include "result_method_arg_adapt.hpp" //ResultMethodArgAdapt header
#include "void_method_void_adapt.hpp" //VoidMethodVoidAdapt header
#include <memory> //std::shared_pointer
#include <unistd.h> //sleep
#include <iostream>
using namespace advcpp;


BEGIN_TEST(test_5_threads_join)
{
    using Adapter = ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>;
    Counter counter;
    auto adapter = std::make_shared<Adapter>(counter, &Counter::IncrementBy, 10);
    
    {
        GroupThread<JoinPolicy> gt(adapter, 5);
    }
    
    ASSERT_EQUAL(adapter->GetResult(), 50);
}
END_TEST

BEGIN_TEST(test_1000_threads_join)
{
    using Adapter = ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>;
    Counter counter;
    auto adapter = std::make_shared<Adapter>(counter, &Counter::IncrementBy, 1);
    
    {
        GroupThread<JoinPolicy> gt(adapter, 1000);
    }
    
    ASSERT_EQUAL(adapter->GetResult(), 1000);
    ASSERT_EQUAL(adapter.use_count(), 1);
}
END_TEST

BEGIN_TEST(test_5_threads_detach)
{
    using Adapter = ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>;
    Counter counter;
    std::shared_ptr<Adapter> adapter = std::make_shared<Adapter>(counter, &Counter::IncrementBy, 10);
    GroupThread<DetachPolicy> gt(adapter, 5);
    
    ASSERT_NOT_EQUAL(adapter->GetResult(), 50);
    ASSERT_NOT_EQUAL(adapter.use_count(), 1);
}
END_TEST

BEGIN_TEST(test_500_threads_detach)
{
    using Adapter = ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>;   
    Counter counter;
    auto adapter = std::make_shared<Adapter>(counter, &Counter::IncrementBy, 1);
    GroupThread<DetachPolicy> gt(adapter, 500);
    
    ASSERT_NOT_EQUAL(adapter->GetResult(), 500);
    ASSERT_NOT_EQUAL(adapter.use_count(), 1);
}
END_TEST

BEGIN_TEST(test_add_5_join)
{
    using Adapter = ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>;
    Counter counter;
    auto adapter = std::make_shared<Adapter>(counter, &Counter::IncrementBy, 1);
    
    {
        GroupThread<JoinPolicy> gt(adapter, 0);
        gt.Add(5);
    }

    ASSERT_EQUAL(adapter->GetResult(), 5);
    ASSERT_EQUAL(adapter.use_count(), 1);
}
END_TEST

BEGIN_TEST(test_add_1000_join)
{
    using Adapter = ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>;
    Counter counter;
    std::shared_ptr<Adapter> adapter = std::make_shared<Adapter>(counter, &Counter::IncrementBy, 1);
    GroupThread<JoinPolicy> gt(adapter, 0);
    gt.Add(1000);
    ASSERT_EQUAL(adapter->GetResult(), 999);
}
END_TEST

BEGIN_TEST(simple_remove)
{
    using Adapter = ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>;
    Counter counter;
    auto adapter = std::make_shared<Adapter>(counter, &Counter::IncrementBy, 1);
    
    {  
        GroupThread<JoinPolicy> gt(adapter, 5);
        size_t result = gt.Remove(4);
        ASSERT_EQUAL(result, 4);
    }
}
END_TEST

BEGIN_TEST(test_remove)
{
    using Adapter = ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>;
    Counter counter;
    auto adapter = std::make_shared<Adapter>(counter, &Counter::IncrementBy, 1);
    GroupThread<JoinPolicy> gt(adapter, 2000);
    gt.Remove(2000);
    ASSERT_EQUAL(adapter->GetResult(), 2000);
}
END_TEST

BEGIN_TEST(remove_add_remove)
{
    using Adapter = VoidMethodVoidAdapt<Counter&, void(Counter::*)()>;
    Counter counter;
    auto adapter1 = std::make_shared<Adapter>(counter, &Counter::Increment);
    auto adapter2 = std::make_shared<Adapter>(counter, &Counter::Decrement);
    
    {
        GroupThread<JoinPolicy> gt1(adapter1, 1000);
        GroupThread<JoinPolicy> gt2(adapter2, 1000);

        gt2.Remove(900);
        gt1.Add(1000);
        gt2.Remove(1000);
    }

    ASSERT_EQUAL(counter.Count(), 1000);
}
END_TEST

BEGIN_TEST(remove_when_empty)
{
    using Adapter = VoidMethodVoidAdapt<Counter&, void(Counter::*)()>;
    Counter counter;
    auto adapter1 = std::make_shared<Adapter>(counter, &Counter::Increment);   
    size_t result = 10;

    {
        GroupThread<JoinPolicy> gt1(adapter1, 0);
        result = gt1.Remove(1);
    }

    ASSERT_EQUAL(result, 0);
}
END_TEST


class Task : public Callable
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
        sleep(2);        
    }
};

BEGIN_TEST(check_func_how_many_working_threads)
{
    std::shared_ptr<Task> task (new Task());
    
    size_t result = 0;
    {
        GroupThread<JoinPolicy> gt1(task, 5);
        result = gt1.HowManyAtWork();
    }

    ASSERT_EQUAL(result, 5);
}   
END_TEST

BEGIN_SUITE(不耻下问)
    
    TEST(test_5_threads_join)
    TEST(test_1000_threads_join)
    TEST(test_5_threads_detach)
    TEST(test_500_threads_detach)
    TEST(test_add_5_join)
    TEST(test_add_1000_join)
    TEST(simple_remove)
    TEST(remove_add_remove)
    TEST(remove_when_empty)
    TEST(check_func_how_many_working_threads)

END_SUITE
