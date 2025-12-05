//// #192411237*
 Exp 08 - Compute FOLLOW set (simplified educational version)
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXP 20
char prod[MAXP][64];
int nprod=0;

void add_unique(char *s, char ch){
    if (!strchr(s,ch)) { size_t l=strlen(s); s[l]=ch; s[l+1]=0; }
}

void compute_first_char(char X, char *out){
    // simplified: if terminal -> itself. else find first char of RHS
    if(!isupper((unsigned char)X)){ out[0]=X; out[1]=0; return; }
    for(int i=0;i<nprod;i++){
        if(prod[i][0]==X && prod[i][1]=='-' && prod[i][2]=='>'){
            char rhs = prod[i][3];
            out[0]=rhs; out[1]=0; return;
        }
    }
    out[0]=0;
}

void compute_follow(char A, char *out){
    // extremely simplified: add $ if start symbol, and add terminals that follow A directly in productions.
    if (prod[0][0] == A) add_unique(out, '$');
    for(int i=0;i<nprod;i++){
        char *rhs = strchr(prod[i], '>'); if(!rhs) continue; rhs++;
        for(size_t j=0;j<strlen(rhs);++j){
            if (rhs[j]==A && rhs[j+1]){
                char next = rhs[j+1];
                if (!isupper((unsigned char)next)) add_unique(out, next);
                else {
                    char tmp[4]={0}; compute_first_char(next, tmp); if(tmp[0]) add_unique(out, tmp[0]);
                }
            } else if (rhs[j]==A && rhs[j+1]==0){
                add_unique(out, prod[i][0]);
            }
        }
    }
}

int main(void){
    printf("Enter number of productions: ");
    if(scanf("%d%*c",&nprod)!=1) return 0;
    for (int i=0;i<nprod;i++){ fgets(prod[i], sizeof(prod[i]), stdin); prod[i][strcspn(prod[i],\"\\n\")]=0; }
    char A; printf("Enter non-terminal to find FOLLOW: "); scanf(\" %c\", &A);
    char out[64]={0};
    compute_follow(A, out);
    if(out[0]) printf(\"FOLLOW(%c) = { %s }\\n\", A, out); else printf(\"FOLLOW(%c) could not be computed by this simple tool\\n\", A);
    return 0;
}
