#ifndef mSTACK
#define mSTACK

// used to use any datatype we want
template <typename T>
class Node
{
public:
    // data of any type
    T data;
    // pointers
    Node *down;

    // constructor to init node
    Node(T data)
    {
        this->data = data;
        this->down = nullptr;
    };
};

template <typename T>
class Stack
{
public:
    Stack();  // construct
    ~Stack(); // destructor to free memory

    T    pop();
    T    peek();
    void push(T element);

    bool isEmpty();
    int  size();
    void clear();

    void testSTACK(char mode);


private:
    // a pointer to the top node in the stack
    Node<T> *top;
    int stack_size;
};

// init top to be NULL
template <typename T>
Stack<T>::Stack()
{
    top = nullptr;
    stack_size = 0;
}

// destructor
template <typename T>
Stack<T>::~Stack()
{
    clear();
}
#endif