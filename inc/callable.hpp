#ifndef CALLABLE_HPP_
#define CALLABLE_HPP_


namespace advcpp
{

class Callable
{
public:
    Callable() = default;
    virtual ~Callable() = default;
    virtual void Execute() = 0;
};

}


#endif //CALLABLE_HPP_