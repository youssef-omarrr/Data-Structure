///////////////////////////////////////////////////////////////////////////
/////////////////////        HEADER           /////////////////////////////
///////////////////////////////////////////////////////////////////////////
#ifndef mQueue
#define mQueue

#include <vector>
#include <iostream>
#include <stdexcept>
#include <stack>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

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

///////////////////////////////////////////////////////////////////////////
/////////////////////        QUEUE            /////////////////////////////
///////////////////////////////////////////////////////////////////////////

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
    T ans = vec.back();

    // pop it (delete it)
    vec.pop_back();

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

///////////////////////////////////////////////////////////////////////////
/////////////////////         MAIN            /////////////////////////////
///////////////////////////////////////////////////////////////////////////

// function to parse input and add it to stack in reverse order
template <typename T>
void getdata(ILinkedBased<T> &linkedQueue, const std::string &input)
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
        linkedQueue.enqueue(*it);
    }

}

int main()
{
    ILinkedBased<int> linkedQueue;
    std::string line;

    try
    {
        // read the first line for list elements
        if (std::getline(std::cin, line) && !line.empty())
            getdata(linkedQueue, line);
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
        if (operation == "enqueue")
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
                        
                    linkedQueue.enqueue(element);
                    linkedQueue.printQueue(); 
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
        else if (operation == "dequeue")
        {
            if (linkedQueue.size() == 0){
                std::cout << "Error" << std::endl;
                return 0;
            }
            linkedQueue.dequeue();
            linkedQueue.printQueue(); 
            std::cout << std::endl;
        }
        else if (operation == "isEmpty")
        {
            std::cout << (linkedQueue.isEmpty() ? "True" : "False") << std::endl;
        }
        else if (operation == "size")
        {
            std::cout << linkedQueue.size() << std::endl;
        }
        else
        {
            std::cout << "Error" << std::endl;
            return 1;
        }
    }
    catch (const std::runtime_error &e)
    {
        // Print the error message if an exception is caught
        std::cout << "Error" << std::endl;
        return 1;
    }

    return 0;
}