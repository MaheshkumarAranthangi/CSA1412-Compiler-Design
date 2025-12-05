// #192424420
/*
 Exp 02 - Detect if a given line is a comment (// or /* ... */)
*/
#include <stdio.h>
#include <string.h>

int main(void) {
    char s[256];
    printf("Enter line:\n");
    if(!fgets(s, sizeof(s), stdin)) return 0;
    // strip newline
    size_t n = strlen(s); if (n && s[n-1]=='\n') s[n-1]=0;

    if (s[0] == '/' && s[1] == '/') {
        printf("It is a single-line comment (//)\n");
    } else if (s[0] == '/' && s[1] == '*') {
        // look for closing */
        if (strstr(s, "*/") != NULL) printf("It is a block comment (/* ... */) on one line\n");
        else printf("It starts a block comment (/*) but no closing (*/ ) found on this line\n");
    } else {
        printf("It is NOT a comment\n");
    }
    return 0;
}
