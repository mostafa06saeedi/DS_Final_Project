#ifndef HASH_TABLE_H
#define HASH_TABLE_H

template <typename T>
class HashMap {
public:
    HashMap(int capacity, float loadFactor);
    int size();
    int capacity();
    const char *hashFunction(key);
    bool put(int key, T value);
    const T &get(int key);
    const T &remove(int key);
    bool containsKey(int key);
    //keys();
    //values
    void clear();
    bool resize(int newCapacity);
private:
};

#include "HashTable.tpp"
#endif