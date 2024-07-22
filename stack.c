#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct node_stk{
    int data;
    struct node_stk* pnext;
} node_stk;

node_stk* ptop;

node_stk* create_node_stk(int data){ 
    node_stk* pnode_stk = (node_stk*) malloc(sizeof(node_stk));
    if (pnode_stk != NULL){
            pnode_stk -> data = data;
            pnode_stk -> pnext = NULL;
        }
    return pnode_stk;
}

void push(int data){
    node_stk* pnode_stk = create_node_stk(data);
    if (pnode_stk != NULL){ //check ifnode_stk is created
        pnode_stk -> pnext = ptop; //make the new node_stk points to the data under it pointed by old ptop
        ptop = pnode_stk; //makes the data on top the new ptop
    }
}

void pop(){
    node_stk* pnode_stk = ptop;
    if (pnode_stk != NULL){
        printf("Poped data: %d\n", pnode_stk -> data);
        ptop = pnode_stk -> pnext;
        free(pnode_stk);
        pnode_stk = NULL;
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
    node_stk* pnode_stk = ptop;
    printf("-----------------\n");
    while (pnode_stk != NULL){
        printf("%d\n", pnode_stk->data);
        pnode_stk = pnode_stk -> pnext;
    }
    free(pnode_stk);
    pnode_stk = NULL;
    printf("-----------------\n");
}