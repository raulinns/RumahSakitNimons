#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* Membuat node baru */
Node* createNode(int data);

#endif