#include "../header/user.h"

int IdxUser(char *name){
    FILE *userfile = fopen("file/user.csv","r");
    if (userfile == NULL)
    {
        perror("Error opening file");
        return -1;
    }
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELDS][MAX_FIELD_LENGTH];

    while (fgets(line, sizeof(line), userfile))
    {
        int field_idx = 0, char_idx = 0;
        for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++)
        {
            if (line[i] == ';') //parsing dengan pembeda ";"
            {
                fields[field_idx][char_idx] = '\0'; // end current field
                field_idx++;
                char_idx = 0;
            }
            else
            {
                fields[field_idx][char_idx++] = line[i];
            }
        }
        fields[field_idx][char_idx] = '\0'; // terminate last field
        field_idx++;

        //Checking valid username
        if (strcmp(name,fields[1]) == 0)
        {
            return atoi(fields[0]);
        }
    }
    
    fclose(userfile);

    return -1;
}

void AddUser(char *name, char *pass){
    FILE * fp = fopen("file/user.csv","a");
    fprintf(fp, ";%s;%s;;;;;;;;;;;;;\n", name, pass);
    fclose(fp);
}