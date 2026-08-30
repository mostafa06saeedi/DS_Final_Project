#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <functional>
#include <cstddef>

template <typename T>
class DoublyLinkedList
{
public:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;

        explicit Node(const T &d);
    };

private:
    Node *head;
    Node *tail;
    size_t count;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList &) = delete;
    DoublyLinkedList &operator=(const DoublyLinkedList &) = delete;

    DoublyLinkedList(DoublyLinkedList &&other) noexcept;
    DoublyLinkedList &operator=(DoublyLinkedList &&other) noexcept;

    bool isEmpty() const;
    size_t size() const;

    Node *getHead() const { return head; }
    Node *getTail() const { return tail; }

    void insertFront(const T &value);
    void insertBack(const T &value);
    void insertAfter(Node *node, const T &value);
    void insertBefore(Node *node, const T &value);

    void remove(Node *node);
    void removeFront();
    void removeBack();

    Node *find(std::function<bool(const T &)> predicate) const;

    void traverseForward(std::function<void(T &)> fn);
    void traverseBackward(std::function<void(T &)> fn);

    void clear();
};

#include "DoublyLinkedList.tpp"

#endif
