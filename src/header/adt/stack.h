#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

typedef struct Stack{
    struct Node* top;
    int size;
} Stack;

/* Membuat node baru yang berisikan data dari parameter */
void stack_create(Stack* s);

/* Menambahkan node baru di stack */
void stack_push(Stack* s, int data);

/* Mengembalikan pointer ke posisi teratas pada stack
   Mengembalikan NULL jika stack kosong
*/
int stack_top(Stack* s);

/* Menghapus elemen teratas pada stack */
void stack_pop(Stack* s);

/* Menghapus stack seluruhnya */
void stack_clear(Stack* s);

/* Mengembalikan 1 jika stack kosong
   Mengembalikan 0 jika stack memiliki setidaknya satu elemen*/
int stack_isEmpty(Stack s);

#endif