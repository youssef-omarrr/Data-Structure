#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct node{
    int data;
    struct node* pright;
    struct node* pleft;
} node;

node* pfirst;

node* create_node(int data){
    node* pnode = (node*) malloc(sizeof(node));
    if (pnode != NULL){
        pnode -> data = data;
        pnode -> pright = NULL;
        pnode -> pleft = NULL;
    }
    return pnode;
}