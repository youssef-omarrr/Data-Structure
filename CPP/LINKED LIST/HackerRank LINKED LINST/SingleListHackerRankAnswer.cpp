#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <math.h>
#include <climits>

/////////////////////////////////////////////////////////////////////////
/////----- HEADER FILE ------/////
/////////////////////////////////////////////////////////////////////////
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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
/////////////////////////////////////////////////////////////////////////
/////----- HEADER FILE ------/////
/////////////////////////////////////////////////////////////////////////

/////----- DATA ENTERY ------/////
// add data to the front of the list
template <typename T>
void SingleLinkedList<T>::add_front(T element)
{
    // create new node2 (new keyword is for dynamic memory allocation (heap))
    Node2<T> *newNode2 = new Node2<T>(element);

    // check if the node2 was created successfully
    if (newNode2 != nullptr)
    {
        // empty list
        if (head == nullptr)
            head = tail = newNode2;

        else
        {
            // make the new head points to the old head
            newNode2->next = head;
            // redefine new head
            head = newNode2;
        }
        // inc list size
        list_size++;
    }
}

// add data to the back of the list
template <typename T>
void SingleLinkedList<T>::add(T element)
{
    // create new node2 (new keyword is for dynamic memory allocation (heap))
    Node2<T> *newNode2 = new Node2<T>(element);

    // check if the node2 was created successfully
    if (newNode2 != nullptr)
    {
        // empty list
        if (head == nullptr)
            head = tail = newNode2;

        else
        {
            // make the old tail points to new tail
            tail->next = newNode2;
            // redefine new tail
            tail = newNode2;
        }
        // inc list size
        list_size++;
    }
}

template <typename T>
void SingleLinkedList<T>::addToIndex(int index, T element)
{
    // first
    if (index == 0)
    {
        add_front(element);
        display();
        return;
    }
    // last
    else if (index == list_size)
    {
        add(element);
        display();
        return;
    }

    else if (index > list_size || index < 0)
    {
        std::cout << "Error" << std::endl;
        return;
    }

    Node2<T> *newNode2 = new Node2<T>(element);
    if (newNode2 != nullptr)
    {
        // mid
        // create temp node2
        Node2<T> *temp = head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        // now temp is just one before the node we want
        newNode2->next = temp->next;
        temp->next = newNode2;

        // inc list size
        list_size++;
        display();
    }
}

/////----- GETTERS and SETTERS ------/////
template <typename T>
T SingleLinkedList<T>::get(int index)
{
    // Return an error if list is empty or index is out of bounds
    if (head == nullptr || index < 0 || index >= list_size)
        return INT_MIN;

    if (index == 0)
        return head->data;

    if (index == list_size - 1)
        return tail->data;

    // create temp node2
    Node2<T> *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;

    return temp->data;
}

template <typename T>
void SingleLinkedList<T>::set(int index, T element)
{
    // return if list is empty
    if (head == nullptr)
    {
        std::cout << "Error" << std::endl;
        return;
    }

    if (index == 0)
        head->data = element;

    else if (index == list_size - 1)
        tail->data = element;

    else if (index >= list_size || index < 0)
    {
        std::cout << "Error" << std::endl;
        return;
    }

    else
    {
        // create temp node2
        Node2<T> *temp = head;
        for (int i = 0; i < index; i++)
            temp = temp->next;

        temp->data = element;
    }
    display();
}

/////----- EXTRA FUNCTIONS ------/////
template <typename T>
bool SingleLinkedList<T>::isEmpty()
{
    // if it equalls zero (true) it means it is empty
    if (list_size == 0)
        std::cout << "True" << std::endl;
    else
        std::cout << "False" << std::endl;
    return list_size == 0;
}

template <typename T>
int SingleLinkedList<T>::size()
{
    return list_size;
}

template <typename T>
bool SingleLinkedList<T>::contains(T element)
{
    // create temp
    Node2<T> *temp = head;

    while (temp != nullptr)
    {
        if (temp->data == element)
        {
            std::cout << "True" << std::endl;
            return true;
        }
        temp = temp->next;
    }

    // else
    std::cout << "False" << std::endl;
    return false;
}

template <typename T>
SingleLinkedList<T> SingleLinkedList<T>::sublist(int from_index, int to_index)
{
    // create a new list to store sublist
    SingleLinkedList<T> ans;

    // check if indices are within range and valid
    if (from_index < 0 || to_index >= list_size || from_index > to_index)
    {
        // return an empty list if the range is invalid
        return ans;
    }

    // create temp
    Node2<T> *temp = head;

    // list not empty
    if (temp != nullptr)
    {
        for (int i = 0; i < from_index; i++)
            temp = temp->next;

        for (int i = from_index; i <= to_index; i++)
        {

            ans.add(temp->data);
            // go forward
            temp = temp->next;
        }
    }

    return ans;
}

template <typename T>
void SingleLinkedList<T>::display()
{
    if (list_size == 0)
    {
        std::cout << "[]";
        return;
    }

    std::cout << "[";
    for (int i = 0; i < list_size - 1; i++)
        std::cout << get(i) << ", ";

    std::cout << get(list_size - 1) << "]";
}

