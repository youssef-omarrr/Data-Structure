#include "mStack.h"
#include <iostream>
#include <string>

int main()
{
    try
    {
        // Create a stack of integers
        Stack<int> intStack;

        std::cout << "Testing isEmpty() on a new stack: " 
                  << (intStack.isEmpty() ? "Empty" : "Not Empty") << std::endl;

        // Test push()
        std::cout << "\nPushing elements onto the stack: 10, 20, 30" << std::endl;
        intStack.push(10);
        intStack.push(20);
        intStack.push(30);
        intStack.testSTACK('a');
        std::cout << std::endl;
        intStack.testSTACK('b');

        // Test size()
        std::cout << "\nSize of the stack: " << intStack.size() << std::endl;

        // Test peek()
        std::cout << "\nPeeking at the top element: " << intStack.peek() << std::endl;

        // Test pop()
        std::cout << "\nPopping elements from the stack..." << std::endl;
        std::cout << "Popped: " << intStack.pop() << std::endl;
        intStack.testSTACK('a');
        std::cout << std::endl;

        std::cout << "Popped: " << intStack.pop() << std::endl;
        intStack.testSTACK('a');
        std::cout << std::endl;

        std::cout << "Popped: " << intStack.pop() << std::endl;
        intStack.testSTACK('a');
        std::cout << std::endl;

        // Test isEmpty() after popping all elements
        std::cout << "\nTesting isEmpty() after popping all elements: " 
                  << (intStack.isEmpty() ? "Empty" : "Not Empty") << std::endl;

        // Test popping from an empty stack
        std::cout << "\nAttempting to pop from an empty stack:" << std::endl;
        try
        {
            intStack.pop();
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }

        // Test clearing the stack
        std::cout << "\nTesting clear() function:" << std::endl;
        intStack.push(100);
        intStack.push(200);
        intStack.push(300);
        intStack.testSTACK('a');
        std::cout << std::endl;
        intStack.clear();
        std::cout << "After clearing:" << std::endl;
        intStack.testSTACK('a');
        std::cout << std::endl;

        // Test with another data type (e.g., strings)
        std::cout << "\nTesting stack with strings:" << std::endl;
        Stack<std::string> stringStack;
        stringStack.push("Hello");
        stringStack.push("World");
        stringStack.push("Stack");
        stringStack.testSTACK('a');
        std::cout << std::endl;
        std::cout << "Popped: " << stringStack.pop() << std::endl;
        stringStack.testSTACK('a');
        std::cout << std::endl;

    }
    catch (const std::exception &e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
