#include "producer.hpp" //Producer header

namespace test_widgets
{

Producer::Producer(advcpp::BlockBoundedQ<size_t>& a_queue, size_t a_amountToProduce)
: m_queue(a_queue)
, m_amountToProduce(a_amountToProduce){}

void Producer::FillContainer()
{
    const int noPriority = 0;
    for(size_t i = 0 ; i < m_amountToProduce ; ++i)
    {
        m_queue.Enqueue(i, noPriority);
    }
}

}