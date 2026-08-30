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
    bool (*cmp)(const T &, const T &);

    void resize();
    void heapifyUp(int);
    void heapifyDown(int);

public:
    PriorityQueue();
    ~PriorityQueue();

    PriorityQueue(const PriorityQueue &) = delete;
    PriorityQueue &operator=(const PriorityQueue &) = delete;

    void create(bool (*comparator)(const T &, const T &));
    void clear();

    bool isEmpty() const;
    int size() const;

    T &peek();
    const T &peek() const;
    void push(const T &);
    void pop();

    T getAt(int index) const
    {
        if (index >= 0 && index < count)
        {
            return data[index];
        }
        return T();
    }
    int getCount() const { return count; }
};

#include "PriorityQueue.tpp"

#endif
