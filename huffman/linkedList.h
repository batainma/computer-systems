//
//  linkedList.h
//  
//
//  Created by Jordan Coffland on 4/8/19.
//

#ifndef linkedList_h
#define linkedList_h
#include <stdio.h> /* for printf */
#include <stdlib.h> /* for malloc */
// Structures and typedefs

typedef struct node {
    struct tnode *t;
    struct node *next; /* pointer to next element in list */
} LLIST;

// Prototypes
LLIST *list_add(LLIST **p, struct tnode*);
LLIST *list_add2(LLIST **p,struct tnode*);
//void list_remove(LLIST **p);
//LLIST **list_search(LLIST **n);
void list_print(LLIST *n);
LLIST *list_add_in_order(LLIST **n,struct tnode*);

#endif /* linkedList_h */
