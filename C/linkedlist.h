#ifndef link_h
#define link_h

void add_front(int data);
void remove_front ();
void add_back(int data);
void remove_back ();
void add_many (int n, ...); //first arrgument is the number of inputs we will add
int insert_node (int data, int index);
int delete_node (int index);
int swap (int index1, int index2);
void reverse ();
int recover (int num); //recovers the latest data in the recycle bin and adds it to the end of the list
void empty(); //a function that empties the recycle bin
void print_list ();
void print_index (int index); //prints a certain index not the full list

#endif
