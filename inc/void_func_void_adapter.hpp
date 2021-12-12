#ifndef VOID_FUNC_VOID_ADAPTER_HPP_
#define VOID_FUNC_VOID_ADAPTER_HPP_
#include "callable.hpp"


namespace advcpp
{

template<typename FuncType>
class VoidFuncVoidAdapter : public Callable 
{
public:
    VoidFuncVoidAdapter(FuncType& a_func) : m_func(a_func){}
    virtual ~VoidFuncVoidAdapter() = default;
private:
    void Execute() override {m_func();}

private:
    FuncType& m_func;
};

}

#endif //VOID_FUNC_VOID_ADAPTER_HPP

