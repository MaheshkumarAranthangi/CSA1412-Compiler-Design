// #192424420
/*
 Exp 15 - Operator precedence parsing (simple table-driven for + and * and parentheses)
*/
#include <stdio.h>
#include <string.h>

int prec(char a, char b){
    // returns -1 if a < b (shift), 0 equal, 1 if a > b (reduce)
    // Simplified mapping for +,*,(,),i,$
    const char *order = "+*-()i$";
    // define precedence manually:
    if (a=='+' && b=='+') return 1;
    if (a=='+' && b=='*') return -1;
    if (a=='*' && b=='+') return 1;
    if (a=='*' && b=='*') return 1;
    if (a=='(') return -1;
    if (b==')') return 1;
    if (b=='$') return 1;
    return -1;
}

int main(void){
    char in[256];
    printf("Enter expression with single-letter identifiers (use i for id), append $ or not:\n");
    if(!scanf("%255s", in)) return 0;
    strcat(in, "$");
    char stack[256] = "$";
    int sp = 1, ip = 0;
    printf("STACK\tINPUT\tACTION\n");
    while(1){
        char a = stack[strlen(stack)-1];
        char b = in[ip];
        int r = prec(a,b);
        if (r==-1){
            // shift
            int L=strlen(stack); stack[L]=b; stack[L+1]=0; ip++;
            printf("%s\t%s\tShift\n", stack, in+ip);
        } else {
            // reduce (very simplified): replace i with E, and E+E/E*E -> E
            // perform naive reductions
            char *p = strstr(stack, "i");
            if(p){ *p='E'; printf("%s\t%s\tReduced i->E\n", stack, in+ip); continue; }
            if (strstr(stack, "E+E") || strstr(stack, "E*E")){
                char *q = strstr(stack, "E+E"); if(!q) q = strstr(stack,"E*E");
                if(q){ *q='E'; memmove(q+1, q+3, strlen(q+3)+1); printf("%s\t%s\tReduced E op E -> E\n", stack, in+ip); continue; }
            }
            if (a=='$' && b=='$') break;
            // fallback shift to avoid infinite loop
            if (b=='$') break;
            int L=strlen(stack); stack[L]=b; stack[L+1]=0; ip++;
        }
    }
    if (strcmp(stack, "$E$")==0 || strcmp(stack, "E")==0) printf("Accepted\n"); else printf("Resulting stack: %s\n", stack);
    return 0;
}
