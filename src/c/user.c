#include "../header/file/user.h"
#include "../header/user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD_LENGTH 100

char *ParseData(char *line, int *i, char token) {
    char *data = (char *)malloc(MAX_FIELD_LENGTH * sizeof(char));
    if (data == NULL) return NULL;

    int idx = 0;
    while (line[*i] != token && line[*i] != '\n' && line[*i] != '\0') {
        data[idx++] = line[*i];
        (*i)++;
    }

    data[idx] = '\0'; // null-terminate
    if (line[*i] == token) {
        (*i)++; // lewati token
    }

    return data;
}

// int IdxUser(char *name){
//     FILE *userfile = fopen("data/user.csv","r");
//     if (userfile == NULL)
//     {
//         perror("Error opening file");
//         return -1;
//     }
//     char line[MAX_LINE_LENGTH];
//     char fields[MAX_FIELDS][MAX_FIELD_LENGTH];

//     while (fgets(line, sizeof(line), userfile))
//     {
//         int field_idx = 0, char_idx = 0;
//         for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++)
//         {
//             if (line[i] == ';') //parsing dengan pembeda ";"
//             {
//                 fields[field_idx][char_idx] = '\0'; // end current field
//                 field_idx++;
//                 char_idx = 0;
//             }
//             else
//             {
//                 fields[field_idx][char_idx++] = line[i];
//             }
//         }
//         fields[field_idx][char_idx] = '\0'; // terminate last field
//         field_idx++;

//         //Checking valid username
//         if (strcmp(name,fields[1]) == 0)
//         {
//             return atoi(fields[0]);
//         }
//     }
    
//     fclose(userfile);

//     return -1;
// }

char *NamaUser(int idx) {
    FILE *userFile = fopen("../data/user.csv", "r");
    char name[MAX_FIELD_LENGTH], line[MAX_LINE_LENGTH];
    int id, i;
    while (id != idx) {
        fgets(line, MAX_LINE_LENGTH, userFile);
        i = 0;
        id = atoi(ParseData(line, i, ';'));
    }
    fclose(userFile);
    int temp = i;
    strcpy(name, ParseData(line, i, ';'));
    return name;
}

char* to_string(int value) {
    char* buffer = malloc(12 * sizeof(char)); 
    if (buffer != NULL) {
        snprintf(buffer, 12, "%d", value);
    }
    return buffer;
}

void AddUser(char *name, char *pass, UserList *uList){
    int len = uList->len;
    char* temp = to_string(len);
    User* newUser = &uList->contents[uList->len];

    strcpy( &newUser->field[0] , temp );
    strcpy( &newUser->field[1] , name );
    strcpy( &newUser->field[2] , pass );
    strcpy( &newUser->field[3] , "Pasien" );

    free(temp);
    uList->len = uList->len + 1;
}