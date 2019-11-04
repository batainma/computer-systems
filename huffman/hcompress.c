//
//  hcompress.c
//  
//
//  Created by Jordan Coffland on 4/8/19.
//


#include "hcompress.h"
#include "linkedList.h"

int main(int argc, char *argv[]) {

    // Check the make sure the input parameters are correct
    if(argc != 3) {
        printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n");
        fflush(stdout);
        exit(1);
        // Create the frequency table by reading the generic file
    }
        struct tnode* leafNodes;
        
        leafNodes = createFreqTable(argv[2]);
        
        // Create the huffman tree from the frequency table
        struct tnode* treeRoot = createHuffmanTree(leafNodes);
        // encode
    
    
        if (strcmp(argv[1], "-e") == 0) {
            // Pass the leafNodes since it will process bottom up
            encodeFile(argv[2], leafNodes);
            
        } else { // decode
            //    // Pass the tree root since it will process top down
            //    decodeFile(argv[2], treeRoot);
        }
    free(leafNodes);
    free(treeRoot);
    printf("\n\nCheck file 'text.huff' for compressed huffman code\n\n");
    
        return 0;
}
    struct tnode* createFreqTable(char *fileName){
        FILE *file;
        file = fopen(fileName, "r");
        char character;
        //list_print(n);
        struct tnode *testNode;
        
        testNode = (struct tnode*)malloc(128*sizeof(struct tnode));
        int c;
        for(c=0;c<128; c++){
            testNode[c].weight= 0;
            testNode[c].c = c;
            testNode[c].parent = NULL;
            testNode[c].left = NULL;
            testNode[c].right = NULL;
        }
        while((character = fgetc(file)) != EOF){
            testNode[(int)character].weight++;
        }
        
        return testNode;
        
    }
    struct tnode* createHuffmanTree(struct tnode *leafNodes){
        
        LLIST *n = NULL;
        
        LLIST *prev = n;
        int c;
        for(c=0;c<128; c++){
            if(leafNodes[c].weight!=0)
                list_add_in_order(&n, &leafNodes[c]);
        }
        printf("\n\nShows the nodes have successfully make it into a LLIST\n");
        list_print(n);
        printf("\n\nShows the nodes being combined into TNODES and added back into the min heap list\n");
        while(n!=NULL&&n->next != NULL){
            
            struct tnode *parent = (struct tnode*)malloc(sizeof(struct tnode));
            
            n->t->parent = parent;
            n->next->t->parent = parent;
            parent->weight = n->t->weight + n->next->t->weight;
            parent->c = -1;
            parent->left = n->t;
            parent->right = n->next->t;
            prev = n;
            n = n->next;
            free(prev);
            prev = n;
            n = n->next;
            free(prev);
            list_add_in_order(&n,parent);
            list_print(n);
        }
        
        return n->t;
        //while n->next != NULL
        //add n + n->next
        //n = n->next->next
        //free node
        //nullify c
        //new tnode children
        
        
        return NULL;
    }
    void encodeFile(char* fileName, struct tnode *leafNodes){
        struct tnode *current;
        struct tnode *previous;
        FILE *file;
        FILE *filew;
        file = fopen(fileName, "r");
        filew = fopen("text.huff", "w");
        char character;
        int counter;
        int buffCount;
        buffCount = 0;
        counter = 0;
        unsigned short code;                            //holds huffman code so it can be flipped
        unsigned short buff;                            //holds 8 bytes of huff code to be kicked to the file
        buff = 0;
        code = 0;
        printf("\n\nPrints Huffman tree addresses for each letter:\n");
        while((character = fgetc(file)) != EOF){        //while there are still words in the file
            printf("\n%c: ",character);
            previous = &leafNodes[(int)character];
            counter = 0;
            while(previous->parent !=NULL){
                 current = previous->parent;
                if(counter !=0){
                    code = code<<1;
                }

                if(previous == current->left){
                    
                }
                if(current->right !=NULL && previous == current->right){
                    
                    code += 1;
                }
                counter++;
                previous = current;
                
            }

            unsigned int mask;
            mask = 1;
            //printf("%d",counter);
            
            for(int c = 0; c < counter; c++){
                printf("%d",1&code);
                buff += 1&code;
                buffCount++;
                if(buffCount == 8){
                    //printf("%d",buff);
                    putc(buff,filew);
                    buff = 0;
                    buffCount =0;
                }
                buff = buff <<1;
                code = code >>1;
            }
        }
        while(buffCount !=0){
            buff = buff <<1;
            buffCount++;
            if(buffCount == 8){
               // printf("%d",buff);
                putc(buff,filew);
                buff = 0;
                buffCount =0;
            }
        }
        printf("\n");
    }
    
