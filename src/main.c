// Include any necessary headers
#include <stdio.h>
#include <string.h>
#include "header/login.h"
#include "header/denah.h"

int main()
{
    char prompt[1001];
    Matrix denah; int i = 0;
    CreateDenah(&denah);
    printf("========================================\n");
    printf(">>> ");
    scanf("%s", prompt);
    if (strcmp(prompt,"LOGIN") == 0)
    {
        login();
    }
    if( strcmp(prompt,"REGISTER") == 0){
        Register();
    }
    if (strcmp(prompt, "LIHAT_DENAH") == 0) {
        PrintDenah(denah);
    }
    if (strcmp(ParseData(prompt, i, ' '), "LIHAT_RUANGAN") == 0) {
        PrintRuang(prompt, denah);
    }
    if (strcmp(ParseData(prompt, i, ' '), "UBAH_DENAH") == 0) {
        UbahDenah(prompt, &denah);
    }
}