#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue {
public:
    Queue();
    bool isEmpty();
    int size();
    bool enqueue(T data);
    const T &dequeue();
    const T &peek();
    void clear();
    T &front();
    T &back();

private:

};

#include "Queue.tpp"
#endif