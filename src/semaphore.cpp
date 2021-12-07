#include "semaphore.hpp" //semaphore header


Semaphore::Semaphore(int a_pshared, unsigned int a_semVal) {
    int result = sem_init(&m_semaphore, a_pshared, a_semVal);
    if(result != 0) {
        throw(result);
    }
}

void Semaphore::Wait() {
    int result = sem_wait(&m_semaphore);
    if(result != 0) {
        throw(result);
    }
}

void Semaphore::Post() {
    int result = sem_post(&m_semaphore);
    if(result != 0) {
        throw(result);
    }
}

int Semaphore::GetValue() {
    int semaphoreNumber;
    int result = sem_getvalue(&m_semaphore, &semaphoreNumber);
    if(result != 0) {
        throw(result);
    }
    return semaphoreNumber;
}