// SinglyLinkedList.h
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <string>

template <typename T>
class SinglyLinkedList
{
public:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &d);
    };

private:
    Node *head;
    int count;

public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    SinglyLinkedList(const SinglyLinkedList &) = delete;
    SinglyLinkedList &operator=(const SinglyLinkedList &) = delete;

    void create();
    void clear();

    bool isEmpty() const;
    int size() const;

    Node *getHead() const { return head; }

    void insertFront(const T &);
    void insertBack(const T &);
    void insertAfter(Node *, const T &);

    void remove(Node *);
    void removeFront();

    Node *find(bool (*predicate)(const T &));
    void traverse(void (*fn)(T &));

    void reverse();
};

#include "SinglyLinkedList.tpp"

#endif
