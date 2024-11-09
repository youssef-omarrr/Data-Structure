#include <iostream>
#include "mLinkedList.h" 

int main()
{
    /////////////////////////////////////////////////////////////////////////
    /////----- DoubleLinkedList part ------/////
    /////////////////////////////////////////////////////////////////////////

    std::cout << "/////----- DoubleLinkedList part ------/////" << std::endl;

    // Create an instance of DoubleLinkedList for integers
    DoubleLinkedList<int> list;

    // Test adding elements
    std::cout << "Adding elements to the list..." << std::endl;
    std::cout << "Add 10 back" << std::endl;
    list.add(10);
    list.display();
    std::cout << std::endl;
    std::cout << "Add 20 back" << std::endl;
    list.add(20);
    list.display();
    std::cout << std::endl;
    std::cout << "Add 40 back" << std::endl;
    list.add(40);
    list.display();
    std::cout << std::endl;
    std::cout << "Add 50 back" << std::endl;
    list.add(50);
    list.display();
    std::cout << std::endl;
    std::cout << "Add 15 back" << std::endl;
    list.add(15);
    list.display();
    std::cout << std::endl;
    std::cout << "Add 5 front" << std::endl;
    list.add_front(5);
    list.display();
    std::cout << std::endl;
    std::cout << "Add 15 to index 1" << std::endl;
    list.addToIndex(1, 15);
    list.display();
    std::cout << std::endl;

    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;

    // Print elements of the list
    std::cout << "Elements in the list: ";
    list.display();
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
    std::cout << std::endl;

    // Test case 2: Get a sublist with a single element
    DoubleLinkedList<int> sublist2 = list.sublist(3, 3);
    std::cout << "Sublist from index 3 to 3 (single element): ";
    sublist2.display(); // Expected output: 20
    std::cout << std::endl;

    // Test case 3: Get a sublist in reverse order
    DoubleLinkedList<int> sublist3 = list.sublist(4, 2);
    std::cout << "Sublist from index 4 to 2 (in reverse): ";
    sublist3.display(); // Expected output: 40 20 10
    std::cout << std::endl;

    // Test case 4: Out of bounds indices
    DoubleLinkedList<int> sublist4 = list.sublist(-1, 10);
    std::cout << "Sublist from out-of-bounds indices (-1, 10): ";
    sublist4.display(); // Expected output: (empty list)
    std::cout << std::endl;
    std::cout << "===============================" << std::endl;

    list.set(1, 12); // Change element at index 1 to 12
    std::cout << "After setting index 1 to 12: ";
    list.display();
    std::cout << std::endl;
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
    list.display();
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Removing back element..." << std::endl;
    list.remove_back(); // Removes 20
    std::cout << "List after removing back: ";
    list.display();
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Removing by index..." << std::endl;
    list.remove(2);
    std::cout << "List after removing index 2: ";
    list.display();
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Clearing list..." << std::endl;
    list.clear();
    std::cout << "List after clearing: ";
    list.display();
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << list.size() << std::endl;

    /////////////////////////////////////////////////////////////////////////
    /////----- SingleLinkedList part ------/////
    /////////////////////////////////////////////////////////////////////////

    std::cout << "/////----- SingleLinkedList part ------/////" << std::endl;

    // Create an instance of SingleLinkedList for integers
    SingleLinkedList<int> single_list;

    // Test adding elements
    std::cout << "Adding elements to the list..." << std::endl;
    std::cout << "Add 10 back" << std::endl;
    single_list.add(10);
    single_list.display();
    std::cout << std::endl;
    std::cout << "Add 20 back" << std::endl;
    single_list.add(20);
    single_list.display();
    std::cout << std::endl;
    std::cout << "Add 40 back" << std::endl;
    single_list.add(40);
    single_list.display();
    std::cout << std::endl;
    std::cout << "Add 50 back" << std::endl;
    single_list.add(50);
    single_list.display();
    std::cout << std::endl;
    std::cout << "Add 15 back" << std::endl;
    single_list.add(15);
    single_list.display();
    std::cout << std::endl;
    std::cout << "Add 5 front" << std::endl;
    single_list.add_front(5);
    single_list.display();
    std::cout << std::endl;
    std::cout << "Add 15 to index 1" << std::endl;
    single_list.addToIndex(1, 15);
    single_list.display();
    std::cout << std::endl;

    // Print size of the list
    std::cout << "List size: " << single_list.size() << std::endl;

    // Print elements of the list
    std::cout << "Elements in the list: ";
    single_list.display();
    std::cout << std::endl;
    std::cout << "===============================" << std::endl;

    // Test get and set
    std::cout << "First element: " << single_list.get(0) << std::endl;                     // 5
    std::cout << "Last element: " << single_list.get(single_list.size() - 1) << std::endl; // 20
    // Print size of the list
    std::cout << "List size: " << single_list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    // Test case 1: Get a valid sublist in order
    SingleLinkedList<int> sublist5 = single_list.sublist(2, 4);
    std::cout << "Sublist from index 2 to 4 (in order): ";
    sublist5.display(); // Expected output: 10 20 40
    std::cout << std::endl;

    // Test case 2: Get a sublist with a single element
    SingleLinkedList<int> sublist6 = single_list.sublist(3, 3);
    std::cout << "Sublist from index 3 to 3 (single element): ";
    sublist6.display(); // Expected output: 20
    std::cout << std::endl;

    // Test case 3: Get a sublist in reverse order
    SingleLinkedList<int> sublist7 = single_list.sublist(4, 2);
    std::cout << "Sublist from index 4 to 2 (in reverse): ";
    sublist7.display(); // Expected output: 40 20 10
    std::cout << std::endl;

    // Test case 4: Out of bounds indices
    SingleLinkedList<int> sublist8 = single_list.sublist(-1, 10);
    std::cout << "Sublist from out-of-bounds indices (-1, 10): ";
    sublist8.display(); // Expected output: (empty list)
    std::cout << std::endl;
    std::cout << "===============================" << std::endl;

    single_list.set(1, 12); // Change element at index 1 to 12
    std::cout << "After setting index 1 to 12: ";
    single_list.display();
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << single_list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    // Test contains
    std::cout << "List contains 15? " << (single_list.contains(15) ? "Yes" : "No") << std::endl;
    std::cout << "List contains 99? " << (single_list.contains(99) ? "Yes" : "No") << std::endl;
    std::cout << "List contains 50? " << (single_list.contains(50) ? "Yes" : "No") << std::endl;
    std::cout << "List contains 19? " << (single_list.contains(19) ? "Yes" : "No") << std::endl;

    // Print size of the list
    std::cout << "List size: " << single_list.size() << std::endl;
    std::cout << "===============================" << std::endl;
    // Test removing elements
    std::cout << "Removing front element..." << std::endl;
    single_list.remove_front(); // Removes 5
    std::cout << "List after removing front: ";
    single_list.display();
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << single_list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Removing back element..." << std::endl;
    single_list.remove_back(); // Removes 20
    std::cout << "List after removing back: ";
    single_list.display();
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << single_list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Removing by index..." << std::endl;
    single_list.remove(2);
    std::cout << "List after removing index 2: ";
    single_list.display();
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << single_list.size() << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Clearing list..." << std::endl;
    single_list.clear();
    std::cout << "List after clearing: ";
    single_list.display();
    std::cout << std::endl;
    // Print size of the list
    std::cout << "List size: " << single_list.size() << std::endl;

    return 0;
}
