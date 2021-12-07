#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__
#include <pthread.h> //pthread_mutex_t


namespace advcpp
{

class Mutex {
public:

    Mutex();
    ~Mutex();

    Mutex(const Mutex& a_mutex) = delete;
    Mutex& operator=(const Mutex& a_mutex) = delete;
    
    void Lock();
    void UnLock();
    pthread_mutex_t& GetMutex();

private:
    pthread_mutex_t m_mutex;
};

}

#endif // __MUTEX_HPP_

