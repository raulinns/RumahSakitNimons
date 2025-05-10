#ifndef LIST_H
#define LIST_H

#define CAPACITY 100

#define NEFF(l)     (l).nEff
#define ELMT(l, i)  (l).contents[i]

typedef struct {
    int nEff;
    int contents[CAPACITY];
} List;

/* I.S. l belum terdefinisi
   F.S. l sudah terdefinisi */
void CreateList(List *l);

#endif