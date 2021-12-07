#include "sync_point.hpp" //SyncPoint header


namespace advcpp
{

bool SyncPoint::GetFlag()
{
    rethrowIfFail();
    return m_flag.IsOn();
}

void SyncPoint::SetFlag()
{
    return m_flag.Set();
}

void SyncPoint::SetException(std::exception_ptr a_exceptionPtr)
{
    m_exceptionPtr = a_exceptionPtr;
}

void SyncPoint::rethrowIfFail()
{
    if(m_exceptionPtr)
    {
        std::rethrow_exception(m_exceptionPtr);
    }
}

}