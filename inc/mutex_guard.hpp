#ifndef MUTEX_GUARD_HPP_
#define MUTEX_GUARD_HPP_
#include <pthread.h> //pthread_mutex_t


class MutexGuard {
public:
    MutexGuard();
    ~MutexGuard();

private:
    pthread_mutex_t m_mutex;
};


#endif // MUTEX_GUARD_HPP_