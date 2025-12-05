// #192424420
/*
 Exp 13 - Simple top-down / bottom-up demonstrator (very small)
 This program checks membership for a tiny grammar S->aS | Sb | ab
*/
#include <stdio.h>
#include <string.h>

int check(const char *str){
    // brute force simulation: accept strings that are of form a^n b^m with at least one a and one b and all a's before b's
    int i=0;
    int n = strlen(str);
    if (n<2) return 0;
    while(i<n && str[i]=='a') i++;
    if(i==0) return 0;
    int j=i;
    while(j<n && str[j]=='b') j++;
    return j==n && str[n-1]=='b';
}

int main(void){
    char s[128];
    printf("Enter string:\n");
    if(!scanf("%127s", s)) return 0;
    if (check(s)) printf("String accepted\n"); else printf("String not accepted\n");
    return 0;
}
