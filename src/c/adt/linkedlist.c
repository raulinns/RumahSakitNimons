#include "../header/adt/linkedlist.h"

LinkedList* linked_create(){
    LinkedList* newLinked = malloc(sizeof(LinkedList));
    if (!newLinked) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newLinked->size = 0;
    newLinked->head = NULL;
    newLinked->tail = NULL;

    return newLinked;
}

void linked_insertEnd(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    list->tail->next = newNode;
    list->tail = newNode;
    list->size++;

}

void linked_print(LinkedList list) {
    Node* cur = list.head;
    while (cur != NULL) {
        printf("%d,", cur->data);
        cur = cur->next;
    }
}

void linked_free(LinkedList* list) {
    Node* cur = list->head;
    Node* temp;
    while (cur != NULL) {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(list);
}

int linked_isEmpty(LinkedList head){
    return head.size == 0;
}