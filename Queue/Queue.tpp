template <typename T>
Queue<T>::Queue(size_t capacity): _container(new T[capacity]), _capacity(capacity), _size(0), _eindex(0), _dindex(0) {}

template<typename T>
bool Queue<T>::isEmpty() const {
    return _size == 0;
}

template<typename T>
size_t Queue<T>::size() const {
    return _size;
}

template<typename T>
bool Queue<T>::enqueue(const T &data) { 
    if(_size >= _capacity) {
        return false;
        //doubling the capacity if maximum size exceeded
        //     T *temp = new T[_capacity * 2];
            
        //     //copying the first part of the container 
        //     std::memcpy(temp, _container + _dindex, (_capacity - _dindex) * sizeof(T));
            
        //     //copying the second part of the container
        //     std::memcpy(temp + (_capacity - _dindex), _container, _eindex * sizeof(T));
            
        //     delete[] _container;
        //     _container = temp;
            
        //     _eindex = _size - 1;
        //     _dindex = 0;
        //     _capacity *= 2;
        }
    
        _container[_eindex] = data;
        _size++;
        
        //circular buffer implementation - also increasing _eindex
        _eindex = (_eindex + 1) % _capacity;
        return true;
}