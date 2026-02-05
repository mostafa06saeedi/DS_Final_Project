#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstddef>

template <typename T>
class HashMap {
public:
    HashMap(int capacity = 16, float loadFactor = 0.75f);
    ~HashMap();
    int size();
    int capacity();
    // const char *hashFunction(key);
    bool put(int key, T value);
    const T &get(int key);
    const T &remove(int key);
    bool containsKey(int key);
    //keys();
    //values
    void clear();
    bool resize(int newCapacity);
private:
    struct Node {
        int key;
        T value;
        Node* next;
        Node(int k, T v);
    };
    
    Node** _buckets;
    size_t _size;
    size_t _capacity;
    float _loadFactor;
    
    void _rehash();
};

#include "HashTable.tpp"
#endif