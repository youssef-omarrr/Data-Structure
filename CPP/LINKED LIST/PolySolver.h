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
