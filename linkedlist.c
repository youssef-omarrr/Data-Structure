#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct node{
    int data;
    struct node* nextnode;
    struct node* prevnode;
}node;

typedef struct del{ //linked list for deleted data 🎅🏿
    int data;
    struct del* nextnode;
    struct del* prevnode;
}del;

node *pfirst, *plast; //declared in global so it is intialized with NULL
del  *pdelfirst, *pdellast;

node* create_node(int data){
    node* pnode = (node*)malloc(sizeof(node)); //free memory for the node
    if (pnode != NULL) //node created succesfully(i dnot know how to spell successfullyy)
    {   
        pnode -> data = data;
        pnode -> nextnode = NULL;
        pnode -> prevnode = NULL;
        return pnode;
    }
    return NULL; //no need for else bec. the function terminates after the first return
}

del* create_node_del (int data){ //creates a node for deleted data
    del* pnode = (del*)malloc(sizeof(del)); //free memory for the node
    if (pnode != NULL) //node created succesfully(i dnot know how to spell successfullyy)
    {   
        pnode -> data = data;
        pnode -> nextnode = NULL;
        pnode -> prevnode = NULL;
        return pnode;
    }
    return NULL; //no need for else bec. the function terminates after the first return
}

void add_front(int data){
    node* pnode = create_node(data);
    if (pfirst == NULL)
        pfirst = plast = pnode;
    else{
        pfirst -> nextnode = pnode; //old pfirst
        pnode -> prevnode = pfirst;
        pfirst = pnode; //our new node (pfirst)
    }
}

void add_back_del(int data_del){ //adds deleted data
    del* pnode = create_node_del(data_del);
    if (pdelfirst == NULL)
        pdelfirst = pdellast = pnode;
    else{
        pdellast -> prevnode = pnode; //old plast
        pnode -> nextnode = pdellast;
        pdellast = pnode; //our new plast
    }
}

void remove_front (){
    int deleted_data = pfirst -> data;
    add_back_del(deleted_data);
    pfirst = pfirst -> prevnode;
    free (pfirst -> nextnode); //free the memory
    pfirst -> nextnode = NULL;
}

void add_back(int data){
    node* pnode = create_node(data);
    if (pfirst == NULL)
        pfirst = plast = pnode;
    else{
        plast -> prevnode = pnode; //old plast
        pnode -> nextnode = plast;
        plast = pnode; //our new plast
    }
}

void remove_back (){
    int deleted_data = plast -> data;
    add_back_del(deleted_data);
    plast = plast -> nextnode;
    free (plast -> prevnode); //free the mem
    plast -> prevnode =NULL;
}

void add_many (int n, ...){ //first arrgument is the number of inputs we will add
    va_list ptr;
    va_start (ptr,n);
    for (int i =0; i < n; i++)
        add_back(va_arg (ptr, int));

    va_end(ptr);
}

int insert_node (int data, int index){
    if (pfirst == NULL || index == 0){
        add_front(data);
        return 1;
    }

    node* pnode = create_node(data);
    node* pref = pfirst -> prevnode; //refrence pointer

    if (pnode != NULL){
    for (int i=1; i<index; i++){
        if (pref != NULL) 
            pref = pref -> prevnode; //go back
        else{
           add_back(data);  // if the user enters a number more than the list we just add it to the back
           return -1;
        }
    } 

    pref -> nextnode -> prevnode = pnode; //common sense 🎅🏿
    pnode -> nextnode = pref -> nextnode;
    pref -> nextnode = pnode;
    pnode -> prevnode = pref;
    return 0;
    }
    
}

int delete_node (int index){
    if (pfirst == NULL){ //if the list is empty
        printf("The list is EMPTY");
        return 1;
    }
    if (index == 0){
        remove_front(); //first
        return 0;
    }

    node* pref = pfirst -> prevnode;
    for (int i=1; i<index; i++){ //reference node we want to delete
        if (pref != NULL)
            pref = pref -> prevnode;
        else{
            remove_back(); //last
            return -1;
        }
    }
    if ((pref -> prevnode) == NULL){
        remove_back(); //last
        return -1;  
    }
    else{
        add_back_del(pref -> data); //add deleted data to the back of the list,
        pref -> prevnode -> nextnode = pref -> nextnode;
        pref -> nextnode -> prevnode = pref -> prevnode;
        free (pref); //free the mem
        pref = NULL;
        return 2;
    }
    
}

