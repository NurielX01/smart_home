#ifndef CONSUMER_HPP_
#define CONSUMER_HPP_
#include "block_bounded_q.hpp" //BlockBoundedQ header
#include <cstddef> //size_t
#include <vector> //std::vector
#include <memory> 


namespace test_widgets
{
    
class Consumer
{
public:
    Consumer(advcpp::BlockBoundedQ<size_t>& a_queue, size_t a_amountToConsume);
    ~Consumer() = default;

    Consumer(const Consumer& a_other) = delete;
    Consumer& operator=(const Consumer& a_other) = delete;

    void ConsumeContainer();
    
    //for tests
    std::vector<size_t>& GetInnerContainer();
    size_t Size();

    
private:
    advcpp::BlockBoundedQ<size_t>& m_queue;
    size_t m_amountToConsume;
    std::vector<size_t> m_vector;
};


}


#endif // CONSUMER_HPP_

