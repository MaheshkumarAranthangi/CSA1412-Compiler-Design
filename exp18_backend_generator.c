// #192411237
/*
 Exp 18 - Very simple backend-like translator: reads 3-address-like lines and prints mock assembly
 Example input lines: a = b + c
*/
#include <stdio.h>
#include <string.h>

int main(void){
    char lhs[64], eq[4], op1[64], op[4], op2[64];
    printf("Enter number of statements (n): ");
    int n; if(scanf("%d%*c", &n)!=1) return 0;
    for(int i=0;i<n;i++){
        printf("Enter statement %d (format: a = b + c):\n", i+1);
        if(scanf("%63s%3s%63s%3s%63s", lhs, eq, op1, op, op2)!=5){ 
            // maybe binary operator missing (like a = b)
            // try simpler parse
            rewind(stdin);
            break;
        }
        printf("mov %s, R%d\n", op1, i);
        if(strcmp(op, "+")==0) printf("add %s, R%d\n", op2, i);
        else if(strcmp(op, "-")==0) printf("sub %s, R%d\n", op2, i);
        else if(strcmp(op, "*")==0) printf("mul %s, R%d\n", op2, i);
        else if(strcmp(op, "/")==0) printf("div %s, R%d\n", op2, i);
        printf("mov R%d, %s\n", i, lhs);
    }
    return 0;
}
