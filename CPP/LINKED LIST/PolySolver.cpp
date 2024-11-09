#include "PolySolver.h"
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

    std::cout << "P(" << x << ") = " << result << std::endl;

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
