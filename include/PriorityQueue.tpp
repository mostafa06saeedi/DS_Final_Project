
#ifndef PRIORITY_QUEUE_TPP
#define PRIORITY_QUEUE_TPP

template <typename T>
PriorityQueue<T>::PriorityQueue()
    : data(nullptr), capacity(0), count(0), cmp(nullptr) {}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    clear();
}

template <typename T>
void PriorityQueue<T>::create(bool (*comparator)(const T &, const T &))
{
    cmp = comparator;
    capacity = 16;
    count = 0;
    data = new T[capacity];
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
    return count == 0;
}

template <typename T>
int PriorityQueue<T>::size() const
{
    return count;
}

template <typename T>
T &PriorityQueue<T>::peek()
{
    return data[0];
}

template <typename T>
const T &PriorityQueue<T>::peek() const
{
    return data[0];
}

template <typename T>
void PriorityQueue<T>::resize()
{
    int newCap = (capacity == 0) ? 16 : capacity * 2;
    T *newData = new T[newCap];
    for (int i = 0; i < count; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCap;
}

template <typename T>
void PriorityQueue<T>::heapifyUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (cmp(data[index], data[parent]))
        {
            T tmp = data[index];
            data[index] = data[parent];
            data[parent] = tmp;
            index = parent;
        }
        else
            break;
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(int index)
{
    while (true)
    {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int best = index;

        if (left < count && cmp(data[left], data[best]))
            best = left;
        if (right < count && cmp(data[right], data[best]))
            best = right;

        if (best != index)
        {
            T tmp = data[index];
            data[index] = data[best];
            data[best] = tmp;
            index = best;
        }
        else
            break;
    }
}

template <typename T>
void PriorityQueue<T>::push(const T &value)
{
    if (!cmp)
        return;
    if (count == capacity)
        resize();
    data[count] = value;
    heapifyUp(count);
    ++count;
}

template <typename T>
void PriorityQueue<T>::pop()
{
    if (!cmp || isEmpty())
        return;
    data[0] = data[count - 1];
    --count;
    if (count > 0)
        heapifyDown(0);
}

template <typename T>
void PriorityQueue<T>::clear()
{
    delete[] data;
    data = nullptr;
    capacity = 0;
    count = 0;
    cmp = nullptr;
}

#endif
