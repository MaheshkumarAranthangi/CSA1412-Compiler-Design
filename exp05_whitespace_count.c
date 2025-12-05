// #192411237
/*
 Exp 05 - Count whitespace/newlines (simple)
*/
#include <stdio.h>

int main(void){
    int c;
    int words=0, lines=0, chars=0;
    int inword=0;
    printf("Enter text (Ctrl-D to end):\n");
    while((c=getchar())!=EOF){
        chars++;
        if(c=='\\n') lines++;
        if(c==' '||c=='\\n' || c=='\\t') {
            if(inword){ words++; inword=0; }
        } else inword=1;
    }
    if(inword) words++;
    printf("Characters: %d\\nWords: %d\\nLines: %d\\n", chars, words, lines);
    return 0;
}
