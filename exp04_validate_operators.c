// #192424420
/*
 Exp 04 - Validate operators (very small validator)
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void){
    char s[256];
    printf("Enter the token to check (single char or operator):\n");
    if(!fgets(s,sizeof(s),stdin)) return 0;
    char c = s[0];
    if (strchr("+-*/=%", c)) printf("Operator\n");
    else printf("Not an operator (by simple check)\n");
    return 0;
}
