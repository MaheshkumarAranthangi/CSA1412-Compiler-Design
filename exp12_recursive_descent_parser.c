// #192411237
/*
 Exp 12 - Recursive descent parser for grammar:
 E -> T E'
 E' -> + T E' | epsilon
 T -> F T'
 T' -> * F T' | epsilon
 F -> (E) | id
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *s;
int pos;

void error(){ printf("Rejected\\n"); exit(0); }

void F(){
    if (s[pos]=='('){ pos++; // '('
        // parse E
        // E -> T E'
        // reuse functions below
        // forward declarations omitted in C; we'll define order
    } else if (isalpha((unsigned char)s[pos])) { pos++; } else error();
}

void Tprime();
void T(){
    if (s[pos]=='(' || isalpha((unsigned char)s[pos])){
        F();
        Tprime();
    } else error();
}

void Eprime();
void E(){
    T();
    Eprime();
}

void Eprime(){
    if (s[pos]=='+'){ pos++; T(); Eprime(); }
    // else epsilon -> do nothing
}

void Tprime(){
    if (s[pos]=='*'){ pos++; F(); Tprime(); }
    // else epsilon
}

int main(void){
    char input[256];
    printf("Enter string (no spaces), append $ at end or leave, parser will check until '\\0'):\n");
    if(!scanf("%s", input)) return 0;
    s = input; pos = 0;
    E();
    if (s[pos]=='\\0') printf("Accepted\\n"); else printf("Rejected\\n");
    return 0;
}
