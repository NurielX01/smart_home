#include <stdexcept> //std::runtime_error
#include "mutex.hpp" // Mutex header


namespace advcpp
{

Mutex::Mutex() 
: m_mutex(PTHREAD_MUTEX_INITIALIZER) {}

Mutex::~Mutex()
{
    UnLock();
    pthread_mutex_destroy(&m_mutex);
}

void Mutex::Lock()
{
    int result = pthread_mutex_lock(&m_mutex);
    if(result != 0)
    {
        throw(std::runtime_error("Mutex lock failed"));
    }
}

void Mutex::UnLock()
{
    int result = pthread_mutex_unlock(&m_mutex);
    if(result != 0)
    {
        throw(std::runtime_error("Mutex unlock failed"));
    }
}

pthread_mutex_t& Mutex::GetMutex()
{
    return m_mutex;
}

}