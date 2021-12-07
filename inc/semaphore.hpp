#ifndef __SEMAPHORE_HPP__
#define __SEMAPHORE_HPP__
#include <semaphore.h> //sem_t


class Semaphore {
public:
    ///ctor
    Semaphore(int a_pshared = 0, unsigned int a_semVal = 0);
    
    //dtor
    ~Semaphore() = default;

    //public methods 
    void Wait();
    void Post();
    int GetValue();

private:
    sem_t m_semaphore;
};


#endif //__SEMAPHORE_HPP__