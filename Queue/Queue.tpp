template <typename T>
Queue<T>::Queue(size_t capacity): _container(new T[capacity]), _capacity(capacity), _size(0) {}