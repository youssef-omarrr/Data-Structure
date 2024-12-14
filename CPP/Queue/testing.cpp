#include <iostream>
#include "mQueue.cpp"

int main() {
    std::cout << "Testing ILinkedBased Queue:" << std::endl;

    // Create an instance of ILinkedBased
    ILinkedBased<int> linkedQueue;

    // Test isEmpty (should be true initially)
    std::cout << "Is Linked Queue empty? " << (linkedQueue.isEmpty() ? "Yes" : "No") << std::endl;

    // Enqueue elements
    linkedQueue.enqueue(10);
    linkedQueue.printQueue();
    std::cout << std::endl;

    linkedQueue.enqueue(20);
    linkedQueue.printQueue();
    std::cout << std::endl;

    linkedQueue.enqueue(30);
    linkedQueue.printQueue();
    std::cout << std::endl;

    // Print queue
    std::cout << "Linked Queue after enqueue: ";
    linkedQueue.printQueue();
    std::cout << std::endl;

    // Test size
    std::cout << "Linked Queue size: " << linkedQueue.size() << std::endl;

    // Dequeue an element
    int dequeuedValue = linkedQueue.dequeue();
    std::cout << "Dequeued from Linked Queue: " << dequeuedValue << std::endl;

    // Print queue again
    std::cout << "Linked Queue after dequeue: ";
    linkedQueue.printQueue();
    std::cout << std::endl;

    // Test isEmpty (should be false)
    std::cout << "Is Linked Queue empty? " << (linkedQueue.isEmpty() ? "Yes" : "No") << std::endl;

    // Test dequeue from an empty queue (should throw exception)
    try {
        linkedQueue.dequeue();
        linkedQueue.dequeue(); // This should throw an exception
    } catch (const std::runtime_error &e) {
        std::cout << "Exception caught in Linked Queue: " << e.what() << std::endl;
    }

    std::cout << "\nTesting IArrayBased Queue:" << std::endl;

    // Create an instance of IArrayBased
    IArrayBased<int> arrayQueue;

    // Test isEmpty (should be true initially)
    std::cout << "Is Array Queue empty? " << (arrayQueue.isEmpty() ? "Yes" : "No") << std::endl;

    // Enqueue elements
    arrayQueue.enqueue(40);
    arrayQueue.printQueue();
    std::cout << std::endl;

    arrayQueue.enqueue(50);
    arrayQueue.printQueue();
    std::cout << std::endl;

    arrayQueue.enqueue(60);
    arrayQueue.printQueue();
    std::cout << std::endl;

    // Print queue
    std::cout << "Array Queue after enqueue: ";
    arrayQueue.printQueue();
    std::cout << std::endl;

    // Test size
    std::cout << "Array Queue size: " << arrayQueue.size() << std::endl;

    // Dequeue an element
    int dequeuedValue2 = arrayQueue.dequeue();
    std::cout << "Dequeued from Array Queue: " << dequeuedValue2 << std::endl;

    // Print queue again
    std::cout << "Array Queue after dequeue: ";
    arrayQueue.printQueue();
    std::cout << std::endl;

    // Test isEmpty (should be false)
    std::cout << "Is Array Queue empty? " << (arrayQueue.isEmpty() ? "Yes" : "No") << std::endl;

    // Test dequeue from an empty queue (should throw exception)
    try {
        arrayQueue.dequeue();
        arrayQueue.dequeue(); // This should throw an exception
    } catch (const std::runtime_error &e) {
        std::cout << "Exception caught in Array Queue: " << e.what() << std::endl;
    }

    return 0;
}
