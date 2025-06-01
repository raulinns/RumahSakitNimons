#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

/**
 Membuat node baru dengan data tertentu
 I.S. : data sembarang
 F.S. : Node baru dialokasikan dengan data dan next = NULL
*/
Node* createNode(int data);


#endif