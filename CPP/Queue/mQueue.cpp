#include "mQueue.h"
#include <iostream>
#include <stdexcept>
#include <stack>

///////////////////////////////////////////////////////////////////////////
/////////////////////      PARENT             /////////////////////////////
///////////////////////////////////////////////////////////////////////////

template <typename T>
void Queue<T>::enqueue(T element)
{
    throw std::runtime_error("Error");
}
template <typename T>
T Queue<T>::dequeue()
{
    throw std::runtime_error("Error");
}

template <typename T>
bool Queue<T>::isEmpty()
{
    return true;
}

template <typename T>
int Queue<T>::size()
{
    return 0;
}

template <typename T>
void Queue<T>::printQueue()
{
    std::cout << "[]";
}

///////////////////////////////////////////////////////////////////////////
/////////////////////      INHERTENCE         /////////////////////////////
///////////////////////////////////////////////////////////////////////////

template <typename T>
void ILinkedBased<T>::enqueue(T element)
{
    try
    {
        // create new node
        Node<T> *newNode = new Node<T>(element);

        // queue is NOT empty
        if (front != nullptr && rear != nullptr && queue_size != 0)
        {
            rear->next = newNode;
            rear = newNode;
        }
        // queue is empty
        else
        {
            front = rear = newNode;
        }

        // update queue
        queue_size++;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Error" << std::endl;
    }
}

template <typename T>
T ILinkedBased<T>::dequeue()
{
    if (queue_size == 0)
    {
        throw std::runtime_error("Error");
    }

    // save current front data to be sent
    Node<T> *current = front;
    T data = current->data;

    // update queue
    front = front->next;
    queue_size--;

    // free memory and return data
    delete current;
    return data;
}

template <typename T>
bool ILinkedBased<T>::isEmpty()
{
    return queue_size == 0;
}

template <typename T>
int ILinkedBased<T>::size()
{
    return queue_size;
}

template <typename T>
void ILinkedBased<T>::printQueue()
{
    if (front == nullptr)
    {
        std::cout << "[]";
        return;
    }

    std::stack<T> stack;
    Node<T> *current = front;

    // push all elements onto the stack
    while (current != nullptr)
    {
        stack.push(current->data);
        current = current->next;
    }

    std::cout << "[";
    while (!stack.empty())
    {
        std::cout << stack.top();
        stack.pop();
        if (!stack.empty())
            std::cout << ", ";
    }
    std::cout << "]";
}

///////////////////////////////////////////////////////////////////////////
/////////////////////      INHERTENCE         /////////////////////////////
///////////////////////////////////////////////////////////////////////////

template <typename T>
void IArrayBased<T>::enqueue(T element)
{
    try
    {
        vec.push_back(element);
        // update queue
        queue_size++;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Error" << std::endl;
    }
}

template <typename T>
T IArrayBased<T>::dequeue()
{
    if (queue_size == 0)
    {
        throw std::runtime_error("Error");
    }

    // get last element
    T ans = vec[0];

    // pop it (delete it)
    vec.erase(vec.begin());

    queue_size--;

    return ans;
}

template <typename T>
bool IArrayBased<T>::isEmpty()
{
    return queue_size == 0;
}

template <typename T>
int IArrayBased<T>::size()
{
    return queue_size;
}

template <typename T>
void IArrayBased<T>::printQueue()
{
    if (vec.empty())
    {
        std::cout << "[]";
        return;
    }

    std::cout << "[";
    // loop through the vector in reverse order using reverse iterators
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
    {
        std::cout << *it;
        if (it + 1 != vec.rend()) // check if it's not the last element
            std::cout << ", ";    // print a comma between elements
    }
    std::cout << "]";
}