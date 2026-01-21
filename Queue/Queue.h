#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>

template <typename T>
class Queue {
public:
    Queue(size_t capacity);
    bool isEmpty();
    int size();
    bool enqueue(T data);
    const T &dequeue();
    const T &peek();
    void clear();
    T &front();
    T &back();

private:
    size_t _size;
    size_t _capacity;
    T *_container;
};

#include "Queue.tpp"
#endif