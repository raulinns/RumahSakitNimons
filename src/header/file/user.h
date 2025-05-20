#ifndef USER_H
#define USER_H

#include "field.h"
#include "../adt/linkedlist.h"

<<<<<<< HEAD
#define id(x)           (x).fields[0]
#define username(x)     (x).fields[1]
#define password(x)     (x).fields[2]
#define role(x)         (x).fields[3]
#define riwayat(x)      (x).fields[4]
#define suhu(x)         (x).fields[5]
#define sistol(x)       (x).fields[6]
#define diastol(x)      (x).fields[7]
#define detak(x)        (x).fields[8]
#define saturasi(x)     (x).fields[9]
#define gula(x)         (x).fields[10]
#define berat(x)        (x).fields[11]
#define tinggi(x)       (x).fields[12]
#define kolesterol(x)   (x).fields[13]
#define LDL(x)          (x).fields[14]
#define trombosit(x)    (x).fields[15]
=======
#define id(x)           (x).field[0]
#define username(x)     (x).field[1]
#define password(x)     (x).field[2]
#define role(x)         (x).field[3]
#define riwayat(x)      (x).field[4]
#define suhu(x)         (x).field[5]
#define sistol(x)       (x).field[6]
#define diastol(x)      (x).field[7]
#define detak(x)        (x).field[8]
#define saturasi(x)     (x).field[9]
#define gula(x)         (x).field[10]
#define berat(x)        (x).field[11]
#define tinggi(x)       (x).field[12]
#define kolesterol(x)   (x).field[13]
#define LDL(x)          (x).field[14]
#define trombosit(x)    (x).field[15]
>>>>>>> fitur-load-save
#define USER(l,x)       (l).contents[x]

typedef struct User{
    fields field[16];
    LinkedList inventoryObat;
} User;

typedef struct UserList{
    User contents[MAX_USER];
    int len;
} UserList;

/* Mengembalikan ID User yang terdapat pada user.csv
   Mengembalikan -1 jika user dengan nama "name" tidak ditemukan */
int IdxUser(char *name);

/* Menambahkan data user baru pada user.csv */
void AddUser(char *name, char *pass, UserList *uList);

#endif