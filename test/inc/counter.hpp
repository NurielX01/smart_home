#ifndef COUNTER_HPP_
#define COUNTER_HPP_
#include <cstddef>


namespace advcpp
{

class Counter
{
public:
    //ctor, dtor, assignment
    Counter() = default;
    Counter(const Counter& a_other) = default;
    Counter& operator=(const Counter& a_other) = default;

    //member methods
    size_t Count() const;
    size_t IncrementBy(size_t a_thisMuch);
    void IncrementThenMultiply(size_t a_incByThisMuch, size_t a_multiByThisMuch);
    void Increment();
    void Decrement();

private:
    size_t m_count = 0;
};

}


#endif // COUNTER_HPP_