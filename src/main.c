// Include any necessary headers
#include <stdio.h>
#include <string.h>
#include "header/login.h"

int main()
{
    char prompt[1001];
    printf("========================================\n");
    printf(">>> ");
    scanf("%s", &prompt);
    if (strcmp(prompt,"LOGIN") == 0)
    {
        login();
    }
    if( strcmp(prompt,"REGISTER") == 0){
        Register();
    }
}