#include "../../header/adt/linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

void linked_create(LinkedList* newLinked) {
    newLinked->size = 0;
    newLinked->head = NULL;
    newLinked->tail = NULL;
}

void linked_insertEnd(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

void linked_print(LinkedList list) {
    Node* cur = list.head;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) printf(", ");
        cur = cur->next;
    }
    printf("\n");
}

void linked_free(LinkedList* list) {
    Node* cur = list->head;
    while (cur != NULL) {
        Node* temp = cur;
        cur = cur->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int linked_isEmpty(LinkedList list) {
    return list.size == 0;
}

void linked_delete(LinkedList* list, int idx) {
    if (idx < 0 || idx >= list->size) return;

    Node* temp = list->head;

    // Delete head
    if (idx == 0) {
        list->head = temp->next;
        if (list->tail == temp) list->tail = NULL; // if only one element
        free(temp);
        list->size--;
        return;
    }

    // Delete node at index > 0
    Node* prev = NULL;
    for (int i = 0; i < idx; i++) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;
    if (temp == list->tail) list->tail = prev;
    free(temp);
    list->size--;
}
