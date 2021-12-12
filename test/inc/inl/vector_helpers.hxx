#ifndef VECTOR_HELPERS_HXX_
#define VECTOR_HELPERS_HXX_
#include <algorithm>
#include <iostream>


namespace test_widgets
{

template<typename TypeContainer, typename ValueType>
void PrintContainer(TypeContainer a_container)
{
    auto PrintHelper = [](const ValueType& a_val) {std::cout << a_val << ",";};
    std::for_each(a_container.begin(), a_container.end(), PrintHelper);  
}


template<typename T>
void PrintVector(const std::vector<T>& a_vector)
{
    auto PrintHelper = [](const T& a_val) {std::cout << a_val << std::endl;};
    std::for_each(a_vector.begin(), a_vector.end(), PrintHelper);
}

template<typename TypeContainer>
bool IsSorted(const TypeContainer& a_container)
{
    auto size = a_container.size();
    
    for(size_t i = 0 ; i < size ; ++i)
    {
        for(size_t j = i ; j < size - 1 ; ++j)
        {
            if(a_container[j] > a_container[j + 1])
            {
                return false;
            }
        }
    }
    return true;
}


}


#endif // VECTOR_HELPERS_HXX_