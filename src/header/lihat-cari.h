#ifndef LIHAT_CARI_H
#define LIHAT_CARI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file/user.h"

/* Mengubah seluruh char dalam string menjadi lower-case*/
char* ToLower (char *str);

/* Mengubah seluruh char dalam string menjadi upper-case*/
char* ToUpper (char *str);

/* Melakukan sorting list untuk penampilan user */
UserList sortList (UserList uList, int urutan, int sort);

/* Prosedur awal untuk LihatUser, LihatDokter, dan LihatPasien */
void PilihanLihat (UserList uList, char* prompt);

/* Menampilkan menu pilihan untuk melihat data user, dokter, atau pasien */
void MenuLihat (int *urutan, int *sort, char *sortLihat, char *urutanLihat, int pilihan);

/* Menampilkan seluruh data user yang terdapat pada user.csv */
void LihatUser (UserList uList, int pilihan);

/* Menampilkan seluruh data pasien yang terdapat pada user.csv */
void LihatPasien (UserList uList);

/* Menampilkan seluruh data dokter yang terdapat pada user.csv */
void LihatDokter (UserList uList);

/* Melakukan binary search pada user.csv untuk mencari user berdasarkan ID */
void BinarySearchUser(UserList uList, int id, int first, int last, UserList *hasilCari);

/* Prosedur awal untuk CariUser, CariPasien, dan CariDokter */
void PilihanCari (UserList uList, char* prompt);

/* Menampilkan menu pilihan untuk mencari data user, dokter, atau pasien */
void MenuCari (int *basis, char *basisCari, char *data, int pilihan);

/* Menampilkan seluruh data user yang terdapat pada user.csv */
void CariUser (UserList uList, int pilihan);

/* Menampilkan seluruh data pasien yang terdapat pada user.csv */
void CariPasien (UserList uList);

/* Menampilkan seluruh data dokter yang terdapat pada user.csv */
void CariDokter (UserList uList);
#endif