int swap (int index1, int index2){
    
    if (index1 >= index2){
        printf("Wrong input. Make sure index 1 is less than index 2");
        return -1;
    }

    if (index1 < 0 || index2 < 0){
        printf("Wrong input!");
        return -1;
    }
    
    node* pref1 = pfirst;
    node* pref2 = pfirst -> prevnode;

    if (pref1 == NULL){
        printf("This list has no items");
        return -1;
    }
    if (pref2 == NULL){
        printf("This list has one item only.");
        return -1;
    }

    for (int i=0; i<index1; i++){ //starting from zero because pfirst is the starting index
        if (pref1 != NULL)
            pref1 = pref1 -> prevnode;
        else{
            printf("Index is out of range!");
            return 1;
        }
    }
    for (int i=1; i<index2; i++){ //starting from 1 becacuse index 1 
        if (pref2 != NULL)        //(pfirst -> prevnode) is the starting index
            pref2 = pref2 -> prevnode;
        else{
            printf("Index is out of range!");
            return 1;
        }
    }

    // all possible possibilites 
    if (pref1 == pfirst && pref2 -> prevnode == NULL){ //1) first and last nodes

        if (index2 - index1 == 1){ //1.a) if they are next to each other
            pref2 -> nextnode = NULL; //middle part (no nodes)
            pref1 -> prevnode = NULL;

            pref2 -> prevnode = pref1; //main characters
            pref1 -> nextnode = pref2;   
            }
        else{ //1.b) if they are "NOT" next to each other
            pref2 -> nextnode -> prevnode = pref1; //middle nodes
            pref1 -> prevnode -> nextnode = pref2;
            
            pref1 -> nextnode = pref2 -> nextnode;
            pref2 -> nextnode = NULL;

            pref2 -> prevnode = pref1 -> prevnode;
            pref1 -> prevnode = NULL;
            }

        pfirst = pref2;
        plast = pref1;
        return 0;
    }

    else if (pref1 == pfirst){ //2) pref1 is the first node and any other node

        if (index2 - index1 == 1){ //2.a) if they are next to each other
            pref2 -> prevnode -> nextnode = pref1; //outter nodes 

            pref1 -> prevnode = pref2 -> prevnode; //middle part (no nodes)
            pref2 -> nextnode = NULL;

            pref1 -> nextnode = pref2 ; //main characters
            pref2 -> prevnode = pref1; 
            }
        else{ //2.b) if they are "NOT" next to each other
            pref2 -> nextnode -> prevnode = pref1; //middle nodes
            pref1 -> prevnode -> nextnode = pref2;

            pref2 -> prevnode -> nextnode = pref1; //outter nodes
             
            pref1 -> nextnode = pref2 -> nextnode; //main characters
            pref2 -> nextnode = NULL;

            node* temp = create_node(0);
            temp -> prevnode = pref1 -> prevnode;
            pref1 -> prevnode = pref2 -> prevnode;
            pref2 -> prevnode = temp -> prevnode;
            free (temp);
            }

        pfirst = pref2;
        return 0;
    }

    else if (pref2 -> prevnode == NULL){//3) pref2 is the last node and any other node

        if (index2 - index1 == 1){ //3.a) if they are next to each other
            pref1 -> nextnode -> prevnode = pref2; //outter nodes 

            pref2 -> nextnode = pref1 -> nextnode; //middle part (no nodes)
            pref1 -> prevnode = NULL;

            pref2 -> prevnode = pref1 ; //main characters
            pref1 -> nextnode = pref2; 
            }
        else{ //3.b) if they are "NOT" next to each other
            pref1 -> prevnode -> nextnode = pref2; //middle nodes
            pref2 -> nextnode -> prevnode = pref1;

            pref1 -> nextnode -> prevnode = pref2; //outter nodes
                
            pref2 -> prevnode = pref1 -> prevnode; //main characters
            pref1 -> prevnode = NULL;

            node* temp = create_node(0);
            temp -> nextnode = pref2 -> nextnode;
            pref2 -> nextnode = pref1 -> nextnode;
            pref1 -> nextnode = temp -> nextnode;
            free (temp);
            }  

        plast = pref1;   
        return 0;
    }

    else{ //4) any 2 random nodes
        if (index2 - index1 == 1){ //4.a) if they are next to each other
            pref2 -> prevnode -> nextnode = pref1; //outter nodes
            pref1 -> nextnode -> prevnode = pref2; 

            pref2 -> nextnode = pref1 -> nextnode; //middle part (no nodes)
            pref1 -> prevnode = pref2 -> prevnode;

            pref2 -> prevnode = pref1; //main characters
            pref1 -> nextnode = pref2;
            }
        else{ //4.b) if they are "NOT" next to each other
            pref2 -> nextnode -> prevnode = pref1; //middle nodes
            pref1 -> prevnode -> nextnode = pref2;

            pref2 -> prevnode -> nextnode = pref1; //outter nodes
            pref1 -> nextnode -> prevnode = pref2;
            
            node* temp = create_node(0); //main characters
            temp -> nextnode = pref1 -> nextnode;
            pref1 -> nextnode = pref2 -> nextnode;
            pref2 -> nextnode = temp -> nextnode;

            temp -> prevnode = pref1 -> prevnode;
            pref1 -> prevnode = pref2 -> prevnode;
            pref2 -> prevnode = temp -> prevnode;
            free (temp);
            }
    }
}

