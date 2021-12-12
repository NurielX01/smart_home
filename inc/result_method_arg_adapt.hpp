#ifndef RESULT_METHOD_ARG_ADAPT_
#define RESULT_METHOD_ARG_ADAPT_
#include "callable.hpp" //Callable header


namespace advcpp
{


template<typename ResultType, typename ClassObject, typename FuncType, typename ArgType> 
class ResultMethodArgAdapt : public Callable
{ 
public:
    ResultMethodArgAdapt(ClassObject& a_obj, FuncType a_func, ArgType a_arg) : m_func(a_func), m_obj(a_obj), m_arg(a_arg){}
    virtual ~ResultMethodArgAdapt() = default;
    ResultType GetResult() {return m_result;}

private:
    void Execute() override {m_result = (m_obj.*m_func)(m_arg);}

private:
    FuncType m_func;
    ClassObject m_obj;
    ArgType m_arg;
    ResultType m_result = 0;
};


}

#endif // RESULT_METHOD_ARG_ADAPT_

