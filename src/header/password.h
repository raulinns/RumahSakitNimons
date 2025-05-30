#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file/field.h"

#define MAX_FIELDS 20

/*Mengembalikan hasil encoding dari string*/
char* runLengthEncoding(const char* a);

/*Melakukan update data fields[replaceIndex] pada file user.csv*/
void updateFile(const char* user, int replaceIndex, const char* newValue);

#endif