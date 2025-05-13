#include "../header/password.h"

char* runLengthEncoding(const char* a){
    //Alokasi memori di heap 
    char* encoding = malloc(2001); 
    if (!encoding) return NULL;
    encoding[0] = '\0';

    //Proses encoding string a 
    int count = 1;
    char prev = a[0];
    for(int i=1; i<strlen(a); i++){     
        if(a[i] == prev){
            count++;    //Menghitung jumlah kemunculan karakter
        } else{
            if (count==1){            
                char temp[30];
                sprintf(temp, "%c", prev);   //Tulis karakternya saja
                strcat(encoding, temp);
                prev = a[i];
            }
            else{
                char temp[30];        
                sprintf(temp, "%d%c", count, prev);  //Tulis jumlah kemunculan beserta karakternya
                strcat(encoding, temp);   
                prev = a[i];
                count = 1;
            }
        }
    } 
    //Pengecekan elemen terakhir
    if (count==1){
        char temp[30];
        sprintf(temp, "%c", prev);
        strcat(encoding, temp);
    }
    else{
        char temp[30];
        sprintf(temp, "%d%c", count, prev);
        strcat(encoding, temp);
    }
    return encoding;   
}
void updateFile(const char* user, int replaceIndex, const char* newValue){
    FILE *userfile = fopen("data/user.csv", "r");
    FILE *temp = fopen("data/temp.csv", "w");    //File temp untuk salin isi file user.csv beserta updatenya
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

        //Jika menemukan username yang sesuai, ubah fields[replaceIndex] dengan newValue
        if (strcmp(fields[1], user) == 0){
            strcpy(fields[replaceIndex], newValue);
        }

        //Menyalin perubahan ke file output
        for (int i = 0; i < field_idx; i++) {
            fprintf(temp, "%s", fields[i]);
            if (i < field_idx-1) fprintf(temp, ";");
        }
        fprintf(temp, "\n");
    }
    fclose(userfile);
    fclose(temp);
    //Menjadikan file temp sebagai user.csv
    remove("data/user.csv");
    rename("data/temp.csv", "data/user.csv");
}