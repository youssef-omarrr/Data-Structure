#ifndef mQueue
#define mQueue

#include <vector>

// used to use any datatype we want
template <typename T>
class Node
{
public:
    // data of any type
    T data;
    // pointers
    Node *next;

    // constructor to init node
    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
    };
};

///////////////////////////////////////////////////////////////////////////
/////////////////////      PARENT             /////////////////////////////
///////////////////////////////////////////////////////////////////////////

template <typename T>
class Queue
{
public:
    Queue(); // construct

    virtual void enqueue(T element);
    virtual T dequeue();

    virtual bool isEmpty();
    virtual int size();

    virtual void printQueue();

private:
    // 2 pointers to point to the front and the rear
    Node<T> *front;
    Node<T> *rear;
    int queue_size;
};

///////////////////////////////////////////////////////////////////////////
/////////////////////      INHERTENCE         /////////////////////////////
///////////////////////////////////////////////////////////////////////////

template <typename T>
class ILinkedBased : public Queue<T>
{
public:
    ILinkedBased(); // construct

    void enqueue(T element) override;
    T dequeue() override;

    bool isEmpty() override;
    int size() override;

    void printQueue() override;

private:
    // 2 pointers to point to the front and the rear
    Node<T> *front;
    Node<T> *rear;
    int queue_size;
};

template <typename T>
class IArrayBased : public Queue<T>
{
public:
    IArrayBased(); // construct

    void enqueue(T element) override;
    T dequeue() override;

    bool isEmpty() override;
    int size() override;

    void printQueue() override;

private:
    int queue_size;
    std::vector<T> vec; // empty vector of integers
};

///////////////////////////////////////////////////////////////////////////
/////////////////          CONSTUCORS          ////////////////////////////
///////////////////////////////////////////////////////////////////////////

// init pointers to be NULL
template <typename T>
Queue<T>::Queue()
{
    front = nullptr;
    rear = nullptr;
    queue_size = 0;
}

// init pointers to be NULL
template <typename T>
ILinkedBased<T>::ILinkedBased()
{
    front = nullptr;
    rear = nullptr;
    queue_size = 0;
}

// init pointers to be NULL
template <typename T>
IArrayBased<T>::IArrayBased()
{
    queue_size = 0;
}

#endif