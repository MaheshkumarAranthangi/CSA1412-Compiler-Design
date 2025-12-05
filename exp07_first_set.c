// #192424420
/*
 Exp 07 - Compute FIRST set for a tiny grammar given as productions (simple)
 This is a simplified, educational implementation for single-character tokens.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXP 20
char prod[MAXP][32];
int nprod=0;

void compute_first(char X, char *out){
    // very small: if X is terminal (lowercase or symbol) -> FIRST = X
    char buf[64]={0};
    if (!isupper((unsigned char)X)) { out[0]=X; out[1]=0; return; }
    for (int i=0;i<nprod;i++){
        if (prod[i][0]==X && prod[i][1]=='-' && prod[i][2]=='>' ){
            char rhs = prod[i][3];
            if (!isupper((unsigned char)rhs)){ out[0]=rhs; out[1]=0; return; }
            // recursive (take first of rhs)
            compute_first(rhs, out);
            return;
        }
    }
    out[0]=0;
}

int main(void){
    printf("Enter number of productions (<=%d): ", MAXP);
    if(scanf("%d%*c",&nprod)!=1) return 0;
    for (int i=0;i<nprod;i++){
        fgets(prod[i], sizeof(prod[i]), stdin);
        // strip newline
        prod[i][strcspn(prod[i], "\n")]=0;
    }
    char X;
    printf("Enter symbol to compute FIRST for: ");
    scanf(" %c", &X);
    char out[64]={0};
    compute_first(X, out);
    if(out[0]) printf("FIRST(%c) = { %s }\n", X, out);
    else printf("FIRST(%c) is empty or could not be computed by this simple tool\n", X);
    return 0;
}
