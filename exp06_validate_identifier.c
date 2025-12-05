// #192424420
/*
 Exp 06 - Validate whether an input string is a valid C-style identifier
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void){
    char s[256];
    printf("Enter identifier to validate:\n");
    if(!fgets(s,sizeof(s),stdin)) return 0;
    size_t n=strcspn(s,"\n"); s[n]=0;
    if (s[0]==0){ printf("Empty\\n"); return 0; }
    if (!(isalpha((unsigned char)s[0]) || s[0]=='_')){ printf("Invalid identifier (must start with letter or _).\\n"); return 0; }
    for (size_t i=1;i<strlen(s);++i){
        if (!(isalnum((unsigned char)s[i]) || s[i]=='_')){ printf("Invalid identifier (invalid char found).\\n"); return 0; }
    }
    printf("Valid identifier\\n");
    return 0;
}
