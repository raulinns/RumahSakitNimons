#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>

#define MAX_FIELDS 20
#define MAX_FIELD_LENGTH 100
#define MAX_LINE_LENGTH 256

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

struct User{
    char fields[MAX_FIELDS][MAX_FIELD_LENGTH];
};

/* Mengembalikan ID User yang terdapat pada user.csv
   Mengembalikan -1 jika user dengan nama "name" tidak ditemukan */
int IdxUser(char *name);

/* Menambahkan data user baru pada user.csv */
void AddUser(char *name, char *pass);

#endif