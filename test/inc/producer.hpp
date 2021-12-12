#ifndef PRODUCER_HPP_
#define PRODUCER_HPP_
#include "block_bounded_q.hpp" //BlockBoundedQ header
#include <cstddef> //size_t
#include <memory> //std::shared_ptr


namespace test_widgets
{
    
class Producer
{
public:
    Producer(advcpp::BlockBoundedQ<size_t>& a_queue, size_t a_amountToProduce);
    ~Producer() = default;

    Producer(const Producer& a_other) = delete;
    Producer& operator=(const Producer& a_other) = delete;

    void FillContainer();
    
private:
    advcpp::BlockBoundedQ<size_t>& m_queue;
    size_t m_amountToProduce;
};


}


#endif // PRODUCER_HPP_