void reverse (){
    int index1 = 0, index2 = 1;
    node* pref = pfirst;
    int counter = 0;

    for (counter; pref-> prevnode != NULL; counter++){
        pref = pref -> prevnode;
    }
    counter;
    for (int i=0 , j=counter ; i< counter; i++,j--){
            if (i >= j)
                continue;
            else 
                swap (i,j);
        }  
}

int recover (int num){ //recovers the latest data in the recycle bin and adds it to the end of the list
    if (pdelfirst == NULL){
        printf("The list is empty");
        return -1;
    }     
    else{
        int counter =0;
        del* pdelnode = pdelfirst;
        for(int i=0; pdelnode != NULL; counter++ )
            pdelnode = pdelnode -> prevnode;
        if (num > counter){
            printf("The recycle bin doesn't have that many items!");
            return -1;
        }
        else{
            for (int i=0; i<num; i++){
                add_back(pdellast -> data);
                pdellast = pdellast -> nextnode;
                free(pdellast -> prevnode);
                pdellast -> prevnode = NULL; 
            }
            return 0;
        } 
    }     
}

void empty(){ //a function that empties the recycle bin
    while (pdellast != NULL){
        if (pdellast -> nextnode != NULL){
            pdellast = pdellast -> nextnode;
            free (pdellast -> prevnode);
            pdellast -> prevnode = NULL;   
        }
        else{
            pdelfirst = pdellast = NULL;
        }
    }
    printf("!!Recycle bin has been cleared!!\n");
}

void print_list (){ //print_list function to print the list 🎅🏿
    node* test = pfirst;
    printf("****************************\n");
    for (int i =0; test != NULL; i++){
        printf("index number %d is %d\n",i, test->data);
        test = test -> prevnode;
    }
    free (test);
    printf("****************************\n");
    if (pdelfirst != NULL)
    {   
        printf("Recycle bin:\n");
        del* test = pdelfirst;
        for (int i =0; test != NULL; i++){
        printf("%d\n",test->data);
        test = test -> prevnode;
        }
        free (test);
        printf("****************************\n");
    }   
    else {
        printf ("Recycle bin is empty.\n");
        printf("****************************\n");
    }    
}

void print_index (int index){ //prints a certain index not the full list
    node* pnode = pfirst;
    for (int i =0; i<index; i++){
        if (pnode != NULL)
            pnode = pnode->prevnode;
        else
            printf("Wrong input");
    }
    printf ("The data in index %d is %d\n", index, pnode->data);
}

