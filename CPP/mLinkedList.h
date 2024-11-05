#ifndef mLinkedList
#define mLinkedList

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
    void add_back(T element);
    void add_index(int index, T element);
    T get(int index);
    void set(int index, T elemnet);
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

#endif