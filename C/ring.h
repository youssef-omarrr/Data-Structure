#ifndef ring_h
#define ring_h

void add_node_back(int data); //adds a node at the end of the ring
void add_node_front(int data); //adds a node at the begining of the ring 
void remove_node(); //removes the first node (we cant remove the last node bec we cant access the data before it)
int pop_ring(); //returns the first value added to the ring
void print_ring(); //prints the ring from the first item to the last and prints the first again to show that it is a ring
void print_loop(int n); //prints the ring but demands number of iterations

#endif 
