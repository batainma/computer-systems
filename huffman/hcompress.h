//
//  hcompress.h
//  
//
//  Created by Jordan Coffland on 4/9/19.
//

#ifndef hcompress_h
#define hcompress_h
#include <stdio.h> /* for printf */
#include <stdlib.h> /* for malloc */
#include <string.h>
struct tnode {
    double weight;
    int c;
    struct tnode* left;
    struct tnode* right;
    struct tnode* parent;
};
struct tnode* createFreqTable(char* fileName);
struct tnode* createHuffmanTree(struct tnode*);
void encodeFile(char*, struct tnode*);
#endif /* hcompress_h */
