#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FIELDS 20
#define MAX_FIELD_LENGTH 100
#define MAX_LINE_LENGTH 256

/*Mengembalikan hasil encoding dari string*/
char* runLengthEncoding(const char* a);

/*Melakukan update data fields[replaceIndex] pada file user.csv*/
void updateFile(const char* user, int replaceIndex, const char* newValue);

#endif