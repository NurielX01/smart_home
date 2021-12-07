#ifndef ATOMIC_VALUE_HPP_
#define ATOMIC_VALUE_HPP_


namespace advcpp
{

// This class should only be used with the following T typenames:
// int, long and their unsigned counterparts  
template<typename T>
class AtomicValue
{
public:
    // ctor, dtor
    AtomicValue(T a_value);
    ~AtomicValue() = default;

    // prevented default
    AtomicValue(const AtomicValue& a_other) = delete;
    AtomicValue& operator=(const AtomicValue& a_other) = delete;

    // methods
    T Get() const;
    void Set(T a_newValue);

    //operators
    T operator++(); //prefix
    T operator++(int); //postfix
    T operator--(); //prefix
    T operator--(int); //postfix
    T operator-=(T a_subtractedVal);
    T operator+=(T a_addedVal);

private:
    mutable T m_value;
};

template<>
class AtomicValue<bool>
{
public:
    // ctor, dtor
    AtomicValue(bool a_status = false);
    ~AtomicValue() = default;

    // prevented default
    AtomicValue(const AtomicValue& a_status) = delete;
    AtomicValue& operator=(const AtomicValue& a_other) = delete;

    // methods
    bool IsOn() const;
    void Toggle();
    void Set();
    bool TrySet();

private:
    mutable unsigned char m_status;
};

}


#include "atomic_value.hxx"
#endif //ATOMIC_VALUE_HPP_
