#include "../../header/adt/node.h"

Node* createNode(int data){
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}