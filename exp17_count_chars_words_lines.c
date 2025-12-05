
/*192411237
 Exp 17 - Count characters, words and lines from stdin input (clean)
*/
#include <stdio.h>
#include <ctype.h>

int main(void){
    int c;
    long nchar=0, nword=0, nline=0;
    int inword=0;
    while((c=getchar())!=EOF){
        nchar++;
        if(c=='\\n') nline++;
        if(isspace(c)){
            if(inword){ nword++; inword=0; }
        } else inword = 1;
    }
    if(inword) nword++;
    // treat empty input as zero counts
    printf("Number of characters = %ld\n", nchar);
    printf("Number of words = %ld\n", nword);
    printf("Number of lines = %ld\n", nline);
    return 0;
}
