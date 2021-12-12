#include <vector> //std::vector
#include <memory> //std::shared_ptr
#include <algorithm> //std::is_sorted
#include "mu_test.h" //mu_tests header
#include "thread.hpp" //Thread header
#include "producer.hpp" //Producer header
#include "consumer.hpp" //Consumer header
#include "vector_helpers.hpp" //VectorHelpers header
#include "block_bounded_q.hpp" //BlockBoundedQ header
#include "void_method_void_adapt.hpp" //ResultMethodArgAdapt header
#include "group_thread.hpp" //GroupThread header
using namespace advcpp;
using namespace test_widgets;
using Adapter = VoidMethodVoidAdapt<Producer&, void(Producer::*)(void)>;
using ProducerAdapter = VoidMethodVoidAdapt<Producer&, void(Producer::*)(void)>;
using ConsumerAdapter = VoidMethodVoidAdapt<Consumer&, void(Consumer::*)(void)>;


BEGIN_TEST(test_queue_get_capacity)
{
    const size_t N = 10;
    BlockBoundedQ<size_t> queue(N);
    ASSERT_EQUAL(queue.GetCapacity(), N);
}
END_TEST

BEGIN_TEST(test_queue_is_empty)
{
    const size_t N = 10;
    BlockBoundedQ<size_t> queue(N); 
    ASSERT_EQUAL(queue.IsEmpty(), true);
}
END_TEST

BEGIN_TEST(test_queue_is_full)
{
    const size_t N = 10;
    BlockBoundedQ<size_t> queue(N);
    Producer producer(queue, N); 
    std::shared_ptr<Adapter> adapter = std::make_shared<Adapter>(producer, &Producer::FillContainer);

    {
        Thread<JoinPolicy> thread(adapter);
    }
    
    ASSERT_EQUAL(queue.IsFull(), true);
}
END_TEST

BEGIN_TEST(test_queue_get_size)
{
    const size_t N = 10;
    BlockBoundedQ<size_t> queue(N);
    Producer producer(queue, N);
    std::shared_ptr<Adapter> adapter = std::make_shared<Adapter>(producer, &Producer::FillContainer);

    {
        Thread<JoinPolicy> thread(adapter);
    }

    ASSERT_EQUAL(queue.GetSize(), N);
}
END_TEST

BEGIN_TEST(one_producer_one_consumer_10_values)
{ 
    const size_t N = 10;
    BlockBoundedQ<size_t> queue(N);
    Producer prod(queue, N);
    std::shared_ptr<ProducerAdapter> adapterProdc = std::make_shared<ProducerAdapter>(prod, &Producer::FillContainer);

    {
        Thread<JoinPolicy> thread1(adapterProdc);
    }

    Consumer consumer(queue, N); 
    std::shared_ptr<ConsumerAdapter> adapterCons = std::make_shared<ConsumerAdapter>(consumer, &Consumer::ConsumeContainer);

    {
        Thread<JoinPolicy> thread2(adapterCons);
    }

    ASSERT_EQUAL(queue.GetSize(), 0);
    bool result = std::is_sorted(consumer.GetInnerContainer().begin(), consumer.GetInnerContainer().end());
    ASSERT_EQUAL(result, true);
}
END_TEST

BEGIN_TEST(one_producer_one_consumer_1000_values)
{
    const size_t N = 1000;
    BlockBoundedQ<size_t> queue(N);
    Producer prod(queue, N);
    std::shared_ptr<ProducerAdapter> adapterProdc = std::make_shared<ProducerAdapter>(prod, &Producer::FillContainer);
    
    {
        Thread<JoinPolicy> thread1(adapterProdc);
    }

    Consumer consumer(queue, N); 
    std::shared_ptr<ConsumerAdapter> adapterCons = std::make_shared<ConsumerAdapter>(consumer, &Consumer::ConsumeContainer);
    
    {
        Thread<JoinPolicy> thread2(adapterCons);
    }

    ASSERT_EQUAL(queue.GetSize(), 0);
    bool result = std::is_sorted(consumer.GetInnerContainer().begin(), consumer.GetInnerContainer().end());
    ASSERT_EQUAL(result, true);
}
END_TEST

BEGIN_TEST(two_producers_one_consumer_1000_values)
{
    const size_t N = 10;
    BlockBoundedQ<size_t> queue(N);
    Producer prod(queue, N);
    std::shared_ptr<ProducerAdapter> adapterProdc = std::make_shared<ProducerAdapter>(prod, &Producer::FillContainer);
    
    Thread<JoinPolicy> thread1(adapterProdc);
    Thread<JoinPolicy> thread2(adapterProdc);
    Consumer consumer(queue, N * 2);
    std::shared_ptr<ConsumerAdapter> adapterCons = std::make_shared<ConsumerAdapter>(consumer, &Consumer::ConsumeContainer);
    
    {
        Thread<JoinPolicy> thread3(adapterCons);
    }

    ASSERT_EQUAL(consumer.Size(), N * 2); //check all values consumed
    ASSERT_EQUAL(queue.GetSize(), NONE); //check all values consumed
    std::vector<size_t>::iterator resultItr = std::unique(consumer.GetInnerContainer().begin(), consumer.GetInnerContainer().end());
    ASSERT_EQUAL(*resultItr, *consumer.GetInnerContainer().end()); //check if consumed any duplicats
}
END_TEST

