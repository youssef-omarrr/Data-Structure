#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/////////////////////////////////////////////////////////////////////////
/////----- DoubleLinkedList part ------/////
/////////////////////////////////////////////////////////////////////////

// used to use any datatype we want
template <typename T>
class Node
{
public:
    // data of any type
    T data;
    // pointers
    Node *prev;
    Node *next;

    // constructor to init node
    Node(T data)
    {
        this->data = data;
        this->prev = nullptr;
        this->next = nullptr;
    };
};

template <typename T>
class DoubleLinkedList
{
public:
    DoubleLinkedList();  // construct
    ~DoubleLinkedList(); // destructor to free memory

    void add_front(T element);
    void add(T element);
    void addToIndex(int index, T element);
    T get(int index);
    void set(int index, T element);
    void clear();
    bool isEmpty();
    void remove_front();
    void remove_back();
    void remove(int index);
    int size();
    DoubleLinkedList<T> sublist(int from_index, int to_index);
    bool contains(T element);
    void display();

private:
    // a pointer to the FIRST node
    Node<T> *head;
    // a pointer to the LAST node
    Node<T> *tail;
    // to keep track of list size
    int list_size;
};

// init head and tail to be NULL
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
    head = nullptr; // its prev is always NULL
    tail = nullptr; // its next is always NULL
    list_size = 0;
}

// destructor
template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    clear();
}

/////////////////////////////////////////////////////////////////////////
/////----- SingleLinkedList part ------/////
/////////////////////////////////////////////////////////////////////////

template <typename T>
class Node2
{
public:
    // data of any type
    T data;
    // pointers
    Node2 *next;

    // constructor to init node
    Node2(T data)
    {
        this->data = data;
        this->next = nullptr;
    };
};

template <typename T>
class SingleLinkedList
{
public:
    SingleLinkedList();  // construct
    ~SingleLinkedList(); // destructor to free memory

    void add_front(T element);
    void add(T element);
    void addToIndex(int index, T element);
    T get(int index);
    void set(int index, T element);
    void clear();
    bool isEmpty();
    void remove_front();
    void remove_back();
    void remove(int index);
    int size();
    SingleLinkedList<T> sublist(int from_index, int to_index);
    bool contains(T element);
    void display();

private:
    // a pointer to the FIRST node
    Node2<T> *head;
    // a pointer to the LAST node
    Node2<T> *tail;
    // to keep track of list size
    int list_size;
};

// init head and tail to be NULL
template <typename T>
SingleLinkedList<T>::SingleLinkedList()
{
    head = nullptr; // its prev is always NULL
    tail = nullptr; // its next is always NULL
    list_size = 0;
}

// destructor
template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    clear();
}
#endif