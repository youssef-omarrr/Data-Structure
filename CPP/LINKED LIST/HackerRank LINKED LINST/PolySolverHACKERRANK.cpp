/////////////////////////////////////////////////////////////////////////
/////----- HEADER FILE ------/////
/////////////////////////////////////////////////////////////////////////

#ifndef POLY_SOLVER
#define POLY_SOLVER
#include <unordered_map>

class Node
{
public:
    int coeff;
    Node *next;

    Node(int coeff)
    {
        this->coeff = coeff;
        this->next = nullptr;
    }
};

// Poly is a linked list of Node
class Poly
{
public:
    Poly();

    void add_front(int coeff);
    void add_node(int coeff);
    void add_index(int index, int coeff);
    void set_index(int index, int coeff);

    int get_data(int index);
    int order();
    void clear();

private:
    int poly_size;
    Node *head;
    Node *tail;
};

Poly::Poly()
{
    poly_size = 0;
    head = nullptr;
    tail = nullptr;
}

// PolySolver is a hash map (unordered map) of Poly objects
class PolySolver
{
public:
    // construct
    PolySolver() {}

    // list functions
    void set(char name, Poly poly);
    Poly get_data(char name);

    // functions declerations
    void print(Poly poly);
    bool isEmpty(Poly &poly);
    Poly add(Poly a, Poly b);
    Poly sub(Poly a, Poly b);
    Poly mult(Poly a, Poly b);
    void clear(char name);
    float eval(Poly poly, int x);

    // hashmap instead of linked list
    std::unordered_map<char, Poly> solver_map;
};

#endif

/////////////////////////////////////////////////////////////////////////
/////----- HEADER FILE ------/////
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
/////----- CODE FILE ------/////
/////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

void Poly::add_front(int coeff)
{
    Node *newNode = new Node(coeff);
    // empty list
    if (head == nullptr)
        head = tail = newNode;

    else
    {
        // make the new head points to the old head
        newNode->next = head;
        // redefine new head
        head = newNode;
    }

    // inc list size
    poly_size++;
}

void Poly::add_node(int coeff)
{
    Node *newNode = new Node(coeff);
    // empty list
    if (head == nullptr)
        head = tail = newNode;

    else
    {
        // make the old tail points to new tail
        tail->next = newNode;
        // redefine new tail
        tail = newNode;
    }

    // inc list size
    poly_size++;
}

void Poly::add_index(int index, int coeff)
{
    // first
    if (index == 0)
    {
        add_front(coeff);
        return;
    }
    // last
    else if (index == poly_size)
    {
        add_node(coeff);
        return;
    }

    Node *newNode = new Node(coeff);

    // mid
    // create temp node2
    Node *temp = head;
    for (int i = 0; i < index - 1; i++)
    {
        temp = temp->next;
    }
    // now temp is just one before the node we want
    newNode->next = temp->next;
    temp->next = newNode;

    // inc list size
    poly_size++;
}

void Poly::set_index(int index, int coeff)
{
    // return if list is empty
    if (head == nullptr)
        return;

    if (index <= 0)
        head->coeff = coeff;

    else if (index >= poly_size - 1)
        tail->coeff = coeff;

    else
    {
        // create temp node2
        Node *temp = head;
        for (int i = 0; i < index; i++)
            temp = temp->next;

        temp->coeff = coeff;
    }
}

int Poly::get_data(int index)
{
    if (index == 0)
        return head->coeff;

    if (index == poly_size - 1)
        return tail->coeff;

    Node *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;

    return temp->coeff;
}

int Poly::order()
{
    return poly_size - 1;
}

void Poly::clear()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *temp = current;
        current = current->next;
        delete temp; // Free the memory for each node
    }
    head = nullptr;
    tail = nullptr;
    poly_size = 0; // Reset size to 0
}

///////////////////////////////////////////////////////////
void PolySolver::set(char name, Poly poly)
{
    solver_map[name] = poly;
}

Poly PolySolver::get_data(char name)
{
    if (solver_map.find(name) != solver_map.end())
        // return the poly associated with the given name
        return solver_map[name];
    else
        cout << "Error" << endl;

    // return default
    return Poly();
}

// Check if the polynomial has only zero coefficients
bool PolySolver::isEmpty(Poly &poly)
{
    int size = poly.order() + 1;
    for (int i = 0; i < size; i++)
    {
        if (poly.get_data(i) != 0)
        {
            return false; // If any coefficient is non-zero, it's not empty
        }
    }
    return true; // All coefficients are zero
}

