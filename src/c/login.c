
#include "../header/login.h"
#include "../header/denah.h"
int login()
{
    FILE *userfile = fopen("file/username.csv","r");
    if (userfile == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    int validuser = 0,validpass = 0;
    char user[1001], pass[1001];
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELDS][MAX_FIELD_LENGTH];
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);

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
        if (strcmp(user,fields[1]) == 0)
        {
            validuser = 1;
            //Checking valid password for username
            if (strcmp(pass,fields[2]) == 0)
            {
                validpass = 1;
            }
            break;
        }
    }
    
    fclose(userfile);
    if (validuser == 1)
    {
        if (validpass == 1)
        {
            if (strcmp(fields[3],"Manager") == 0)
            {
                printf("Selamat pagi Manager %s!\n",user);
            }
            else if (strcmp(fields[3],"Dokter") == 0)
            {
                printf("Selamat pagi Dokter %s!\n",user);
            }
            else if (strcmp(fields[3],"Pasien") == 0)
            {
                printf("Selamat pagi %s! Ada keluhan apa ?\n",user);
            }
        }
        else
        {
            printf("Password salah untuk pengguna yang bernama %s!\n",user);
            login();
        }
    }
    else
    {
        printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n",user);
        login();
    }
    
    return 0;
}

void Register(){
    char user[1001], pass[1001];
    printf("Username: ");
    scanf("%s", user);

    if( IdxUser(user) != -1 ) // User dengan nama yang sama sudah ada
    {
        printf("Registrasi gagal! Pasien dengan nama Denis sudah terdaftar.\n");
        return;
    }

    printf("Pass: ");
    scanf("%s", pass);

    /* Menambahkan data user baru pada user.csv */
    AddUser(user,pass);

    printf("Selamat pagi %s! Ada keluhan apa ?\n", user);
    return;
}

int passwordUpdate(){
    FILE *userfile = fopen("file/username.csv","r");
    if (userfile == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    char user[1001], new_pass[1001], code[1001];
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELDS][MAX_FIELD_LENGTH];
    printf("Username: ");
    scanf("%s", user);
    printf("Kode Unik: ");
    scanf("%s", code);
    int validuser = 0;

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
        //Jika username ditemukan 
        if(strcmp(user, fields[1]) == 0){
            validuser = 1;
            break;
        }
    }
    fclose(userfile);

    //Validasi username dan kode unik
    if (validuser == 1){
        char* encoded = runLengthEncoding(fields[1]);
        if(strcmp(code, encoded) == 0){       
            if (strcmp(fields[3],"Manager") == 0)
            {
                printf("Halo manager %s, silakan daftarkan ulang password anda!\n", user);;
            }
            else if (strcmp(fields[3],"Dokter") == 0)
            {
                printf("Halo dokter %s, silakan daftarkan ulang password anda!\n", user);
            }
            else if (strcmp(fields[3],"Pasien") == 0)
            {
                printf("Halo pasien %s, silakan daftarkan ulang password anda!\n", user);
            }
            printf("Password Baru: ");
            scanf("%s", new_pass);
            free(encoded);
            //Update file CSV dengan password yang baru
            updateFile(user, 2, new_pass);
            //Kembali ke menu login 
            printf("========================================\n");
            printf(">>> LOGIN\n");
            login();      
        }
        else{
            printf("Kode unik salah!\n");
            free(encoded);
        }
    } else{
        printf("Username tidak terdaftar!\n"); 
    }

    return 0;
}