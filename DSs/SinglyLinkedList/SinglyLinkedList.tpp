// SinglyLinkedList.tpp
#ifndef SINGLY_LINKED_LIST_TPP
#define SINGLY_LINKED_LIST_TPP

template <typename T>
SinglyLinkedList<T>::Node::Node(const T &d)
    : data(d), next(nullptr) {}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
{
    create();
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    clear();
}

template <typename T>
void SinglyLinkedList<T>::create()
{
    head = nullptr;
    count = 0;
}

template <typename T>
bool SinglyLinkedList<T>::isEmpty() const
{
    return count == 0;
}

template <typename T>
int SinglyLinkedList<T>::size() const
{
    return count;
}

template <typename T>
void SinglyLinkedList<T>::insertFront(const T &value)
{
    Node *n = new Node(value);
    n->next = head;
    head = n;
    ++count;
}

template <typename T>
void SinglyLinkedList<T>::insertBack(const T &value)
{
    Node *n = new Node(value);
    if (!head)
    {
        head = n;
    }
    else
    {
        Node *curr = head;
        while (curr->next)
            curr = curr->next;
        curr->next = n;
    }
    ++count;
}

template <typename T>
void SinglyLinkedList<T>::insertAfter(Node *node, const T &value)
{
    if (!node)
        return;
    Node *n = new Node(value);
    n->next = node->next;
    node->next = n;
    ++count;
}

template <typename T>
void SinglyLinkedList<T>::removeFront()
{
    if (!head)
        return;
    Node *tmp = head;
    head = head->next;
    delete tmp;
    --count;
}

template <typename T>
void SinglyLinkedList<T>::remove(Node *node)
{
    if (!node || !head)
        return;
    if (node == head)
    {
        removeFront();
        return;
    }
    Node *curr = head;
    while (curr->next && curr->next != node)
        curr = curr->next;
    if (curr->next == node)
    {
        curr->next = node->next;
        delete node;
        --count;
    }
}

template <typename T>
typename SinglyLinkedList<T>::Node *
SinglyLinkedList<T>::find(bool (*predicate)(const T &))
{
    Node *curr = head;
    while (curr)
    {
        if (predicate(curr->data))
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

template <typename T>
void SinglyLinkedList<T>::traverse(void (*fn)(T &))
{
    Node *curr = head;
    while (curr)
    {
        fn(curr->data);
        curr = curr->next;
    }
}

template <typename T>
void SinglyLinkedList<T>::reverse()
{
    Node *prev = nullptr;
    Node *curr = head;
    while (curr)
    {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

template <typename T>
void SinglyLinkedList<T>::clear()
{
    while (head)
        removeFront();
}

#endif
