#ifndef RESULT_FUNC_TWO_ARGS_ADAPTER_HPP_
#define RESULT_FUNC_TWO_ARGS_ADAPTER_HPP_
#include "callable.hpp"
#include <type_traits> //std::is_same
#include <cassert> //assert


namespace advcpp
{

template<typename ResultType, typename FuncType, typename ArgTypeA, typename ArgTypeB>
class ResultFuncTwoArgsAdapter : public Callable
{

public:
    ResultFuncTwoArgsAdapter(FuncType& a_func, ArgTypeA a_argA, ArgTypeB a_argB):
    m_func(a_func), m_argA(a_argA), m_argB(a_argB)
    {
        assert( (std::is_same<FuncType, ResultType(ArgTypeA,ArgTypeB)>::value) );
    }

    virtual ~ResultFuncTwoArgsAdapter() = default;
    ResultType GetResult() {return m_result;}

private:
    void Execute() override {m_result = m_func(m_argA, m_argB);}

private:
    FuncType& m_func;
    ResultType m_result = 0;
    ArgTypeA m_argA;
    ArgTypeB m_argB;
};

}

#endif //RESULT_FUNC_TWO_ARGS_ADAPTER_HPP_