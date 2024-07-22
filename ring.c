#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct rnode{
    int data;
    struct rnode* pnext;
} rnode;

rnode *prfirst, *prlast;

rnode* create_rnode(int data){
    rnode* prnode = (rnode*) malloc(sizeof(rnode));
    if (prnode != NULL){
        prnode -> data = data;
        prnode -> pnext = NULL;
    }
    return prnode;
}

void add_node_back(int data){ //adds a node at the end of the ring
    rnode* prnode = create_rnode(data);

    if (prfirst == NULL){
        prlast = prfirst = prnode;
    }
    else if (prfirst -> pnext == NULL){
        prfirst -> pnext = prnode;
        prnode -> pnext = prfirst;
        prlast = prnode;
    }
    else{
        prlast -> pnext = prnode;
        prnode -> pnext = prfirst;
        prlast = prnode;
    }
}

void add_node_front(int data){ //adds a node at the begining of the node 
    rnode* prnode = create_rnode(data);

    if (prfirst == NULL){
        prlast = prfirst = prnode;
    }
    else if (prlast -> pnext == NULL){
        prlast -> pnext = prnode;
        prnode -> pnext = prlast;
        prfirst = prnode;
    }
    else{
        prlast -> pnext = prnode;
        prnode -> pnext = prfirst;
        prfirst = prnode;
    }
}

void remove_node(){ //removes the first node (we cant remove the last node bec we cant access the data before it)
    if (prfirst == NULL){
        printf("Ring is EMPTY!\n");
    }
    else if (prfirst -> pnext == prlast){
        rnode* temp = prfirst;
        free(temp);
        temp = NULL;
        prfirst = prlast;
        prfirst -> pnext = prlast -> pnext = NULL;
        printf("Item removed!\n");
    }
    else{
        rnode* temp = prfirst;
        prfirst = prfirst -> pnext;
        prlast -> pnext = prfirst;
        free(temp);
        temp = NULL;
        printf("Item removed!\n");
    }
}

int pop_ring(){ //returns the first value added to the ring
    if (prfirst == NULL){
        printf("Ring is empty!\n");
        return -9999;
    }
    else if (prfirst -> pnext == prlast){
        rnode* temp = prfirst;
        int data = temp -> data;
        free(temp);
        temp = NULL;
        prfirst = prlast;
        prfirst -> pnext = prlast -> pnext = NULL;
        return data;
    }
    else{
        rnode* temp = prfirst;
        int data = temp -> data;
        prfirst = prfirst -> pnext;
        prlast -> pnext = prfirst;
        free(temp);
        temp = NULL;
        return data;
    }

}

void print_ring(){ //prints the ring from the first item to the last and prints the first again to show that it is a ring
    rnode* temp = prfirst;
    if (temp == NULL){
        printf("Ring is empty!\n");
        return;
    }
    for (int i=0; temp != prlast; i++){
        printf("%d -> ", temp->data);
        temp = temp -> pnext;
    }
    if (temp == prlast){
        printf ("%d -> %d\n", temp -> data, prfirst -> data);
    }
}

void print_loop(int n){ //prints the ring but demands number of iterations
    rnode* temp = prfirst;

    for (int i=n; i>1; i--){
        printf("%d -> ", temp->data);
        temp = temp -> pnext;
    }
    printf ("%d \n", temp -> data);
}