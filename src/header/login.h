#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <string.h>
#include "user.h"
#include "password.h"

#define MAX_FIELDS 20
#define MAX_FIELD_LENGTH 100

extern char user[1001], pass[1001];
extern maxID;

typedef enum LoggedIn //State of login
    {
        NotLoggedIn /*0*/, Manager /*1*/, Dokter /*2*/, Pasien /*3*/
    } LoggedIn;

extern LoggedIn loggedIn;

// Cari indeks user dalam UserList berdasarkan username
int getIDbyName(UserList uList, char* name);

// Cari ID numerik user berdasarkan username
int findID(UserList uList, char* name);

// Fungsi login, validasi username dan password, lalu mengembalikan role user
int login(UserList uList);

// Registrasi user baru sebagai pasien, tambah data user dan pasien baru
int Register(UserList* uList);

// Update password user setelah verifikasi username dan kode unik
int passwordUpdate();

#endif