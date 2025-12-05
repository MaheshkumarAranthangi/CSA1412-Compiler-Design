// #192411237
/*
 Exp 09 - Eliminate immediate left recursion for one production like A->Aalpha|beta
 This program handles immediate left recursion for a single non-terminal's production alternatives.
*/
#include <stdio.h>
#include <string.h>

int main(void){
    char prod[256];
    printf("Enter production in form A->alpha1|alpha2|... :\n");
    if(!fgets(prod, sizeof(prod), stdin)) return 0;
    prod[strcspn(prod, "\n")] = 0;
    char A = prod[0];
    // parse RHS after "->"
    char *rhs = strstr(prod, "->");
    if(!rhs){ printf("Invalid format\n"); return 0; }
    rhs += 2;
    // split alternatives by '|'
    char *alts[20]; int na=0;
    alts[na++] = strtok(rhs, "|");
    while((alts[na++] = strtok(NULL, "|")) && na<20) ;
    na--; // last was NULL
    char beta_list[1024] = {0}, alpha_list[1024] = {0};
    for(int i=0;i<na;i++){
        if(alts[i][0]==A){
            // left recursive: skip leading A
            strncat(alpha_list, alts[i]+1, sizeof(alpha_list)-strlen(alpha_list)-1);
            strncat(alpha_list, "|", sizeof(alpha_list)-strlen(alpha_list)-1);
        } else {
            strncat(beta_list, alts[i], sizeof(beta_list)-strlen(beta_list)-1);
            strncat(beta_list, "|", sizeof(beta_list)-strlen(beta_list)-1);
        }
    }
    if(alpha_list[0]==0){ printf("No immediate left recursion detected for %c\n", A); return 0; }
    // remove trailing |
    if(beta_list[strlen(beta_list)-1]=='|') beta_list[strlen(beta_list)-1]=0;
    if(alpha_list[strlen(alpha_list)-1]=='|') alpha_list[strlen(alpha_list)-1]=0;
    char Aprime = A + '\'';
    printf("%c -> ", A);
    // print betas with Aprime
    char *p = strtok(beta_list, "|");
    int first=1;
    while(p){
        if(!first) printf(" | ");
        printf("%s%c", p, Aprime);
        first=0;
        p = strtok(NULL, "|");
    }
    printf("\n%c -> ", Aprime);
    p = strtok(alpha_list, "|");
    first=1;
    while(p){
        if(!first) printf(" | ");
        printf("%s%c", p, Aprime);
        first=0;
        p = strtok(NULL, "|");
    }
    printf(" | epsilon\n");
    return 0;
}
