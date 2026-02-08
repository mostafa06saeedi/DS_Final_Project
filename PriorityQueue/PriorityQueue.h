// PriorityQueue.h
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <string>

template <typename T>
class PriorityQueue
{
private:
    T *data;
    int capacity;
    int count;
    bool (*cmp)(const T &, const T &); // comparator: returns true if a has higher priority than b

    void resize();
    void heapifyUp(int);
    void heapifyDown(int);

public:
    PriorityQueue();
    ~PriorityQueue();

    PriorityQueue(const PriorityQueue &) = delete;
    PriorityQueue &operator=(const PriorityQueue &) = delete;

    // Must call create and provide comparator before push/peek/pop.
    void create(bool (*comparator)(const T &, const T &));
    void clear();

    bool isEmpty() const;
    int size() const;

    // Precondition: !isEmpty()
    T &peek();
    void push(const T &);
    void pop();
};

#include "PriorityQueue.tpp"

#endif
