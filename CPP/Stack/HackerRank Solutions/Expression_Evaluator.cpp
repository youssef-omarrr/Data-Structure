#include <iostream>
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <cmath>

////////////////  HEADER ////////////////////////////////
#ifndef mSTACK
#define mSTACK

template <typename T>
class Node
{
public:
    T data;
    Node *down;
    Node(T data)
    {
        this->data = data;
        this->down = nullptr;
    }
};

template <typename T>
class Stack
{
public:
    Stack();
    ~Stack();

    T pop();
    T peek();
    void push(T element);

    bool isEmpty();
    int size();
    void clear();

    void testSTACK(char mode);

private:
    Node<T> *top;
    int stack_size;
};

template <typename T>
Stack<T>::Stack()
{
    top = nullptr;
    stack_size = 0;
}

template <typename T>
Stack<T>::~Stack()
{
    clear();
}

template <typename T>
T Stack<T>::pop()
{
    if (stack_size == 0)
    {
        throw std::runtime_error("Error");
    }
    Node<T> *current = top;
    T data = current->data;
    top = top->down;
    stack_size--;
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
        Node<T> *newNode = new Node<T>(element);
        if (top != nullptr)
        {
            newNode->down = top;
        }
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
        Node<T> *nextNode = current->down;
        delete current;
        current = nextNode;
    }
    top = nullptr;
    stack_size = 0;
}

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

#endif
////////////////  HEADER ////////////////////////////////

class PostfixConverter {
private:
    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
    }

    int precedence(char ch) {
        if (ch == '+' || ch == '-') return 1;
        else if (ch == '*' || ch == '/') return 2;
        else if (ch == '^') return 3;
        return -1;
    }

public:
    std::string preprocessExpression(const std::string& infix) {
        std::string processed = infix;

        // Simplify consecutive signs
        for (size_t i = 0; i < processed.length();) {
            if (processed[i] == '-' && processed[i + 1] == '-') {
                // Case 1: At the very beginning of the expression
                if (i == 0) {
                    processed.replace(i, 2, "");
                    continue;
                }
                
                // Case 2: Preceded by an operator
                if (i > 0 && isOperator(processed[i-1])) {
                    processed.replace(i, 2, "");
                    continue;
                }
                
                // Otherwise, replace with '+'
                processed.replace(i, 2, "+");
                continue;
            }
            else if (processed[i] == '+' && processed[i + 1] == '-') {
                processed.replace(i, 2, "-"); // '+-' becomes '-'
                continue;
            }
            else if (processed[i] == '+' && processed[i + 1] == '+') {
                processed.replace(i, 2, "+"); // '++' becomes '+'
                continue;
            }
            else if (processed[i] == '(' && processed[i + 1] == ')') {
                throw std::runtime_error("Error");
            }
            else if (processed[i] == '*' && processed[i + 1] == '*') {
                throw std::runtime_error("Error");
            }
            else if (processed[i] == '^' && processed[i + 1] == '^') {
                throw std::runtime_error("Error");
            }
            else if (processed[i] == '/' && processed[i + 1] == '/') {
                throw std::runtime_error("Error");
            }

            i++;
        }

        return processed;
    }

    std::string infixToPostfix(const std::string& infix) {
        // Initial error checks
        if (infix[0] == '/' || infix[0] == '*' || infix[0] == '^' || infix[0] == ')') {
            throw std::runtime_error("Error");
        }
        if (infix[infix.length() - 1] == '+' || infix[infix.length() - 1] == '-' || 
            infix[infix.length() - 1] == '/' || infix[infix.length() - 1] == '*' || 
            infix[infix.length() - 1] == '^' || infix[infix.length() - 1] == '(') {
            throw std::runtime_error("Error");
        }

        std::string postfix;
        Stack<char> stack;
        int parenthesesCount = 0;

        for (size_t i = 0; i < infix.length(); i++) {
            if (infix[i] == 'a' || infix[i] == 'b' || infix[i] == 'c') {
                postfix += infix[i];
            }
            else if (infix[i] == '(') {
                stack.push(infix[i]);
                parenthesesCount++;
            }
            else if (infix[i] == ')') {
                parenthesesCount--;

                // Check for negative parentheses count
                if (parenthesesCount < 0) {
                    throw std::runtime_error("Error");
                }

                while (!stack.isEmpty() && stack.peek() != '(') {
                    postfix += stack.peek();
                    stack.pop();
                }
                
                if (!stack.isEmpty() && stack.peek() == '(') {
                    stack.pop();
                }
                else {
                    throw std::runtime_error("Error");
                }
            }
            else if (isOperator(infix[i])) {
                while (!stack.isEmpty() && stack.peek() != '(' &&
                       precedence(infix[i]) <= precedence(stack.peek())) {
                    postfix += stack.peek();
                    stack.pop();
                }
                stack.push(infix[i]);
            }
        }

        // Check for unbalanced parentheses at the end
        if (parenthesesCount != 0) {
            throw std::runtime_error("Error");
        }

        while (!stack.isEmpty()) {
            if (stack.peek() == '(' || stack.peek() == ')') {
                throw std::runtime_error("Error");
            }
            postfix += stack.peek();
            stack.pop();
        }

        return postfix;
    }
};

