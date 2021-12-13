#include "mu_test.h" //test gui header
#include "mutex.hpp" //mutex C++ wrapper header
#include "thread.hpp" //thread C++ wrapper header
#include "group_thread.hpp" //GroupThread header
#include "callable.hpp" //Callable header
#include <memory> //shared_ptr
using namespace advcpp;
using namespace std;


Mutex g_mtx;
int g_x = 0;

class MutexTestAction : public Callable
{
public: 
    void Execute()
    {
        g_mtx.Lock();
        ++g_x;
        g_mtx.UnLock();
    };
};

BEGIN_TEST(simple_test_5_threads)
{   
    MutexTestAction actionItem;
    shared_ptr<Callable> actionItemPtr = make_shared<MutexTestAction>(actionItem);

    {
        Thread<JoinPolicy> thr1(actionItemPtr);
        Thread<JoinPolicy> thr2(actionItemPtr);
        Thread<JoinPolicy> thr3(actionItemPtr);
        Thread<JoinPolicy> thr4(actionItemPtr);
        Thread<JoinPolicy> thr5(actionItemPtr);
    }

    ASSERT_EQUAL(g_x, 5);
}
END_TEST

BEGIN_TEST(simple_test_500_threads)
{       
    MutexTestAction actionItem;
    shared_ptr<Callable> actionItemPtr = make_shared<MutexTestAction>(actionItem);

    {
        GroupThread<JoinPolicy> groupThreads(actionItemPtr, 500);
    }

    ASSERT_EQUAL(g_x, 505);
}
END_TEST

BEGIN_TEST(simple_test_2000_threads)
{       
    MutexTestAction actionItem;
    shared_ptr<Callable> actionItemPtr = make_shared<MutexTestAction>(actionItem);

    {
        GroupThread<JoinPolicy> groupThreads(actionItemPtr, 2000);
    }

    ASSERT_EQUAL(g_x, 2505);
}
END_TEST

BEGIN_SUITE(不耻下问)

    TEST(simple_test_5_threads)
    TEST(simple_test_500_threads)
    TEST(simple_test_2000_threads)

END_SUITE
