template <typename T>
SinglyLinkedList<T>::Node::Node(const T &d)
    : data(d), next(nullptr)
{
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
    : head(nullptr), count(0)
{
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
void SinglyLinkedList<T>::clear()
{
    while (!isEmpty())
        removeFront();
}

template <typename T>
bool SinglyLinkedList<T>::isEmpty() const
{
    return head == nullptr;
}

template <typename T>
int SinglyLinkedList<T>::size() const
{
    return count;
}

template <typename T>
void SinglyLinkedList<T>::insertFront(const T &value)
{
    Node *newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    count++;
}

template <typename T>
void SinglyLinkedList<T>::insertBack(const T &value)
{
    Node *newNode = new Node(value);

    if (isEmpty())
    {
        head = newNode;
    }
    else
    {
        Node *current = head;
        while (current->next)
            current = current->next;

        current->next = newNode;
    }

    count++;
}

template <typename T>
void SinglyLinkedList<T>::insertAfter(Node *node, const T &value)
{
    if (!node)
        return;

    Node *newNode = new Node(value);
    newNode->next = node->next;
    node->next = newNode;
    count++;
}

template <typename T>
void SinglyLinkedList<T>::removeFront()
{
    if (isEmpty())
        return;

    Node *temp = head;
    head = head->next;
    delete temp;
    count--;
}

template <typename T>
void SinglyLinkedList<T>::remove(Node *node)
{
    if (!node || isEmpty())
        return;

    if (node == head)
    {
        removeFront();
        return;
    }

    Node *current = head;
    while (current && current->next != node)
        current = current->next;

    if (current)
    {
        current->next = node->next;
        delete node;
        count--;
    }
}

template <typename T>
typename SinglyLinkedList<T>::Node *
SinglyLinkedList<T>::find(bool (*predicate)(const T &))
{
    Node *current = head;

    while (current)
    {
        if (predicate(current->data))
            return current;

        current = current->next;
    }

    return nullptr;
}

template <typename T>
const typename SinglyLinkedList<T>::Node *
SinglyLinkedList<T>::find(bool (*predicate)(const T &)) const
{
    Node *current = head;

    while (current)
    {
        if (predicate(current->data))
            return current;

        current = current->next;
    }

    return nullptr;
}

template <typename T>
void SinglyLinkedList<T>::traverse(void (*fn)(T &))
{
    Node *current = head;

    while (current)
    {
        fn(current->data);
        current = current->next;
    }
}

template <typename T>
void SinglyLinkedList<T>::traverse(void (*fn)(T &)) const
{
    Node *current = head;

    while (current)
    {
        fn(current->data);
        current = current->next;
    }
}

template <typename T>
void SinglyLinkedList<T>::reverse()
{
    Node *prev = nullptr;
    Node *current = head;
    Node *next = nullptr;

    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
}
