#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file/user.h"
#include "adt/set.h"

extern Set setUser;

/* i adalah indeks awal data yang ingin di parse 
   token adalah char yang berfungsi sebagai MARK (untuk '\0' dan '\n' tidak perlu dibuat sebagai token)
   line adalah string char di mana data berada
   Mengembalikan data yang sudah di parse */
char *ParseData(char *line, int *i, char token);

/* Mengembalikan ID User yang terdapat pada user.csv
   Mengembalikan -1 jika user dengan nama "name" tidak ditemukan */
int IdxUser(char *name);

/* Prakondisi: idx adalah ID yang terdapat pada user.csv
 * Mengembalikan Username yang terdapat pada user.csv*/
char *NamaUser(int idx);

/* Menambahkan data user baru pada user list */
void AddUser(char *name, char *pass,UserList *uList);

/* Menambahkan dokter baru ke user list */
int AddDokter(UserList* uList);

#endif