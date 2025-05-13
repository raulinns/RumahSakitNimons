#ifndef LIST_H
#define LIST_H

#define CAPACITY 100

#define NEFF(l)     (l).nEff
#define ELMT(l, i)  (l).contents[i]

typedef struct {
    int nEff;
    char contents[100][CAPACITY];
} List;

/* I.S. l belum terdefinisi
   F.S. l sudah terdefinisi */
void list_create(List *l);

/*  Menambahkan user baru dengan nama 'name'
    I.S. l tidak penuh
    F.S. l berisikan user baru dengan nama 'name'
*/
void list_add(List *l,char *name);

#endif