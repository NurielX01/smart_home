#ifndef RESULT_FUNC_ARG_ADAPTER_HPP_
#define RESULT_FUNC_ARG_ADAPTER_HPP_
#include "callable.hpp"
#include <type_traits> //std::is_same
#include <cassert> //assert


namespace advcpp
{

template<typename ResultType, typename FuncType, typename ArgType>
class ResultFuncArgAdapter : public Callable 
{
public:
    ResultFuncArgAdapter(FuncType& a_func, ArgType a_arg) : m_func(a_func), m_arg(a_arg)
    {
        assert( (std::is_same<FuncType, ResultType(ArgType)>::value) );
    }
    
    virtual ~ResultFuncArgAdapter() = default;
    ResultType GetResult() {return m_result;}

private:
    void Execute() override {m_result = m_func(m_arg);}

private:
    FuncType& m_func;
    ResultType m_result = 0;
    ArgType m_arg;
};

}


#endif // RESULT_FUNC_ARG_ADAPTER_HPP_