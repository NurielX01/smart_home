#include "mutex.hpp"


Mutex::Mutex() 
: m_mutex(PTHREAD_MUTEX_INITIALIZER) {

}

Mutex::~Mutex() {
    UnLock();
    pthread_mutex_destroy(&m_mutex);
}


void Mutex::Lock() {
    int result = pthread_mutex_lock(&m_mutex);
    if(result != 0) {
        throw(result);
    }
}

void Mutex::UnLock() {
    int result = pthread_mutex_unlock(&m_mutex);
    if(result != 0) {
        throw(result);
    }
}


pthread_mutex_t& Mutex::GetMutex() {
    return m_mutex;
}