class PostfixEvaluator {
private:
    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
    }

public:
    int evaluatePostfix(const std::string& postfix, int a, int b, int c) {
        Stack<int> stack;
        for (size_t i = 0; i < postfix.length(); i++) {
            if (postfix[i] == 'a') {
                stack.push(a);
            }
            else if (postfix[i] == 'b') {
                stack.push(b);
            }
            else if (postfix[i] == 'c') {
                stack.push(c);
            }
            else if (isOperator(postfix[i])) {
                if (postfix[i] == '^') {
                    if (stack.size() < 2) {
                        throw std::runtime_error("Error");
                    }
                    else {
                        int right = stack.pop();
                        int left = stack.pop();
                        stack.push(pow(left, right));
                    }
                }
                else if (postfix[i] == '/') {
                    if (stack.size() < 2) {
                        throw std::runtime_error("Error");
                    }
                    else {
                        int right = stack.pop();
                        if (right == 0) {
                            throw std::runtime_error("Error");
                        }
                        int left = stack.pop();
                        stack.push(left / right);
                    }
                }
                else if (postfix[i] == '*') {
                    if (stack.size() < 2) {
                        throw std::runtime_error("Error");
                    }
                    else {
                        int right = stack.pop();
                        int left = stack.pop();
                        stack.push(left * right);
                    }
                }
                else if (postfix[i] == '-') {
                    if (stack.size() < 2) {
                        stack.push(0 - stack.pop());
                    }
                    else {
                        int right = stack.pop();
                        int left = stack.pop();
                        stack.push(left - right);
                    }
                }
                else if (postfix[i] == '+') {
                    if (stack.size() < 2) {
                        stack.push(0 + stack.pop());
                    }
                    else {
                        int right = stack.pop();
                        int left = stack.pop();
                        stack.push(left + right);
                    }
                }
            }
        }
        return stack.peek();
    }
};

int getInput(const std::string& input) {
    size_t pos = input.find('=');

    if (pos != std::string::npos) {
        // Extract the substring after '='
        std::string num = input.substr(pos + 1);

        // Convert to integer and return
        return std::stoi(num);
    }

    // Return a default value or handle error if '=' is not found
    throw std::invalid_argument("Error");
}

int main() {
    try {
        std::string infix;
        std::string InA;
        std::string InB;
        std::string InC;

        // Input infix expression
        std::getline(std::cin, infix);

        std::getline(std::cin, InA);
        std::getline(std::cin, InB);
        std::getline(std::cin, InC);

        int a = getInput(InA);
        int b = getInput(InB);
        int c = getInput(InC);

        PostfixConverter converter;
        PostfixEvaluator evaluator;

        std::string processed = converter.preprocessExpression(infix);
        std::string postfix = converter.infixToPostfix(processed);
        std::cout << postfix << std::endl;

        // Evaluate the postfix expression
        int result = evaluator.evaluatePostfix(postfix, a, b, c);
        std::cout << result << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << e.what();
    }

    return 0;
}