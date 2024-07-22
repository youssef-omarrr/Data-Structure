#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct qnode{
    int data;
    struct qnode* pnext;
} qnode;

qnode *pfirstq, *plastq;

qnode* create_qnode(int data){ 
    qnode* pqnode = (qnode*) malloc(sizeof(qnode));
    if (pqnode != NULL){
            pqnode -> data = data;
            pqnode -> pnext = NULL;
        }
    return pqnode;
}

void qpush (int data){
    qnode* pqnode = create_qnode(data);

    if (pfirstq == plastq && pfirstq == NULL){
        pfirstq = plastq = pqnode;
    }
    else{
        plastq -> pnext = pqnode;
        plastq = pqnode;
    }
}

void qpop(){
    if (pfirstq != NULL){
        printf("Poped data: %d\n", pfirstq -> data);
        qnode* temp = pfirstq;
        pfirstq = pfirstq -> pnext;
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
    qnode* pqnode = pfirstq;
    printf("-----------------\n");
    while (pqnode != NULL){
        printf("%d\n", pqnode->data);
        pqnode = pqnode -> pnext;
    }
    free(pqnode);
    pqnode = NULL;
    printf("-----------------\n");
}