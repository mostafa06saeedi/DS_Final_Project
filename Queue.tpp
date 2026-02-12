#include "Queue.h"
template <typename T>
Queue<T>::Queue(size_t capacity)
    : _size(0), _capacity(capacity), _container(new T[capacity]), _dindex(0), _eindex(0) {}

template <typename T>
Queue<T>::~Queue()
{
    delete[] _container;
}

template <typename T>
bool Queue<T>::isEmpty() const
{
    return _size == 0;
}

template <typename T>
size_t Queue<T>::size() const
{
    return _size;
}

template <typename T>
bool Queue<T>::enqueue(const T &data)
{
    if (_size >= _capacity)
    {
        return false;
    }

    _container[_eindex] = data;
    _eindex = (_eindex + 1) % _capacity;
    _size++;
    return true;
}

template <typename T>
void Queue<T>::dequeue()
{
    if (isEmpty())
    {
        throw std::out_of_range("Queue is empty");
    }

    _dindex = (_dindex + 1) % _capacity;
    _size--;
}

template <typename T>
const T &Queue<T>::peek() const
{
    if (isEmpty())
    {
        throw std::out_of_range("Queue is empty");
    }
    return _container[_dindex];
}

template <typename T>
T &Queue<T>::front()
{
    if (isEmpty())
    {
        throw std::out_of_range("Queue is empty");
    }
    return _container[_dindex];
}

template <typename T>
T &Queue<T>::back()
{
    if (isEmpty())
    {
        throw std::out_of_range("Queue is empty");
    }
    size_t lastIndex = (_eindex == 0) ? (_capacity - 1) : (_eindex - 1);
    return _container[lastIndex];
}

template <typename T>
void Queue<T>::clear()
{
    _eindex = 0;
    _dindex = 0;
    _size = 0;
}