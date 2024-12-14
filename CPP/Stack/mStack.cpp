#include "mStack.h"
#include <iostream>
#include <stdexcept> // For exceptions

template <typename T>
T Stack<T>::pop()
{
    if (stack_size == 0)
    {
        throw std::runtime_error("Error");
    }

    // save current top data to be sent
    Node<T> *current = top;
    T data = current->data;

    // update stack
    top = top->down;
    stack_size--;

    // free memory and return data
    delete current;
    return data;
}

template <typename T>
T Stack<T>::peek()
{
    if (stack_size == 0)
    {
        throw std::runtime_error("Error");
    }

    return top->data;
}

template <typename T>
void Stack<T>::push(T element)
{
    // create new node
    Node<T> *newNode = new Node<T>(element);

    // stack is NOT empty
    if (top != nullptr && stack_size != 0)
    {
        newNode->down = top;
    }

    // update stack
    top = newNode;
    stack_size++;
}

template <typename T>
bool Stack<T>::isEmpty()
{
    return stack_size == 0;
}

template <typename T>
int Stack<T>::size()
{
    return stack_size;
}

template <typename T>
void Stack<T>::clear()
{
    Node<T> *current = top;

    while (current != nullptr)
    {
        Node<T> *NextNode = current->down;
        delete current;
        current = NextNode;
    }

    // reset stack
    top = nullptr;
    stack_size = 0;
}

// a function to test if elements have been stored correctly in the stack
template <typename T>
void Stack<T>::testSTACK(char mode)
{
    if (mode == 'a')
    {
        Node<T> *current = top;
        std::cout << "Top -> ";

        while (current != nullptr)
        {
            std::cout << "[" << current->data << "] -> ";
            current = current->down;
        }
        std::cout << "NULL";
    }
    else if (mode == 'b')
    {
        Node<T> *current = top;
        std::cout << "[";

        while (current->down != nullptr)
        {
            std::cout << current->data << ", ";
            current = current->down;
        }

        std::cout << current->data << "]";
    }
}
