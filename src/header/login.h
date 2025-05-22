#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <string.h>
#include "user.h"
#include "password.h"

#define MAX_FIELDS 20
#define MAX_FIELD_LENGTH 100

extern char user[1001], pass[1001];

typedef enum LoggedIn //State of login
    {
        NotLoggedIn /*0*/, Manager /*1*/, Dokter /*2*/, Pasien /*3*/
    } LoggedIn;

extern LoggedIn loggedIn;

/* Melakukan sequensial searching user.csv dan membandingkan username dan password dengan input */
int login(UserList uList);

/* Menambahkan user baru pada user.csv */
int Register(UserList* uList);

/* Mengupdate password pada username.csv */
int passwordUpdate();

void askQuestion();
#endif