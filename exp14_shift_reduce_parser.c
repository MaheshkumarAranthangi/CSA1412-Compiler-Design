// #192411237
/*
 Exp 14 - Very small shift-reduce parser simulator for grammar E->E+E | E*E | a | b
*/
#include <stdio.h>
#include <string.h>

int main(void){
    char in[128], stack[256] = "$";
    printf("Enter input (e.g. a+b):\n");
    if(!scanf("%127s", in)) return 0;
    strcat(in, "$");
    printf("STACK\tINPUT\tACTION\n");
    int ip=0, sp=1; // stack contains characters starting at index 1
    stack[1]=0;
    while (in[ip]){
        // shift one symbol
        int len = strlen(stack);
        stack[len]=in[ip]; stack[len+1]=0; ip++;
        printf("%s\t%s\tShift\n", stack, in+ip);
        // check simple reductions
        // reduce 'a' or 'b' to E
        if (stack[len]=='a' || stack[len]=='b'){
            stack[len]='E'; stack[len+1]=0;
            printf("%s\t%s\tReduced: E->a/b\n", stack, in+ip);
        }
        // reduce E+E or E*E to E
        int L = strlen(stack);
        if (L>=3 && stack[L-3]=='E' && (stack[L-2]=='+'||stack[L-2]=='*') && stack[L-1]=='E'){
            stack[L-3]='E'; stack[L-2]=0; stack[L-1]=0;
            printf("%s\t%s\tReduced: E->E+E/E*E\n", stack, in+ip);
        }
    }
    if (strcmp(stack, "E")==0) printf("ACCEPT\n"); else printf("REJECT\n");
    return 0;
}
