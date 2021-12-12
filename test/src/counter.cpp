#include "counter.hpp"
#include <iostream>


namespace advcpp
{

size_t Counter::Count() const
{
    return m_count;
}

void Counter::Increment()
{
    ++m_count;
}


size_t Counter::IncrementBy(size_t a_thisMuch)
{
    return m_count += a_thisMuch; 
}


void Counter::IncrementThenMultiply(size_t a_incByThisMuch, size_t a_multiByThisMuch)
{
    m_count = (m_count + a_incByThisMuch) * a_multiByThisMuch;
}


void Counter::Decrement()
{
    if(m_count != 0)
    {
        --m_count;
    }
}


}