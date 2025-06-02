#include "../../header/adt/linkedlist.h"

void linked_create(LinkedList* newLinked){
    newLinked->size = 0;
    newLinked->head = NULL;
    newLinked->tail = NULL;
    return newLinked;
}

void linked_insertEnd(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        list->size = list->size + 1;
        return;
    }
    list->tail->next = newNode;
    list->tail = newNode;
    list->size = list->size + 1;
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
    list->size = list->size - 1;
}

int linked_isEmpty(LinkedList head){
    return head.size == 0;
}

void linked_delete(LinkedList* head,int idx){
    if( idx >= head->size ) return;
    // Jika idx adalah elemen pertama
    Node* temp;
    Node* prev;
    temp = head->head;
    if( idx == 0 ){
        head->head = temp->next;
        free(temp);
        head->size = head->size - 1;
        return;
    }
    // Jika idx > 0
    while(idx > 0){
        if( idx == 1 ) prev = temp;
        temp = temp->next;
        idx--;
    }
    // Jika idx indeks terakhir
    if(head->tail == temp){
        head->tail =  prev;
    }
    prev->next = temp->next;
    head->size = head->size - 1;
    free(temp);
}