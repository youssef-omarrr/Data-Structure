#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct node{
    int data;
    struct node* pnext;
} node;

node* ptop;

node* create_node(int data){ 
    node* pnode = (node*) malloc(sizeof(node));
    if (pnode != NULL){
            pnode -> data = data;
            pnode -> pnext = NULL;
        }
    return pnode;
}

void push(int data){
    node* pnode = create_node(data);
    if (pnode != NULL){ //check ifnode is created
        pnode -> pnext = ptop; //make the new node points to the data under it pointed by old ptop
        ptop = pnode; //makes the data on top the new ptop
    }
}

void pop(){
    node* pnode = ptop;
    if (pnode != NULL){
        printf("Poped data: %d\n", pnode -> data);
        ptop = pnode -> pnext;
        free(pnode);
        pnode = NULL;
    }
    else{
        printf("stack is empty!");
    }
}

void many_pushes (int n, ...){
    va_list ptr;
    va_start (ptr, n);

    for (int i=0; i<n; i++){
        push (va_arg(ptr, int));
    }
    va_end(ptr);
}

void many_pops (int n){
    for (int i=0; i<n; i++){
        pop ();
    }
}

void print_stack(){
    node* pnode = ptop;
    printf("-----------------\n");
    while (pnode != NULL){
        printf("%d\n", pnode->data);
        pnode = pnode -> pnext;
    }
    free(pnode);
    pnode = NULL;
    printf("-----------------\n");
}