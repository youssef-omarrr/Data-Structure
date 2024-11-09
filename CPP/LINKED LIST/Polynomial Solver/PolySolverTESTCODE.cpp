#include "PolySolver.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;
// function to parse input into a Poly object
void getdata(Poly &poly, const std::string &input)
{
    std::string data = input;

    // Remove brackets '[' and ']' from the string
    data.erase(std::remove(data.begin(), data.end(), '['), data.end());
    data.erase(std::remove(data.begin(), data.end(), ']'), data.end());

    std::stringstream ss(data);
    std::string item;

    // Split by commas and add each element to the polynomial
    int index = 0; // To handle the coefficient's index
    while (std::getline(ss, item, ','))
    {
        // Remove whitespace around item
        item.erase(0, item.find_first_not_of(" \t"));
        item.erase(item.find_last_not_of(" \t") + 1);

        // Convert item to integer and add to the polynomial
        int value = std::stoi(item);
        poly.add_index(index++, value); // Add coefficients in order
    }

    // // For testing
    // std::cout << "Parsed Polynomial: ";
    // PolySolver solver;
    // solver.print(poly);
    // std::cout << std::endl;
}

int main()
{
    // Create polynomials
    Poly poly1;
    std::string input = "[3, -4, 5, 0, 2]"; // Represents 3x^4 - 4x^3 + 5x^2 + 0x + 2
    getdata(poly1, input);

    Poly poly2;
    std::string input2 = "[7, 0, -3, 2]"; // Represents 7x^3 + 0x^2 - 3x + 2
    getdata(poly2, input2);

    // Create two more example polynomials
    Poly poly3;
    std::string input3 = "[1, -1, 0, 0, 4]"; // Represents x^4 - x^3 + 4
    getdata(poly3, input3);

    Poly poly4;
    std::string input4 = "[5, 0, 2]"; // Represents 5x^2 + 2
    getdata(poly4, input4);


    // Initialize PolySolver
    PolySolver solver;

    // Add polynomials to solver
    solver.set('A', poly1);
    solver.set('B', poly2);
    solver.set('C', poly3);
    solver.set('D', poly4);

    // Retrieve and print polynomials
    cout << "Polynomial A: ";
    solver.print(solver.get_data('A'));
    cout << endl;

    cout << "Polynomial B: ";
    solver.print(solver.get_data('B'));
    cout << endl;

    cout << "Polynomial C: ";
    solver.print(solver.get_data('C'));
    cout << endl;

    cout << "Polynomial D: ";
    solver.print(solver.get_data('D'));
    cout << endl;

    cout << "===================================================" << endl;

    // Perform and print addition
    Poly resultAdd = solver.add(poly1, poly2); // Add A and B
    cout << "A + B: ";
    solver.print(resultAdd); 
    cout << "~ Represents (3x^4 - 4x^3 + 5x^2 + 2) + (7x^3 - 3x + 2)" << endl;
    cout << "~ Result: 3x^4 + 3x^3 + 5x^2 - 3x + 4" << endl;

    cout << "===================================================" << endl;

    // Perform and print subtraction
    Poly resultSub = solver.sub(poly1, poly2); // Subtract B from A
    cout << "A - B: ";
    solver.print(resultSub);
    cout << " ~ Represents (3x^4 - 4x^3 + 5x^2 + 2) - (7x^3 - 3x + 2)" << endl;
    cout << " ~ Result: 3x^4 - 11x^3 + 5x^2 + 3x" << endl;

    cout << "===================================================" << endl;

    // Perform and print multiplication
    Poly resultMul = solver.mult(poly1, poly2); // Multiply A and B
    cout << "A * B: ";
    solver.print(resultMul);
    cout << " ~ Represents (3x^4 - 4x^3 + 5x^2 + 2) * (7x^3 - 3x + 2)" << endl;
    cout << " ~ Result: 21x^7 - 28x^6 + 26x^5 + 18x^4 - 9x^3 + 10x^2 - 6x + 4" << endl;


    return 0;
}