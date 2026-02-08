#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <string>

template <typename T>
class DoublyLinkedList
{
public:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
        Node(const T &d);
    };

private:
    Node *head;
    Node *tail;
    int count;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList &) = delete;
    DoublyLinkedList &operator=(const DoublyLinkedList &) = delete;

    void create();
    bool isEmpty() const;
    int size() const;

    void insertFront(const T &);
    void insertBack(const T &);
    void insertAfter(Node *, const T &);
    void insertBefore(Node *, const T &);

    void remove(Node *);
    void removeFront();
    void removeBack();

    Node *find(bool (*predicate)(const T &));
    void traverseForward(void (*fn)(T &));
    void traverseBackward(void (*fn)(T &));

    void clear();
    Node *getHead() const { return head; }
    Node *getTail() const { return tail; }
};

#include "DoublyLinkedList.tpp"

#endif
