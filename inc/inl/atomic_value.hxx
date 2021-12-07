#ifndef ATOMIC_VALUE_HXX_
#define ATOMIC_VALUE_HXX_


namespace advcpp
{

// template version methods
template<typename T>
AtomicValue<T>::AtomicValue(T a_value)
{
    Set(a_value);
}

template<typename T>
T AtomicValue<T>::Get() const 
{
    return __sync_fetch_and_add(&m_value, T(0));
}

template<typename T>
void AtomicValue<T>::Set(T a_newValue)
{
    T oldValue;
    T actualOldValue;
    do
    {   
        oldValue = Get();
        actualOldValue = __sync_val_compare_and_swap(&m_value, oldValue, a_newValue);
    } while (actualOldValue != oldValue);
}

template<typename T>
T AtomicValue<T>::operator++()
{
    return operator+=(1);
}

template<typename T>
T AtomicValue<T>::operator++(int)
{
    return __sync_fetch_and_add(&m_value, 1);
}

template<typename T>
T AtomicValue<T>::operator+=(T a_addedVal)
{
    return __sync_add_and_fetch(&m_value, a_addedVal);
}

template<typename T>
T AtomicValue<T>::operator-=(T a_subtractedVal)
{
    return __sync_sub_and_fetch(&m_value, a_subtractedVal);
}

template<typename T>
T AtomicValue<T>::operator--()
{
    return operator-=(1);
}

template<typename T>
T AtomicValue<T>::operator--(int)
{
    return __sync_fetch_and_sub(&m_value, 1);
}


// bool specialization version methods
inline AtomicValue<bool>::AtomicValue(bool a_status)
: m_status(a_status) {}

inline bool AtomicValue<bool>::IsOn() const
{
    return __sync_and_and_fetch(&m_status, true);
}

inline void AtomicValue<bool>::Toggle()
{ 
    __sync_xor_and_fetch(&m_status, true);
}

inline void AtomicValue<bool>::Set()
{
    __sync_or_and_fetch(&m_status, true); 
}

inline bool AtomicValue<bool>::TrySet()
{
    return __sync_bool_compare_and_swap(&m_status, false, true);
}

}


#endif // ATOMIC_VALUE_HXX_