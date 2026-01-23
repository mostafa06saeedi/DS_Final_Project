#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>
#include <cstring>
#include <stdexcept>

template <typename T>
class Queue {
public:
    Queue(size_t capacity);
    bool isEmpty() const;
    size_t size() const;
    bool enqueue(const T &data);
    void dequeue();
    const T &peek();
    void clear();
    T &front();
    T &back();

private:
    size_t _size;
    size_t _capacity;
    T *_container;
    size_t _dindex; //has an instance(full slot)
    size_t _eindex; //empty slot
};

#include "Queue.tpp"
#endif