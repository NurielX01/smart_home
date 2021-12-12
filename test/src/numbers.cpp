#include "numbers.hpp"
#include <iostream> //std::cout


namespace test_widgets
{

void PrintSomthing()
{
    std::cout << "Counter: printed something" << std::endl;
}

size_t ReturnArgPlusFive(size_t a_arg)
{
    return a_arg + 5;
}  

size_t Sum(size_t a_x, size_t a_y)
{
    return a_x + a_y;
}

} // namespace test_widget


