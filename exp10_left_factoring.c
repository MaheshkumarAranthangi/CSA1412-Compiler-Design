// #192411237
/*
 Exp 10 - Left factoring for two alternatives (simple)
*/
#include <stdio.h>
#include <string.h>

int main(void){
    char prod[256];
    printf("Enter production S->part1|part2 :\n");
    if(!fgets(prod,sizeof(prod),stdin)) return 0;
    prod[strcspn(prod,\"\n\")]=0;
    // find ->
    char *rhs = strstr(prod, "->"); if(!rhs){ printf("Invalid format\n"); return 0; }
    rhs += 2;
    char *bar = strchr(rhs, '|');
    if(!bar){ printf("No alternatives found\n"); return 0; }
    *bar = 0;
    char *p1 = rhs;
    char *p2 = bar+1;
    // find common prefix
    int i=0;
    while(p1[i] && p2[i] && p1[i]==p2[i]) i++;
    if(i==0) { printf("No common prefix, no left factoring needed.\n"); return 0; }
    char prefix[128]; strncpy(prefix,p1,i); prefix[i]=0;
    char X = 'X';
    printf("S -> %s%c\n", prefix, X);
    printf("%c -> %s | %s\n", X, p1+i, p2+i);
    return 0;
}