/////----- DATA REMOVAL ------/////
template <typename T>
void SingleLinkedList<T>::remove_front()
{
    if (!head)
        // the list is empty nothing to remove
        return;

    // save new head pointer
    Node2<T> *newHead = head->next;
    // delete current head
    delete head;

    if (newHead == nullptr)
        // list only had ONE element so tail should also be NULL
        tail = nullptr;

    // init new head
    head = newHead;
    // dec list size
    list_size--;
}
template <typename T>
void SingleLinkedList<T>::remove_back()
{
    if (!tail)
        // the list is empty nothing to remove
        return;

    // create a new tail
    Node2<T> *newTail = head;

    // there is more than one node
    if (newTail->next != nullptr)
    {
        // loop until the next node is the tail
        while (newTail->next != tail)
        {
            newTail = newTail->next;
        }
        // now we are sure we are at the node just before the tail
        // delete current tail
        delete tail;
        // redefine new tail
        tail = newTail;
        // to be sure make the new tail's next null
        newTail->next = nullptr;
    }

    // there is only one node
    else
    {
        // delete current tail
        delete tail;

        head = nullptr;
    }

    // dec list size
    list_size--;
}
template <typename T>
void SingleLinkedList<T>::remove(int index)
{
    // return if list is empty
    if (head == nullptr)
    {
        std::cout << "Error";
        return;
    }

    // first
    if (index == 0)
    {
        remove_front();
        display();
        return;
    }
    // last
    else if (index == list_size - 1)
    {
        remove_back();
        display();
        return;
    }
    else if (index >= list_size || index < 0)
    {
        std::cout << "Error" << std::endl;
        return;
    }

    // mid
    // create one_before_current node
    Node2<T> *one_before_current = head;
    for (int i = 0; i < index - 1; i++)
    {
        one_before_current = one_before_current->next;
    }

    // now we are at the node just before the one we want to delete
    Node2<T> *current = one_before_current->next; // current to delete

    one_before_current->next = current->next;

    // delete current
    delete current;

    // dec list size
    list_size--;
    display();
}

template <typename T>
void SingleLinkedList<T>::clear()
{
    // start with head
    Node2<T> *current = head;

    while (current != nullptr)
    {
        // save the pointer of the next node2
        Node2<T> *nextNode2 = current->next;
        // delete the current node2
        delete current;
        // make the new current node2 the "next node2" we saved earlier
        current = nextNode2;
    }

    // reset head, tail and list size
    head = nullptr;
    tail = nullptr;
    list_size = 0;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// function to parse input
template <typename T>
void getdata(SingleLinkedList<T> &list, const std::string &input)
{
    std::string data = input;

    // Remove brackets '[' and ']' from the string
    data.erase(std::remove(data.begin(), data.end(), '['), data.end());
    data.erase(std::remove(data.begin(), data.end(), ']'), data.end());

    std::stringstream ss(data);
    std::string item;

    // Split by commas and add each element to the linked list
    while (std::getline(ss, item, ','))
    {
        // Remove whitespace around item
        item.erase(0, item.find_first_not_of(" \t"));
        item.erase(item.find_last_not_of(" \t") + 1);

        // Convert item to integer and add to the linked list
        T value = static_cast<T>(std::stoi(item));
        list.add(value);
    }
    // for testing
    //  std::cout << "===================" << std::endl;
    //  list.display();
    //  std::cout << std::endl;
    //  std::cout << "===================" << std::endl;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
int main()
{
    SingleLinkedList<int> list;
    std::string line;

    // read the first line for list elements
    std::getline(std::cin, line);
    getdata(list, line);

    // read the second line for the operation keyword
    std::string operation;
    std::getline(std::cin, operation);

    // handle and perform the operation
    if (operation == "add")
    {
        int value;
        std::cin >> value;
        list.add(value);
        list.display();
    }
    else if (operation == "disp")
    {
        list.display();
    }
    else if (operation == "addToIndex")
    {
        int index, value;
        std::cin >> index >> value;
        list.addToIndex(index, value);
    }
    else if (operation == "get")
    {
        int index;
        std::cin >> index;
        auto result = list.get(index);
        if (result != INT_MIN)
            std::cout << result << std::endl;
        else
            std::cout << "Error" << std::endl;
    }
    else if (operation == "set")
    {
        int index, value;
        std::cin >> index >> value;
        list.set(index, value);
    }
    else if (operation == "clear")
    {
        list.clear();
        list.display();
    }
    else if (operation == "isEmpty")
    {
        list.isEmpty();
    }
    else if (operation == "remove")
    {
        int index;
        std::cin >> index;
        list.remove(index);
    }
    else if (operation == "sublist")
    {
        int from_index, to_index;
        std::cin >> from_index >> to_index;
        SingleLinkedList<int> sublist = list.sublist(from_index, to_index);
        if (sublist.size() != 0)
            sublist.display();
        else
            std::cout << "Error" << std::endl;
    }
    else if (operation == "contains")
    {
        int value;
        std::cin >> value;
        list.contains(value);
    }
    else if (operation == "size")
    {
        std::cout << list.size();
    }
    else
    {
        std::cout << "Error" << std::endl;
    }

    return 0;
}