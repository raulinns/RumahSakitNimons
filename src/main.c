// Include any necessary headers
#include <stdio.h>
#include <string.h>
#include "header/tes.h"
#include "header/login.h"


int main()
{
    // Your code goes here
    char promt[1001];
    printf("========================================\n");
    printf(">>> ");
    scanf("%s", &promt);
    if (strcmp(promt,"LOGIN") == 0)
    {
        login();
    }
    //printf("Hello, World!\n");
    //tes();
    return 0;
}