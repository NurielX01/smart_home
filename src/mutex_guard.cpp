#include <stdexcept> //std::runtime_error
#include "mutex_guard.hpp" //mutex_guard header


MutexGuard::MutexGuard() 
: m_mutex(PTHREAD_MUTEX_INITIALIZER) {
    if(0 != pthread_mutex_lock(&m_mutex))
    {
        throw std::runtime_error("MutexGuard lock fail");
    }
}

MutexGuard::~MutexGuard() {
    pthread_mutex_unlock(&m_mutex);
    pthread_mutex_destroy(&m_mutex);
}

