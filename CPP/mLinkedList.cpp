#include "mLinkedList.h"
#include <iostream>

/////----- DATA ENTERY ------/////
// add data to the front of the list
template <typename T>
void DoubleLinkedList<T>::add_front(T element)
{
    // create new node (new keyword is for dynamic memory allocation (heap))
    Node<T> *newNode = new Node<T>(element);

    // check if the node was created successfully
    if (newNode != nullptr)
    {
        // empty list
        if (head == nullptr)
            head = tail = newNode;

        else
        {
            // old head points prev to new head (new node)
            head->prev = newNode;
            // new head points next to old head
            newNode->next = head;
            // head is now the new node
            head = newNode;
        }
        // inc list size
        list_size++;
    }
}

// add data to the back of the list
template <typename T>
void DoubleLinkedList<T>::add_back(T element)
{
    // create new node (new keyword is for dynamic memory allocation (heap))
    Node<T> *newNode = new Node<T>(element);

    // check if the node was created successfully
    if (newNode != nullptr)
    {
        // empty list
        if (head == nullptr)
            head = tail = newNode;

        else
        {
            // old tail points next to new tail
            tail->next = newNode;
            // new tail points prev to old tail
            newNode->prev = tail;
            // tail is now the new node
            tail = newNode;
        }
        // inc list size
        list_size++;
    }
}

/* we will deal with wrong inputs by:
    ~if it is LESS than the list size we add it to the FRONT
    ~if it is MORE then the list size we add it to the BACK
*/

template <typename T>
void DoubleLinkedList<T>::add_index(int index, T element)
{
    // first
    if (index <= 0)
    {
        add_front(element);
        return;
    }
    // last
    else if (index > list_size || index >= list_size - 1)
    {
        add_back(element);
        return;
    }

    Node<T> *newNode = new Node<T>(element);
    if (newNode != nullptr)
    {
        // mid
        // create temp node
        Node<T> *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        // now temp is in the place we want to add the new node at
        newNode->prev = temp->prev;
        newNode->next = temp;
        temp->prev->next = newNode;
        temp->prev = newNode;

        // inc list size
        list_size++;
    }
}

/////----- GETTERS and SETTERS ------/////
template <typename T>
T DoubleLinkedList<T>::get(int index)
{
    // return if list is empty
    if (head == nullptr)
        return T();

    if (index <= 0)
        return head->data;

    if (index > list_size || index == list_size - 1)
        return tail->data;

    // create temp node
    Node<T> *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;

    return temp->data;
}

template <typename T>
void DoubleLinkedList<T>::set(int index, T element)
{
    // return if list is empty
    if (head == nullptr)
        return;

    if (index <= 0)
        head->data = element;

    else if (index > list_size || index == list_size - 1)
        tail->data = element;

    else
    {
        // create temp node
        Node<T> *temp = head;
        for (int i = 0; i < index; i++)
            temp = temp->next;

        temp->data = element;
    }
}

/////----- EXTRA FUNCTIONS ------/////
template <typename T>
bool DoubleLinkedList<T>::isEmpty()
{
    // if it equalls zero (true) it means it is empty
    return list_size == 0;
}

template <typename T>
int DoubleLinkedList<T>::size()
{
    return list_size;
}

template <typename T>
bool DoubleLinkedList<T>::contains(T element)
{
    // create temp
    Node<T> *temp = head;

    while (temp != nullptr)
    {
        if (temp->data == element)
            return true;
        temp = temp->next;
    }

    // else
    return false;
}

template <typename T>
DoubleLinkedList<T> DoubleLinkedList<T>::sublist(int from_index, int to_index)
{
    // create a new list to store sublist
    DoubleLinkedList<T> ans;

    // check if indices are within range and valid
    if (from_index < 0 || to_index >= list_size)
    {
        // return an empty list if the range is invalid
        return ans;
    }

    // create temp
    Node<T> *temp = head;

    // list not empty
    if (temp != nullptr)
    {
        for (int i = 0; i < from_index; i++)
            temp = temp->next;

        // now we are at from index
        // if from_index less than to_index then we will add data in order
        if (from_index <= to_index)
        {
            for (int i = from_index; i <= to_index; i++)
            {

                ans.add_back(temp->data);
                // go forward
                temp = temp->next;
            }
        }
        // else we will add data in reverse order
        else if (from_index > to_index)
        {
            for (int i = to_index; i <= from_index; i++)
            {
                ans.add_back(temp->data);
                // go back
                temp = temp->prev;
            }
        }
    }

    return ans;
}

template <typename T>
void DoubleLinkedList<T>::display()
{
    for (int i = 0; i < list_size; i++)
        std::cout << get(i) << " ";
    std::cout << std::endl;
}

/////----- DATA REMOVAL ------/////
template <typename T>
void DoubleLinkedList<T>::remove_front()
{
    if (!head)
        // the list is empty nothing to remove
        return;

    // save new head pointer
    Node<T> *newHead = head->next;
    // delete current head
    delete head;

    if (newHead != nullptr)
        // make new head points prev to null
        newHead->prev = nullptr;
    else
        // list only had ONE element so tail should also be NULL
        tail = nullptr;

    // init new head
    head = newHead;
    // dec list size
    list_size--;
}
template <typename T>
void DoubleLinkedList<T>::remove_back()
{
    if (!tail)
        // the list is empty nothing to remove
        return;

    // save new tail pointer
    Node<T> *newTail = tail->prev;
    // delete current tail
    delete tail;

    if (newTail != nullptr)
        // make new tail points next to null
        newTail->next = nullptr;
    else
        // list only had ONE element so head should also be NULL
        head = nullptr;

    // init new tail
    tail = newTail;
    // dec list size
    list_size--;
}
template <typename T>
void DoubleLinkedList<T>::remove(int index)
{
    // return if list is empty
    if (head == nullptr)
        return;

    // first
    if (index <= 0)
    {
        remove_front();
        return;
    }
    // last
    else if (index > list_size || index == list_size - 1)
    {
        remove_back();
        return;
    }

    // mid
    // create current node
    Node<T> *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    // now current is in the place of the node we want to remove
    if (current->prev != nullptr)
        current->prev->next = current->next;

    if (current->next != nullptr)
        current->next->prev = current->prev;

    // delete node
    delete current;

    // dec list size
    list_size--;
}

template <typename T>
void DoubleLinkedList<T>::clear()
{
    // start with head
    Node<T> *current = head;

    while (current != nullptr)
    {
        // save the pointer of the next node
        Node<T> *nextNode = current->next;
        // delete the current node
        delete current;
        // make the new current node the "next node" we saved earlier
        current = nextNode;
    }

    // reset head, tail and list size
    head = nullptr;
    tail = nullptr;
    list_size = 0;
}