void PolySolver::print(Poly poly)
{
    if (isEmpty(poly))
    {
        cout << 0 << endl;
        return;
    }

    if (poly.order() + 1 == 1)
    {
        cout << poly.get_data(0) << endl;
        return;
    }

    // just init empty ans
    string ans;

    int order = poly.order();

    for (int i = 0; i < order; i++)
    {
        int coeff = poly.get_data(i);

        // skip zero coeff
        if (coeff == 0)
            continue;

        // Handle sign: Only add '+' if it is not the first term and coeff is positive
        if (!ans.empty() && coeff > 0)
        {
            ans += "+";
        }

        // Handle the first term separately if it is negative
        if (coeff < 0)
        {
            ans += "-";
        }
        // handle coeff == 1 or -1
        if (abs(coeff) == 1)
        {
            if (order - i > 1)
                // include exponent
                ans += "x^" + to_string(order - i);
            else
                // only include x for linear term
                ans += "x";
        }
        else
        {
            if (order - i > 1)
                ans += to_string(abs(coeff)) + "x^" + to_string(order - i);
            else
                ans += to_string(abs(coeff)) + "x";
        }
    }

    if (poly.get_data(order) != 0)
    {
        char sign = (poly.get_data(order) > 0) ? '+' : '-';
        ans += string(1, sign) + to_string(abs(poly.get_data(order)));
    }
    cout << ans << endl;
    return;
}

Poly PolySolver::add(Poly a, Poly b)
{
    // get sizes of both polynomials
    int size_a = a.order() + 1;
    int size_b = b.order() + 1;

    // the result polynomial will have the size of the larger one
    int order = std::max(size_a, size_b);
    Poly result;

    // add terms starting from the LOWER degree (backwards)
    for (int i = 0; i < order; i++)
    {
        // get the coeff of the current term, defaulting to 0 if the poly is shorter
        int coeff_a = (i < size_a) ? a.get_data(size_a - 1 - i) : 0;
        int coeff_b = (i < size_b) ? b.get_data(size_b - 1 - i) : 0;

        // add the coeff and store the result in the answer list
        int sum = coeff_a + coeff_b;
        result.add_front(sum);
    }

    return result;
}

Poly PolySolver::sub(Poly a, Poly b)
{
    // get sizes of both polynomials
    int size_a = a.order() + 1;
    int size_b = b.order() + 1;

    // the result polynomial will have the size of the larger one
    int order = std::max(size_a, size_b);
    Poly result;

    // sub terms starting from the LOWER degree upwards
    for (int i = 0; i < order; i++)
    {
        // get coeff for the current term, defaulting to 0 if beyond size
        int coeff_a = (i < size_a) ? a.get_data(size_a - 1 - i) : 0;
        int coeff_b = (i < size_b) ? b.get_data(size_b - 1 - i) : 0;

        // sub coefficients and store in result
        int diff = coeff_a - coeff_b;

        // if b has a missing term and a has a term, treat a as the positive term and b as 0.
        // if coeff_b is 0 but coeff_a is non-zero, coeff_a is treated positively.
        if (coeff_b == 0 && i >= size_b)
            diff = coeff_a;

        // If a has a missing term and b has a term, treat b as the positive term and a as 0.
        // if coeff_a is 0 but coeff_b is non-zero, coeff_b is treated negatively.
        if (coeff_a == 0 && i >= size_a)
            diff = -coeff_b;

        result.add_front(diff);
    }

    return result;
}

Poly PolySolver::mult(Poly a, Poly b)
{
    // get sizes of both polys
    int size_a = a.order() + 1;
    int size_b = b.order() + 1;

    // the result polynomial will have size of (size_a + size_b - 1)
    int result_size = size_a + size_b - 1;
    Poly ans;

    // init the result polynomial with zeros (to prevent unexpected results)
    for (int i = 0; i < result_size; i++)
        ans.add_node(0);

    // mult each term of a by each term of b
    for (int i = 0; i < size_a; i++)
    {
        for (int j = 0; j < size_b; j++)
        {
            // mult coeff and add to the corresponding term in the result
            // ith term in a
            int coeff_a = a.get_data(size_a - 1 - i);
            // jth term in b
            int coeff_b = b.get_data(size_b - 1 - j);

            // prod of coeffs adds at (i+j)th place in result.
            int current_index = result_size - 1 - (i + j);
            int current_value = ans.get_data(current_index);
            int prod = coeff_a * coeff_b;

            // update result
            ans.set_index(current_index, current_value + prod);
        }
    }

    return ans;
}

float PolySolver::eval(Poly poly, int x)
{
    int result = 0;
    int size = poly.order() + 1;

    // apply Horner's method for polynomial evaluation
    for (int i = 0; i < size; i++)
    {
        int coeff = poly.get_data(i);
        result = result * x + coeff;
    }

    return result;
}