BEGIN_TEST(one_producer_two_consumers_1000_values)
{
    const size_t PRODUCER_AMOUNT = 20;
    const size_t CONSUMER_AMOUNT = 10;
    const size_t QUEUE_CAPACITY = 5;
    BlockBoundedQ<size_t> queue(QUEUE_CAPACITY);
    Producer producer(queue, PRODUCER_AMOUNT);
    auto adapterProdc = std::make_shared<ProducerAdapter>(producer, &Producer::FillContainer);
    Thread<JoinPolicy> thread1(adapterProdc);
    Consumer consumer1(queue, CONSUMER_AMOUNT); 
    Consumer consumer2(queue, CONSUMER_AMOUNT);
    auto adapterCons1 = std::make_shared<ConsumerAdapter>(consumer1, &Consumer::ConsumeContainer);
    auto adapterCons2 = std::make_shared<ConsumerAdapter>(consumer2, &Consumer::ConsumeContainer);
    
    {
        Thread<JoinPolicy> thread2(adapterCons1);
        Thread<JoinPolicy> thread3(adapterCons2);
    }

    ASSERT_EQUAL(consumer1.Size(), CONSUMER_AMOUNT);
    ASSERT_EQUAL(consumer2.Size(), CONSUMER_AMOUNT);
    ASSERT_PASS(); 
}
END_TEST

BEGIN_TEST(two_producer_two_consumers_1000_values)
{
    const size_t PRODUCER_AMOUNT = 500;
    const size_t CONSUMER_AMOUNT = 500;
    const size_t QUEUE_CAPACITY = 5;
    BlockBoundedQ<size_t> queue(QUEUE_CAPACITY);
    Producer producer(queue, PRODUCER_AMOUNT);
    Consumer consumer(queue, CONSUMER_AMOUNT); 
    auto adapterProdc = std::make_shared<ProducerAdapter>(producer, &Producer::FillContainer);
    Thread<JoinPolicy> thread1(adapterProdc);
    Thread<JoinPolicy> thread2(adapterProdc);

    auto adapterCons = std::make_shared<ConsumerAdapter>(consumer, &Consumer::ConsumeContainer);   
    {
        Thread<JoinPolicy> thread3(adapterCons);
        Thread<JoinPolicy> thread4(adapterCons);
    }

    ASSERT_EQUAL(queue.GetSize(), 0);
    auto resultItr = std::unique(consumer.GetInnerContainer().begin(), consumer.GetInnerContainer().end());
    ASSERT_EQUAL(*resultItr, *consumer.GetInnerContainer().end()); //checking duplicates
}
END_TEST

BEGIN_TEST(fifty_producer_50_consumers_1000_values)
{
    const size_t PRODUCER_AMOUNT = 20;
    const size_t CONSUMER_AMOUNT = 20;
    const size_t QUEUE_CAPACITY = 20;
    BlockBoundedQ<size_t> queue(QUEUE_CAPACITY);
    Producer producer(queue, PRODUCER_AMOUNT);
    Consumer consumer(queue, CONSUMER_AMOUNT); 
    auto adapterProdc = std::make_shared<ProducerAdapter>(producer, &Producer::FillContainer);
    GroupThread<JoinPolicy> gpProducer(adapterProdc, 50);

    auto adapterCons = std::make_shared<ConsumerAdapter>(consumer, &Consumer::ConsumeContainer);   
    {
        GroupThread<JoinPolicy> gpConsumer(adapterCons, 50);
    }

    ASSERT_EQUAL(queue.GetSize(), 0);
    auto resultItr = std::unique(consumer.GetInnerContainer().begin(), consumer.GetInnerContainer().end());
    ASSERT_EQUAL(*resultItr, *consumer.GetInnerContainer().end()); //checking duplicates
}
END_TEST


BEGIN_SUITE(不耻下问)

    TEST(test_queue_get_capacity)
    TEST(test_queue_is_empty)
    TEST(test_queue_is_full)
    TEST(test_queue_get_size)
    TEST(one_producer_one_consumer_10_values)
    TEST(one_producer_one_consumer_1000_values)
    TEST(two_producers_one_consumer_1000_values)
    TEST(one_producer_two_consumers_1000_values)
    TEST(two_producer_two_consumers_1000_values)
    TEST(fifty_producer_50_consumers_1000_values)

END_SUITE