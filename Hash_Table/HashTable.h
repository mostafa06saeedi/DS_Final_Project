#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstddef>
#include <string>

template <typename T>
class HashMap {
public:
    HashMap(int capacity = 16, float loadFactor = 0.75f);
    ~HashMap();
    size_t size() const;
    size_t capacity() const;
    size_t hashFunction(const std::string &key) const;
    bool put(const std::string &key, const T &value);
    const T &get(int key);
    const T &remove(int key);
    bool containsKey(int key);
    //keys();
    //values
    void clear();
    bool resize(int newCapacity);
private:
    struct Node {
        std::string key;
        T value;
        Node* next;
        Node();
        Node(std::string k, T v);
    };
    
    Node** _buckets;
    size_t _size;
    size_t _capacity;
    float _loadFactor;
    
    void _rehash();
};

#include "HashTable.tpp"
#endif