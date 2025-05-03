#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <string.h>
#include "user.h"

#define MAX_LINE_LENGTH 256
#define MAX_FIELDS 20
#define MAX_FIELD_LENGTH 100

/* Melakukan sequensial searching user.csv dan membandingkan username dan password dengan input */
int login();

/* Menambahkan user baru pada user.csv */
void Register();

#endif