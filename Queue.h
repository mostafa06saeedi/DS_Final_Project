#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>
#include <stdexcept>

template <typename T>
class Queue
{
private:
    size_t _size;
    size_t _capacity;
    T *_container;
    size_t _dindex;
    size_t _eindex;

public:
    Queue(size_t capacity);
    ~Queue() { delete[] _container; }
    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;

    bool isEmpty() const { return _size == 0; }
    size_t size() const { return _size; }

    bool enqueue(const T &data);
    void dequeue();

    const T &peek() const
    {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return _container[_dindex];
    }

    T &front()
    {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return _container[_dindex];
    }

    T &back()
    {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return _container[(_eindex - 1 + _capacity) % _capacity];
    }

    void clear();
};

#include "Queue.tpp"
#endif