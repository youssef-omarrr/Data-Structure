#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

////////////////  HEADER ////////////////////////////////
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

    T pop();
    T peek();
    void push(T element);

    bool isEmpty();
    int size();
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
////////////////  HEADER ////////////////////////////////

////////////////  STACK CODE ////////////////////////////////

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
    try
    {
        // create new node
        Node<T> *newNode = new Node<T>(element);

        if (newNode == nullptr)
        {
            std::cout << "Error";
        }

        // stack is NOT empty
        if (top != nullptr && stack_size != 0)
        {
            newNode->down = top;
        }

        // update stack
        top = newNode;
        stack_size++;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Error" << std::endl;
    }
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
        if (top == nullptr)
        {
            std::cout << "[]";
            return;
        }

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

////////////////  STACK CODE ////////////////////////////////

////////////////  MAIN CODE ////////////////////////////////

// function to parse input and add it to stack in reverse order
template <typename T>
void getdata(Stack<T> &stack, const std::string &input)
{
    std::string data = input;

    // remove brackets '[' and ']' from the string
    data.erase(std::remove(data.begin(), data.end(), '['), data.end());
    data.erase(std::remove(data.begin(), data.end(), ']'), data.end());

    std::stringstream ss(data);
    std::string item;
    std::vector<T> elements;

    // split by commas and add each element to the vector
    while (std::getline(ss, item, ','))
    {
        // Remove whitespace around item
        item.erase(0, item.find_first_not_of(" \t"));
        item.erase(item.find_last_not_of(" \t") + 1);

        // convert item to integer and add to the vector
        try
        {
            T value = static_cast<T>(std::stoi(item));
            elements.push_back(value);
        }
        catch (const std::exception &)
        {
            throw std::runtime_error("Error");
        }
    }

    // push elements onto the stack in reverse order
    for (auto it = elements.rbegin(); it != elements.rend(); ++it)
    {
        stack.push(*it);
    }

    // for testing
    //  stack.testSTACK('b');
}

int main()
{
    Stack<int> stack;
    std::string line;

    try
    {
        // read the first line for list elements
        if (std::getline(std::cin, line) && !line.empty())
            getdata(stack, line);
        else
        {
            std::cout << "Error";
            return 1;
        }
    }
    catch (const std::runtime_error &e)
    {
        // Print the error message if an exception is caught
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // read the second line for operation type
    std::string operation;
    std::getline(std::cin, operation);
    try
    {
        if (operation == "push")
        {
            // read the third line element to push
            std::string pushValue;
            try
            {
                if (std::getline(std::cin, pushValue) && !pushValue.empty())
                {
                    size_t pos = 0;
                    int element = std::stoi(pushValue, &pos);
                    
                    if (pos != pushValue.length()){
                        std::cout << "Error";
                        return 0;
                    }
                        
                    stack.push(element);
                    stack.testSTACK('b'); // print the stack after the push
                    std::cout << std::endl;
                }
                else
                    std::cout << "Error";
            }
            catch (const std::invalid_argument &)
            {
                std::cout << "Error" << std::endl;
            }
        }
        else if (operation == "pop")
        {
            stack.pop();
            stack.testSTACK('b'); // print the stack after the pop
            std::cout << std::endl;
        }
        else if (operation == "peek")
        {
            std::cout << stack.peek() << std::endl;
        }
        else if (operation == "isEmpty")
        {
            std::cout << (stack.isEmpty() ? "True" : "False") << std::endl;
        }
        else if (operation == "size")
        {
            std::cout << stack.size() << std::endl;
        }
        else
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
    }
    catch (const std::runtime_error &e)
    {
        // Print the error message if an exception is caught
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

////////////////  MAIN CODE ////////////////////////////////