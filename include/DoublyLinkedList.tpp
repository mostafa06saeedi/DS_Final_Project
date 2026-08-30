#ifndef DOUBLY_LINKED_LIST_TPP
#define DOUBLY_LINKED_LIST_TPP

template <typename T>
DoublyLinkedList<T>::Node::Node(const T &d)
    : data(d), prev(nullptr), next(nullptr) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head(nullptr), tail(nullptr), count(0)
{
}


template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
}

// template <typename T>
// void DoublyLinkedList<T>::create()
// {
//     head = tail = nullptr;
//     count = 0;
// }

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const
{
    return count == 0;
}

template <typename T>
size_t DoublyLinkedList<T>::size() const
{
    return count;
}


template <typename T>
void DoublyLinkedList<T>::insertFront(const T &value)
{
    Node *n = new Node(value);
    n->next = head;
    if (head)
        head->prev = n;
    head = n;
    if (!tail)
        tail = n;
    ++count;
}

template <typename T>
void DoublyLinkedList<T>::insertBack(const T &value)
{
    Node *n = new Node(value);
    n->prev = tail;
    if (tail)
        tail->next = n;
    tail = n;
    if (!head)
        head = n;
    ++count;
}

template <typename T>
void DoublyLinkedList<T>::insertAfter(Node *node, const T &value)
{
    if (!node)
        return;
    Node *n = new Node(value);
    n->prev = node;
    n->next = node->next;
    if (node->next)
        node->next->prev = n;
    node->next = n;
    if (tail == node)
        tail = n;
    ++count;
}

template <typename T>
void DoublyLinkedList<T>::insertBefore(Node *node, const T &value)
{
    if (!node)
        return;
    Node *n = new Node(value);
    n->next = node;
    n->prev = node->prev;
    if (node->prev)
        node->prev->next = n;
    node->prev = n;
    if (head == node)
        head = n;
    ++count;
}

template <typename T>
void DoublyLinkedList<T>::remove(Node* node)
{
    if (!node || isEmpty())
        return;

    if (node->prev)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        tail = node->prev;

    delete node;
    --count;
}

template <typename T>
void DoublyLinkedList<T>::removeFront()
{
    if (isEmpty())
        return;
    remove(head);
}

template <typename T>
void DoublyLinkedList<T>::removeBack()
{
    if (isEmpty())
        return;
    remove(tail);
}

template <typename T>
typename DoublyLinkedList<T>::Node*
DoublyLinkedList<T>::find(std::function<bool(const T&)> predicate) const
{
    Node* curr = head;
    while (curr)
    {
        if (predicate(curr->data))
            return curr;
        curr = curr->next;
    }
    return nullptr;
}


template <typename T>
void DoublyLinkedList<T>::traverseForward(std::function<void(T&)> fn)
{
    Node* curr = head;
    while (curr)
    {
        fn(curr->data);
        curr = curr->next;
    }
}


template <typename T>
void DoublyLinkedList<T>::traverseBackward(std::function<void(T&)> fn)
{
    Node* curr = tail;
    while (curr)
    {
        fn(curr->data);
        curr = curr->prev;
    }
}


template <typename T>
void DoublyLinkedList<T>::clear()
{
    Node *curr = head;
    while (curr)
    {
        Node *next = curr->next;
        delete curr;
        curr = next;
    }
    head = tail = nullptr;
    count = 0;
}

#endif
