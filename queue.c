#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct node{
    int data;
    struct node* pnext;
} node;

node *pfirst, *plast;

node* create_node(int data){ 
    node* pnode = (node*) malloc(sizeof(node));
    if (pnode != NULL){
            pnode -> data = data;
            pnode -> pnext = NULL;
        }
    return pnode;
}

void qpush (int data){
    node* pnode = create_node(data);

    if (pfirst == plast && pfirst == NULL){
        pfirst = plast = pnode;
    }
    else{
        plast -> pnext = pnode;
        plast = pnode;
    }
}

void qpop(){
    if (pfirst != NULL){
        printf("Poped data: %d\n", pfirst -> data);
        node* temp = pfirst;
        pfirst = pfirst -> pnext;
        free (temp);
        temp = NULL;
    }
    else{
        printf("Queue is empty!");
    }
}

void many_qpushes (int n, ...){
    va_list ptr;
    va_start (ptr, n);

    for (int i=0; i<n; i++){
        qpush (va_arg(ptr, int));
    }
    va_end(ptr);
}

void many_qpops (int n){
    for (int i=0; i<n; i++){
        qpop ();
    }
}

void print_queue(){
    node* pnode = pfirst;
    printf("-----------------\n");
    while (pnode != NULL){
        printf("%d\n", pnode->data);
        pnode = pnode -> pnext;
    }
    free(pnode);
    pnode = NULL;
    printf("-----------------\n");
}