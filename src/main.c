// Include any necessary headers
#include <stdio.h>
#include <string.h>
#include "header/login.h"
#include "header/user.h"
#include "header/password.h"

int main()
{
    char prompt[1001];
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
	if (strcmp(prompt,"LUPA_PASSWORD") == 0)
    {
        passwordUpdate();
    }
}