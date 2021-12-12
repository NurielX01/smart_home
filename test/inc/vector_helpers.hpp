#ifndef VECTOR_HELPERS_HPP_
#define VECTOR_HELPERS_HPP_
#include <vector> //std::vector
#include <cstddef> //size_t


namespace test_widgets
{

template<typename TypeContainer, typename ValueType>
void PrintContainer(TypeContainer a_container);

template<typename T>
void PrintVector(const std::vector<T>& a_vector);

template<typename TypeContainer>
bool IsSorted(const TypeContainer& a_container);

}

#include "./inl/vector_helpers.hxx"

#endif // VECTOR_HELPERS_HPP_