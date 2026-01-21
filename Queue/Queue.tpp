template <typename T>
Queue<T>::Queue(size_t capacity): _container(new T[capacity]), _capacity(capacity), _size(0) {}

template<typename T>
bool Queue<T>::isEmpty() const {
    return _size == 0;
}

template<typename T>
size_t Queue<T>::size() const {
    return _size;
}