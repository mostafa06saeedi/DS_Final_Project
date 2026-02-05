#include "HashTable.h"

template <typename T>
HashMap<T>::HashMap(int capacity, float loadFactor) 
           : _size(0), _capacity(capacity > 0 ? capacity : 16)
           , _loadFactor(loadFactor > 0 ? loadFactor : 0.75f) {

    _buckets = new Node*[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
        _buckets[i] = nullptr;
    }
}

template <typename T>
void HashMap<T>::clear() {
    for (size_t i = 0; i < _capacity; ++i) {
        Node *current = _buckets[i];
        while (current != nullptr) {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
        _buckets[i] = nullptr;
    }
    _size = 0;
}

template <typename T>
HashMap<T>::~HashMap() {
    clear();
    delete[] _buckets;
}

template<typename T>
HashMap<T>::Node::Node(int k, T v): key(k), value(v), next(nullptr) {}
