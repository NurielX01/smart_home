#ifndef BLOCK_BOUNDED_Q_HPP_
#define BLOCK_BOUNDED_Q_HPP_
#include <cstddef> //size_t
#include <deque> //std::deque
#include "atomic_value.hpp" //AtomicValue header
#include "semaphore.hpp" //Semaphore header
#include "mutex.hpp" //Mutex header


namespace advcpp
{

template<typename T>
class BlockBoundedQ
{
public:
    //ctor, dtor
    explicit BlockBoundedQ(size_t a_capacity);
    ~BlockBoundedQ();

    //avoid using
    BlockBoundedQ(const BlockBoundedQ& a_other) = delete;
    BlockBoundedQ& operator=(const BlockBoundedQ& a_other) = delete;

    //methods
    bool Enqueue(const T& a_item, bool a_priorityEnqueu); //TODO - find better solution than boolian flag 
    bool Dequeue(T& a_dequeuedValue);
    bool IsEmpty();
    bool IsFull();
    size_t GetCapacity() const;
    size_t GetSize() const;    
    void releaseWaitingThreads();

private:
    AtomicValue<size_t> m_capacity;
    AtomicValue<size_t> m_size;
    Semaphore m_freeSlots;
    Semaphore m_takenSlots;
    std::deque<T> m_queue;
    Mutex m_mutex;
    AtomicValue<bool> m_isQueueClosed;
    AtomicValue<size_t> m_WaitingEnqueue;
    AtomicValue<size_t> m_WaitingDequeue;
};

}


#include "block_bounded_q.hxx"
#endif // BLOCK_BOUNDED_Q_HPP_
