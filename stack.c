#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "stack.h"

typedef struct node_stk{ //original stack
    int data;
    struct node_stk* pnext;
} node_stk;

typedef struct temp1{ //for sorting
    int data;
    struct temp1* pnext;
} temp1;

typedef struct temp2{ //for sorting
    int data;
    struct temp2* pnext;
} temp2;

node_stk* ptop;
temp1* ptop1; 
temp2* ptop2;

/////////////////////original stack///////////////////////////

static node_stk* create_node_stk(int data){ 
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
        //printf("Poped data: %d\n", pnode_stk -> data);
        ptop = pnode_stk -> pnext;
        free(pnode_stk);
        pnode_stk = NULL;
    }
    else{
        printf("stack is empty!");
    }
}

/////////////////////temp1 stack///////////////////////////

static temp1* crtemp1 (int data){ //static to prevent user from using the functions outside
    temp1* pnode_stk = (temp1*) malloc(sizeof(temp1));
    if (pnode_stk != NULL){
            pnode_stk -> data = data;
            pnode_stk -> pnext = NULL;
        }
    return pnode_stk;
}

static void push_1(int data){
    temp1* pnode_stk = crtemp1 (data);
    if (pnode_stk != NULL){ //check ifnode_stk is created
        pnode_stk -> pnext = ptop1; //make the new node_stk points to the data under it pointed by old ptop
        ptop1 = pnode_stk; //makes the data on top the new ptop
    }
}

static void pop_1(){
    temp1* pnode_stk = ptop1;
    if (pnode_stk != NULL){
        ptop1 = pnode_stk -> pnext;
        free(pnode_stk);
        pnode_stk = NULL;
    }
    else{
        printf("stack is empty!");
    }
}

/////////////////////temp2 stack///////////////////////////

static temp2* crtemp2(int data){ 
    temp2* pnode_stk = (temp2*) malloc(sizeof(temp2));
    if (pnode_stk != NULL){
            pnode_stk -> data = data;
            pnode_stk -> pnext = NULL;
        }
    return pnode_stk;
}

static void push_2(int data){
    temp2* pnode_stk = crtemp2(data);
    if (pnode_stk != NULL){ 
        pnode_stk -> pnext = ptop2; 
        ptop2 = pnode_stk; 
    }
}

static void pop_2(){
    temp2* pnode_stk = ptop2;
    if (pnode_stk != NULL){
        ptop2 = pnode_stk -> pnext;
        free(pnode_stk);
        pnode_stk = NULL;
    }
}

/////////////////////original stack///////////////////////////

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

void sort_down(){
    node_stk* cnt = ptop;
    int counter = 0;
    while (cnt != NULL){ //counts the number of elemnts in the stack
        ++counter;
        cnt = cnt-> pnext;
    }
    free(cnt);
 
    for (counter; counter > 0 ; counter--){ //repeats the process as many times as there are elements
        node_stk* pnode = ptop;
        int max = ptop -> data;
        for (int cnt2 = counter; cnt2 > 0; cnt2--){ //each step is one step less than the prev one
            if (pnode -> data >= max){              //bec we are sure that the last element is the largest
                max = pnode -> data; //if the element is bigger than the max we change the max
                push_1(pnode -> data); //and we push that element to stack temp1
                pop (); // and then we pop it out of the original stack
            }
            else{
                push_2 (pnode -> data); //if it is less than the max we push it to stack temp 2
                pop(); //this means that temp1 has all the elements bigger than the unchanged max
                      // and temp2 has the small elements
            }
            if (pnode == NULL) 
                break;
            else
                pnode = pnode -> pnext;
        }

        temp1* ptemp1 = ptop1; //puts the data in the first temp stack to the original
        while (ptemp1 != NULL){
            push (ptemp1 -> data);
            ptemp1 = ptemp1 -> pnext;
            pop_1(); //know we are sure that the max number is at the bottom of he stack
            }
        free(ptemp1);

        temp2* ptemp2 = ptop2; //puts the data in the second temp stack to the original
        while (ptemp2 != NULL){
            push (ptemp2 -> data);
            ptemp2 = ptemp2 -> pnext;
            pop_2(); //the rest of the stack is added
            }
        free(ptemp2);
    }
}

void sort_up(){
    node_stk* cnt = ptop;
    int counter = 0;
    while (cnt != NULL){ //counts the number of elemnts in the stack
        ++counter;
        cnt = cnt-> pnext;
    }
    free(cnt);
 
    for (counter; counter > 0 ; counter--){ //repeats the process as many times as there are elements
        node_stk* pnode = ptop;
        int min = ptop -> data;
        for (int cnt2 = counter; cnt2 > 0; cnt2--){ //each step is one step less than the prev one
            if (pnode -> data <= min){              //bec we are sure that the last element is the largest
                min = pnode -> data; //if the element is less than the min we change the min
                push_1(pnode -> data); //and we push that element to stack temp1
                pop (); // and then we pop it out of the original stack
            }
            else{
                push_2 (pnode -> data); //if it is greater than the min we push it to stack temp 2
                pop(); //this means that temp1 has all the elements less than the unchanged min
                      // and temp2 has the big elements
            }
            if (pnode == NULL) 
                break;
            else
                pnode = pnode -> pnext;
        }

        temp1* ptemp1 = ptop1; //puts the data in the first temp stack to the original
        while (ptemp1 != NULL){
            push (ptemp1 -> data);
            ptemp1 = ptemp1 -> pnext;
            pop_1(); //know we are sure that the min number is at the bottom of he stack
            }
        free(ptemp1);

        temp2* ptemp2 = ptop2; //puts the data in the second temp stack to the original
        while (ptemp2 != NULL){
            push (ptemp2 -> data);
            ptemp2 = ptemp2 -> pnext;
            pop_2(); //the rest of the stack is added
            }
        free(ptemp2);
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