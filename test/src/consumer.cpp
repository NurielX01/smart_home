#include "consumer.hpp" //Consumer header
#include "vector_helpers.hpp" //VectorHelpers header


namespace test_widgets
{

Consumer::Consumer(advcpp::BlockBoundedQ<size_t>& a_queue, size_t a_amountToConsume)
: m_queue(a_queue)
, m_amountToConsume(a_amountToConsume)
{
    m_vector.reserve(m_amountToConsume);
}

void Consumer::ConsumeContainer()
{
    for(size_t i = 0 ; i < m_amountToConsume ; ++i)
    {
        size_t valueDequed;
        m_queue.Dequeue(valueDequed);
        m_vector.push_back(valueDequed);
    }
}

std::vector<size_t>& Consumer::GetInnerContainer()
{
    return m_vector;
}

size_t Consumer::Size()
{
    return m_vector.size();
}


}