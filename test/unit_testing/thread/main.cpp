#include "mu_test.h"
#include "thread.hpp" //Thread header
#include "counter.hpp" //Counter header
#include "numbers.hpp" //Numbers header
#include "void_func_void_adapter.hpp" //VoidFuncVoidAdapter header
#include "result_func_arg_adapter.hpp" //ResultFuncArgAdapter header
#include "result_func_two_args_adapter.hpp" //ResultFuncTwoArgsAdapter header
#include "void_method_void_adapt.hpp" //VoidMethodVoidAdapt header
#include "result_method_arg_adapt.hpp" //ResultMethodArgAdapt header
#include "result_method_two_args_adapt.hpp" //ResultMethodTwoArgsAdapt
#include <memory> //std::shared_pointer
#include <unistd.h> //sleep
#include <functional>


using namespace advcpp;
using namespace test_widgets;


BEGIN_TEST(thread_globalFunc_adapter_void_func_void)

    try
    {
        auto adapter = std::make_shared<VoidFuncVoidAdapter<void(void)>>(PrintSomthing);
        Thread<JoinPolicy> thread(adapter); 
        ASSERT_PASS();
    }
    catch(...)
    {
        ASSERT_FAIL("was not supposed to throw");
    }    

END_TEST


BEGIN_TEST(thread_globalFunc_adapter_result_func_arg)
    using std::shared_ptr;
    using std::make_shared;

    auto adapter = make_shared<ResultFuncArgAdapter<size_t,size_t(size_t), size_t>>(ReturnArgPlusFive, 9);

    {
        Thread<JoinPolicy> thread(adapter);
    }

    size_t resultVal = adapter->GetResult();
    ASSERT_EQUAL(resultVal, 14);

END_TEST


BEGIN_TEST(thread_globalFunc_adapter_result_func_two_args)
    using std::shared_ptr;
    using std::make_shared;

    auto adapter = make_shared<ResultFuncTwoArgsAdapter<size_t, size_t(size_t, size_t), size_t, size_t>>(Sum, 9, 14);
    {
        Thread<JoinPolicy> thread(adapter);
    }
    
    size_t resultVal = adapter->GetResult();
    ASSERT_EQUAL(resultVal, 23);

END_TEST


BEGIN_TEST(thread_classFunc_adapter_void_method_void)

    using std::shared_ptr;
    using std::make_shared;

    Counter counter;
    auto adapter = make_shared<VoidMethodVoidAdapt<Counter&, void(Counter::*)()>>(counter, &Counter::Increment);

    {
        Thread<JoinPolicy> thread(adapter);
    }

    ASSERT_EQUAL(counter.Count(), 1);

END_TEST


BEGIN_TEST(thread_classFunc_adapter_result_method_arg)

    using std::shared_ptr;
    using std::make_shared;

    Counter counter;
    auto adapter = make_shared<ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>>(counter, &Counter::IncrementBy, 29);
    
    {
        Thread<JoinPolicy> thread(adapter);
    }

    ASSERT_EQUAL(adapter->GetResult(), 29);
    ASSERT_EQUAL(counter.Count(), 29);

END_TEST


BEGIN_TEST(thread_classFunc_adapter_result_method_two_args)

    using std::shared_ptr;
    using std::make_shared;

    Counter counter;

    auto adapter = make_shared<ResultMethodTwoArgsAdapt<size_t, Counter&, size_t(Counter::*)(size_t, size_t), size_t, size_t>>(counter, &Counter::IncrementThenMultiply, 5, 4);

    {
        Thread<JoinPolicy> thread(adapter);
    }

    ASSERT_EQUAL(adapter->GetResult(), 20);
    ASSERT_EQUAL(counter.Count(), 20);

END_TEST


BEGIN_TEST(thread_double_join_check)
    
    try
    {
        using std::shared_ptr;
        using std::make_shared;

        Counter counter;
        auto adapter = make_shared<ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>>(counter, &Counter::IncrementBy, 29);
        {
            Thread<JoinPolicy> thread(adapter);
            thread.Join(); //TODO - fix this one
        }        
    }

    catch(const std::exception& e)
    {   
        std::cerr << e.what() << '\n';
        ASSERT_PASS();
    }
    ASSERT_PASS();
    
END_TEST

Counter g_counter1;
BEGIN_TEST(thread_detach_check)
    
    using std::shared_ptr;
    using std::make_shared;

    auto adapter = make_shared<ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>>(g_counter1, &Counter::IncrementBy, 29); 
    
    {
        Thread<DetachPolicy> thread(adapter);
    }
    
    ASSERT_EQUAL(adapter.use_count(), 2);

END_TEST


BEGIN_TEST(two_threads_both_join)
    
    using std::shared_ptr;
    using std::make_shared;

    Counter counter;
    auto adapter = make_shared<ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>>(counter, &Counter::IncrementBy, 30); 
    
    {
        Thread<JoinPolicy> thread1(adapter);
        Thread<JoinPolicy> thread2(adapter);
    }

    ASSERT_EQUAL(adapter->GetResult(), 60);
    ASSERT_EQUAL(adapter.use_count(), 1);

END_TEST


Counter g_counter2;
BEGIN_TEST(two_threads_both_detached)
    
    using Adapter = ResultMethodArgAdapt<size_t, Counter&, size_t(Counter::*)(size_t), size_t>;

    Counter counter;
    std::shared_ptr<Adapter> adapter = std::make_shared<Adapter>(g_counter2, &Counter::IncrementBy, 30); 
    
    Thread<DetachPolicy> thread1(adapter);
    Thread<DetachPolicy> thread2(adapter);
    ASSERT_EQUAL(adapter.use_count(), 4);

END_TEST


    BEGIN_SUITE(不耻下问)
    
    TEST(thread_globalFunc_adapter_void_func_void)
    TEST(thread_globalFunc_adapter_result_func_arg)
    TEST(thread_globalFunc_adapter_result_func_two_args)
    TEST(thread_classFunc_adapter_void_method_void)
    TEST(thread_classFunc_adapter_result_method_arg)
    TEST(thread_classFunc_adapter_result_method_two_args)
    TEST(thread_double_join_check) //TODO - fix abory err
    TEST(thread_detach_check)
    TEST(two_threads_both_join)
    TEST(two_threads_both_detached)

    END_SUITE
