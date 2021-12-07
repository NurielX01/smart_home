namespace advcpp
{

const char THREAD_SHARED = 0;
const char NONE = 0;

//ctor, dtor
template<typename T>
BlockBoundedQ<T>::BlockBoundedQ(size_t a_capacity)
: m_capacity(a_capacity)
, m_size(NONE)
, m_freeSlots(THREAD_SHARED, a_capacity)
, m_takenSlots(THREAD_SHARED, NONE)
, m_WaitingEnqueue(NONE) 
, m_WaitingDequeue(NONE) {}
    
template<typename T>
BlockBoundedQ<T>::~BlockBoundedQ()
{
    m_isQueueClosed.Set();
    releaseWaitingThreads();
}


//public methods
template<typename T>
bool BlockBoundedQ<T>::Enqueue(const T& a_item, bool a_priorityEnqueu)
{
    if(m_isQueueClosed.IsOn())
    {
        return false;
    }

    m_WaitingEnqueue++;
    m_freeSlots.Wait();
    m_WaitingEnqueue--;

    m_mutex.Lock();

    if(m_isQueueClosed.IsOn())
    {
        m_mutex.UnLock();
        m_freeSlots.Post();
        return false;
    }

    try
    {
        if(a_priorityEnqueu)
        {
            m_queue.push_front(a_item);    
        }
        else
        {
            m_queue.push_back(a_item);
        }
    }
    catch(...)
    {
        m_freeSlots.Post();
        m_mutex.UnLock();
        throw;
    }

    m_size++;
    m_mutex.UnLock();
    m_takenSlots.Post();

    return true;
}

template<typename T>
bool BlockBoundedQ<T>::Dequeue(T& a_dequeuedValue)
{
    if(m_isQueueClosed.IsOn())
    {
        return false;
    }

    m_WaitingDequeue++;
    m_takenSlots.Wait();
    m_WaitingDequeue--;

    m_mutex.Lock();

    if(m_isQueueClosed.IsOn())
    {
        m_mutex.UnLock();
        m_takenSlots.Post();
        return false;
    }

    try
    {
        a_dequeuedValue = m_queue.front();
        m_queue.pop_front();
    }
    catch(...)
    {
        m_takenSlots.Post();
        m_mutex.UnLock();
        throw;
    }

    m_size--;
    m_mutex.UnLock();
    m_freeSlots.Post();

    return true;
}

template<typename T>
bool BlockBoundedQ<T>::IsEmpty()
{
    m_mutex.Lock();
    if(NONE != m_size.Get())
    {
        m_mutex.UnLock();
        return false;
    }

    m_mutex.UnLock();
    return true;
}

template<typename T>
bool BlockBoundedQ<T>::IsFull()
{
    m_mutex.Lock();
    if(m_capacity.Get() == m_size.Get())
    {
        m_mutex.UnLock();
        return true;
    }

    m_mutex.UnLock();
    return false;
}

template<typename T>
size_t BlockBoundedQ<T>::GetCapacity() const
{
    return m_capacity.Get();
}

template<typename T>
size_t BlockBoundedQ<T>::GetSize() const
{
    return m_size.Get();
}


//private methods
template<typename T>
void BlockBoundedQ<T>::releaseWaitingThreads()
{
    while(0UL != m_WaitingEnqueue.Get())
    {
        m_freeSlots.Post();
    }

    while(0UL != m_WaitingDequeue.Get())
    {
        m_takenSlots.Post();
    }
}

}


