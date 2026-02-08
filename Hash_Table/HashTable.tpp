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

template <typename T>
size_t HashMap<T>::size() const {
    return _size;
}

template <typename T>
size_t HashMap<T>::capacity() const {
    return _capacity;
}

template<typename T>
size_t HashMap<T>::hashFunction(const std::string &key) const {
    size_t seed = 5381;
    for (char c : key) {
        seed = ((seed << 5) + seed) + static_cast<unsigned char>(c);
    }   
    return seed % _capacity;
}

template<typename T>
bool HashMap<T>::put(const std::string &key, const T &value) {
    size_t index = hashFunction(key);

    Node *current = _buckets[index];
    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;
            return true;
        }
        current = current->next;
    }
    
    Node *newNode = new Node();
    newNode->key = key;
    newNode->value = value;
    newNode->next = _buckets[index]; 
    _buckets[index] = newNode;       
    
    _size++;
    return true;
}

template<typename T>
T *HashMap<T>::get(std::string key) const {
    Node *node = _buckets[hashFunction(key)];
    while (node != nullptr) {
        if (node->key == key) return &node->value;
        node = node->next;
    }
    return nullptr;
}

template<typename T>
bool HashMap<T>::remove(const std::string &key) {
    if (_size == 0) {
        return false;
    }
    
    size_t index = hashFunction(key);
    Node *current = _buckets[index];
    
    if (current != nullptr && current->key == key) {
        _buckets[index] = current->next;
        delete current;
        _size--;
        return true;
    }
    
    Node* prev = current;
    if (prev != nullptr) {
        current = prev->next;
    }
    
    while (current != nullptr) {
        if (current->key == key) {
            prev->next = current->next;
            delete current;
            _size--;
            return true;
        }
        
        prev = current;
        current = current->next;
    }
    
    return false;
}

template<typename T>
bool HashMap<T>::containsKey(const std::string &key) const {
    if (_size == 0) {
        return false;
    }
    
    size_t index = hashFunction(key);
    Node* current = _buckets[index];
    
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

template<typename T>
HashMap<T>::Node::Node(std::string k, T v): key(k), value(v), next(nullptr) {}

template<typename T>
HashMap<T>::Node::Node(): key(std::string()), next(nullptr) {}

template<typename T>
HashMap<T>::Node::~Node() {
    if constexpr (std::is_pointer<T>::value) {
        if (value != nullptr) delete value;
    }
}