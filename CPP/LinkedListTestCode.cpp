#include <iostream>
#include "mLinkedList.h" // Include your header file for the DoubleLinkedList class
//gcc testsss.cpp mLinkedList.cpp -lstdc++ -o output_program


int main()
{
    // Create an instance of DoubleLinkedList for integers
    DoubleLinkedList<int> list;

    // Test adding elements
    std::cout << "Adding elements to the list..." << std::endl;
    list.add_back(10);
    list.add_back(20);
    list.add_back(40);
    list.add_back(50);
    list.add_back(15);
    list.add_front(5);
    list.add_index(1, 15); 

    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;

    // Print elements of the list
    std::cout << "Elements in the list: ";
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "===============================" << std::endl;

    // Test get and set
    std::cout << "First element: " << list.get(0) << std::endl;              // 5
    std::cout << "Last element: " << list.get(list.size() - 1) << std::endl; // 20
    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    // Test case 1: Get a valid sublist in order
    DoubleLinkedList<int> sublist1 = list.sublist(2, 4);
    std::cout << "Sublist from index 2 to 4 (in order): ";
    sublist1.display(); // Expected output: 10 20 40

    // Test case 2: Get a sublist with a single element
    DoubleLinkedList<int> sublist2 = list.sublist(3, 3);
    std::cout << "Sublist from index 3 to 3 (single element): ";
    sublist2.display(); // Expected output: 20

    // Test case 3: Get a sublist in reverse order
    DoubleLinkedList<int> sublist3 = list.sublist(4, 2);
    std::cout << "Sublist from index 4 to 2 (in reverse): ";
    sublist3.display(); // Expected output: 40 20 10

    // Test case 4: Out of bounds indices
    DoubleLinkedList<int> sublist4 = list.sublist(-1, 10);
    std::cout << "Sublist from out-of-bounds indices (-1, 10): ";
    sublist4.display(); // Expected output: (empty list)
    std::cout << "===============================" << std::endl;

    list.set(1, 12); // Change element at index 1 to 12
    std::cout << "After setting index 1 to 12: ";
    list.display();
    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    // Test contains
    std::cout << "List contains 15? " << (list.contains(15) ? "Yes" : "No") << std::endl;
    std::cout << "List contains 99? " << (list.contains(99) ? "Yes" : "No") << std::endl;
    std::cout << "List contains 50? " << (list.contains(50) ? "Yes" : "No") << std::endl;
    std::cout << "List contains 19? " << (list.contains(19) ? "Yes" : "No") << std::endl;

    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "===============================" << std::endl;
    // Test removing elements
    std::cout << "Removing front element..." << std::endl;
    list.remove_front(); // Removes 5
    std::cout << "List after removing front: ";
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Removing back element..." << std::endl;
    list.remove_back(); // Removes 20
    std::cout << "List after removing back: ";
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Removing by index..." << std::endl;
    list.remove(2);
    std::cout << "List after removing index 2: ";
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Clearing list..." << std::endl;
    list.clear();
    std::cout << "List after clearing: ";
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;

    return 0;
}