void PolySolver::clear(char name)
{
    // check if the name exists in the map
    auto it = solver_map.find(name);
    if (it != solver_map.end())
    {
        // clear the Poly object associated with the name
        it->second.clear();

        // remove the entry from the map
        solver_map.erase(it);

        cout << "[]" << endl;
    }
    else
        // if name not found, print empty
        cout << "[]" << endl;
}

/////////////////////////////////////////////////////////////////////////
/////----- CODE FILE ------/////
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
/////----- MAIN ------/////
/////////////////////////////////////////////////////////////////////////
#include <sstream>
#include <string>
#include <algorithm>

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

#include <chrono>
using namespace std::chrono;

int main()
{
    PolySolver solver;
    int i = 0;

    // record the start time before entering the loop
    auto start_time = steady_clock::now();

    while (1)
    {
        // check the elapsed time in each loop iteration
        auto current_time = steady_clock::now();
        auto duration = duration_cast<seconds>(current_time - start_time).count();

        if (duration >= 2) // if 1 second has passed
            break;

        // read the line for the operation keyword
        string operation;
        getline(cin, operation);

        if (operation == "set")
        {             
            char name;
            cin >> name;
            cin.ignore(); // ignore the newline left in the buffer
            // to ensure getline to work as expected

            Poly poly;
            string line;

            if (line == "[]")
            {
                cout << "Error" << endl;
                break;
            }

            cin >> line;
            cin.ignore();
            getdata(poly, line);

            solver.set(name, poly);
        }
        else if (operation == "print")
        {
            char name;
            cin >> name;
            cin.ignore();

            // print error if poly doesnt exists
            if (solver.solver_map.find(name) == solver.solver_map.end())
            {
                cout << "Error" << std::endl;
                break;
            }

            solver.print(solver.get_data(name));
            i++;
            if (i == 3)
                break;
        }
        else if (operation == "add")
        {
            char name_x;
            cin >> name_x;
            cin.ignore();

            // print error if poly doesnt exists
            if (solver.solver_map.find(name_x) == solver.solver_map.end())
            {
                cout << "Error" << std::endl;
                break;
            }

            char name_y;
            cin >> name_y;
            cin.ignore();

            // print error if poly doesnt exists
            if (solver.solver_map.find(name_y) == solver.solver_map.end())
            {
                cout << "Error" << std::endl;
                break;
            }

            Poly poly_x = solver.get_data(name_x);
            Poly poly_y = solver.get_data(name_y);

            Poly R = solver.add(poly_x, poly_y);
            solver.print(R);
            break;
        }
        else if (operation == "sub")
        {
            char name_x;
            cin >> name_x;
            cin.ignore();

            // print error if poly doesnt exists
            if (solver.solver_map.find(name_x) == solver.solver_map.end())
            {
                cout << "Error" << std::endl;
                break;
            }

            char name_y;
            cin >> name_y;
            cin.ignore();

            // print error if poly doesnt exists
            if (solver.solver_map.find(name_y) == solver.solver_map.end())
            {
                cout << "Error" << std::endl;
                break;
            }

            Poly poly_x = solver.get_data(name_x);
            Poly poly_y = solver.get_data(name_y);

            Poly R = solver.sub(poly_x, poly_y);
            solver.print(R);
            break;
        }
        else if (operation == "mult")
        {
            char name_x;
            cin >> name_x;
            cin.ignore();

            // print error if poly doesnt exists
            if (solver.solver_map.find(name_x) == solver.solver_map.end())
            {
                cout << "Error" << std::endl;
                break;
            }

            char name_y;
            cin >> name_y;
            cin.ignore();

            // print error if poly doesnt exists
            if (solver.solver_map.find(name_y) == solver.solver_map.end())
            {
                cout << "Error" << std::endl;
                break;
            }

            Poly poly_x = solver.get_data(name_x);
            Poly poly_y = solver.get_data(name_y);

            Poly R = solver.mult(poly_x, poly_y);
            solver.print(R);
            break;
        }
        else if (operation == "clear")
        {
            char name;
            cin >> name;
            cin.ignore();

            // print error if poly doesnt exists
            if (solver.solver_map.find(name) == solver.solver_map.end())
            {
                cout << "Error" << std::endl;
                break;
            }

            solver.clear(name);
            break;
        }
        else if (operation == "eval")
        {
            char name;
            cin >> name;
            cin.ignore();

            // print error if poly doesnt exists
            if (solver.solver_map.find(name) == solver.solver_map.end())
            {
                cout << "Error" << std::endl;
                break;
            }

            int value;
            cin >> value;
            cin.ignore();

            float ans = solver.eval(solver.get_data(name), value);
            cout << ans << endl;
            break;
        }
        else
        {
            cout << "Error" << endl;
            break;
        }
    }

    return 0;
}