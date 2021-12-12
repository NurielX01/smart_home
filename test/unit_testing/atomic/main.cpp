#include "mu_test.h"
#include "atomic_value.hpp" //AtomicValue header
using namespace advcpp;


BEGIN_TEST(int_simple_increment)
{
    AtomicValue<int> av(5);
    av++;
    ASSERT_EQUAL(av.Get(), 6);
}
END_TEST

BEGIN_TEST(int_simple_decrement)
{
    AtomicValue<int> av(5);
    av--;
    ASSERT_EQUAL(av.Get(), 4);
}
END_TEST

BEGIN_TEST(bool_simple_get)
{
    AtomicValue<bool> av1;
    ASSERT_EQUAL(av1.IsOn(), false);

    AtomicValue<bool> av2(true);
    ASSERT_EQUAL(av2.IsOn(), true);
}
END_TEST

BEGIN_TEST(bool_simple_toggle)
{
    AtomicValue<bool> av;
    
    av.Toggle();
    ASSERT_EQUAL(av.IsOn(), true);
    
    av.Toggle();
    ASSERT_EQUAL(av.IsOn(), false);

    av.Toggle();
    ASSERT_EQUAL(av.IsOn(), true);

    av.Toggle();
    ASSERT_EQUAL(av.IsOn(), false);
}
END_TEST

BEGIN_TEST(bool_simple_set)
{
    AtomicValue<bool> av;
    ASSERT_EQUAL(av.IsOn(), false);

    av.Set();
    ASSERT_EQUAL(av.IsOn(), true);

    av.Set();
    ASSERT_EQUAL(av.IsOn(), true);
}
END_TEST

BEGIN_SUITE(不耻下问)

    TEST(int_simple_increment)
    TEST(int_simple_decrement)

    TEST(bool_simple_get)
    TEST(bool_simple_toggle)

    TEST(bool_simple_set)

END_SUITE

