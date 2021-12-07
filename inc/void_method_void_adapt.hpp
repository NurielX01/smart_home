#ifndef VOID_METHOD_VOID_ADAPT_
#define VOID_METHOD_VOID_ADAPT_
#include "callable.hpp" //callable header


namespace advcpp
{

template<typename ClassObject, typename FuncType>
class VoidMethodVoidAdapt : public Callable
{
public:
    VoidMethodVoidAdapt(const ClassObject& a_obj, const FuncType& a_func) : m_func(a_func), m_obj(a_obj){}
    virtual ~VoidMethodVoidAdapt() = default;
    
private:
    void Execute() override {
        (m_obj.*m_func)();
    }

private:
    FuncType m_func;
    ClassObject& m_obj;
};

}


#endif // VOID_METHOD_VOID_ADAPT_
