//
//  linkedList.c
//  
//
//  Created by Jordan Coffland on 4/8/19.
//
/* Slighted modified LinkedList C implementation from Wikipedia */

// Functions
// Add to the head of the given linkedlist
#include "linkedList.h"
#include "hcompress.h"


LLIST *list_add(LLIST **p, struct tnode *data) {
    if (p == NULL)
        return NULL;
    
    LLIST *n = malloc(sizeof(LLIST));
    if (n == NULL)
        return NULL;
    
    n->next = *p;                            //the previous element (*p) now becomes the "next" element
    *p = n;                                  // add new empty element to the front (head) of the list
    n->t = data;
    return *p;
}



LLIST *list_add2(LLIST **a,struct tnode *data){
    if (a == NULL)                                      //case when a is null
        return NULL;
    
    LLIST *n = malloc(sizeof(LLIST)); //new node
    LLIST *p = *a;                    //temp
    if (n == NULL)                                      //case when pointer doesnt initiallize
        return NULL;
    n->t = data;                                        //sets the tnode as the other tnode
    if(p->next==NULL){                                  //case where there is only one node in the list
        p->next = n;
        n->next = NULL;
    }
    else if(p->next->next == NULL && data->weight>p->next->t->weight){
      //case when the node needs to be the new last
        p->next->next = n;
        n->next =NULL;
        //a=&p;
        //return *a;
    }
    else{
        n->next = p->next;                            //normal case, inserts between p and p->next
        p->next = n;
        a = &p;
    }
    return *a;
}




void list_print(LLIST *n) {                                 //simple print, shows the weight and ascii value of each node
    while (n != NULL) {
        printf("List: %c, %f ", (char)n->t->c,n->t->weight);
        n = n->next;
    }
    printf("\n");
}
/**
 * Compares and walks through the list to find the appropriate insert spot
 **/
LLIST *list_add_in_order(LLIST **head, struct tnode *data){
    LLIST *w;
    LLIST **z = head;
    w = *head;
    //list_print(w);
    if(w==NULL){                                                //LLIST IS EMPTY
         return list_add(head,data);
    }
    if(data->weight<=w->t->weight||w == NULL){                  //INSERT FIRST
        return list_add(head,data);
    }
    if(w->next == NULL){
        return(list_add2(&w,data));
    }
    while(data->weight>w->next->t->weight&&w->next->next!=NULL){//WALKS TO FIND SPOT
        w = w->next;
    }
        list_add2(&w,data);
    return *head;
}

// Remove the head of the given linkedlist
void list_remove(LLIST **p) {
    if (p != NULL && *p != NULL) {
        LLIST *n = *p;
        *p = (*p)->next;
        free(n);
       }
}
// Find the node in the list and return it
LLIST **list_search(LLIST **n, int i) {
    if (n == NULL)
        return NULL;

    while (*n != NULL) {
        if ((*n)->t->c == i) {
            return n;
        }
        n = &((*n)->next);
    }
    return NULL;
    }

// Display the list
// Testing code
//int main(void) {
//    LLIST *n = NULL;
//    //list_print(n);
//    struct tnode *testNode;
//    testNode = (struct tnode*)malloc(128*sizeof(struct tnode));
//    int c;
//    for(c=0;c<128; c++){
//        testNode[c].weight= rand()%128;
//        testNode[c].c = c;
//        list_add_in_order(&n, &testNode[c]);
//
//    }
//    list_print(n);
//
//    return 0;
//}

int main(int argc, char *argv[]) {
// Testing code
struct tnode a;
a.c = 'a';
a.weight=0;
struct tnode b;
b.c = 'b';
b.weight=1;
struct tnode c;
c.c = 'c';
c.weight=2;
struct tnode d;
d.c = 'd';
d.weight=3;
LLIST *n = NULL;
printf("Add\n");    
list_print(n);
list_add(&n, &a); /* list: a,0 */
list_print(n);
list_add(&n, &b); /* list: b,1 : a,0 */
list_print(n);
list_add(&n, &c); /* list: c,2 : b,1 : a,0 */
list_print(n);
list_add(&n, &d); /* list: d,3 : c,2 : b,1 : a,0 */
list_print(n);
printf("\nRemove\n");    
list_remove(&n); /* remove first (3) leaving c,2 : b,1 : a,0 */
list_print(n);
list_remove(&(n->next)); /* remove new second (1) leaving c,2 : a,0 */
list_print(n);
list_remove(list_search(&n, 'a')); /* remove cell containing ‘a’ (first) leaving ‘c’ */  
list_print(n);
list_remove(&n); /* remove last (2) leaving empty */
list_print(n);
printf("\nAdd in Order\n");    
list_add_in_order(&n, &a); /* list: a,0 */
list_print(n);
list_add_in_order(&n, &b); /* list: a,0 : b,1 */
list_print(n);
list_add_in_order(&n, &c); /* list: a,0 : b,1 : c,2 */
list_print(n);
list_add_in_order(&n, &d); /* list: a,0 : b,1 : c,2 : d,3 */
list_print(n);
return 0;
}
