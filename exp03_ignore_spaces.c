// #192424420
/*
 Exp 03 - Remove redundant spaces, tabs, newlines and ignore simple comments
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void){
    char in[1024];
    printf("Enter input (end with EOF / Ctrl-D):\n");
    size_t len = fread(in,1,sizeof(in)-1,stdin);
    in[len]=0;

    int i=0;
    int in_comment = 0;
    while(in[i]){
        if(!in_comment && in[i]=='/' && in[i+1]=='*'){ in_comment = 1; i+=2; continue; }
        if(in_comment && in[i]=='*' && in[i+1]=='/'){ in_comment = 0; i+=2; continue; }
        if(in_comment){ i++; continue; }
        if(isspace((unsigned char)in[i])){
            // print single space for runs of whitespace
            putchar(' ');
            while(isspace((unsigned char)in[i])) i++;
            continue;
        }
        putchar(in[i++]);
    }
    return 0;
}
