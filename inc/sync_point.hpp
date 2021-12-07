#ifndef SYNC_POINT_HPP_
#define SYNC_POINT_HPP_
#include "atomic_value.hpp" //AtomicValue header
#include <exception> //std::exception_ptr


namespace advcpp
{

class SyncPoint
{
public:
    void SetException(std::exception_ptr a_exceptionPtr);
    bool GetFlag();
    void SetFlag();

private:
    void rethrowIfFail();

private:
    AtomicValue<bool> m_flag;
    std::exception_ptr m_exceptionPtr;
};

}


#endif // SYNC_POINT_HPP_