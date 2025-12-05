// #192411237
/*
 Exp 01 - Lexical Analyzer (identify identifiers, constants, operators)
 Cleaned and safe C version
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    char line[512];
    char identifiers[256] = {0};
    char operators[256] = {0};
    int idc = 0, opc = 0, cc = 0;

    printf("Enter the string:\n");
    if (!fgets(line, sizeof(line), stdin)) return 0;

    for (size_t i = 0; i < strlen(line); ++i) {
        if (isspace((unsigned char)line[i])) continue;
        if (isalpha((unsigned char)line[i])) {
            // collect continuous identifier characters (simple)
            identifiers[idc++] = line[i];
            // skip to end of identifier
            while (isalnum((unsigned char)line[i+1])) {
                i++;
                identifiers[idc++] = line[i];
            }
            identifiers[idc++] = ' ';
        } else if (isdigit((unsigned char)line[i])) {
            // collect a numeric constant
            int val = 0;
            while (isdigit((unsigned char)line[i])) {
                val = val * 10 + (line[i] - '0');
                i++;
            }
            i--;
            char tmp[32];
            snprintf(tmp, sizeof(tmp), "%d ", val);
            strncat(identifiers+strlen(identifiers), tmp, sizeof(identifiers)-strlen(identifiers)-1); // reuse identifiers buffer for simplicity
            cc++;
        } else {
            // common operators
            if (strchr("+-*/=%", line[i])) {
                operators[opc++] = line[i];
                operators[opc++] = ' ';
            }
        }
    }

    if (idc) identifiers[idc] = '\\0';
    if (opc) operators[opc] = '\\0';

    printf("Identifiers: %s\n", identifiers[0] ? identifiers : "None");
    printf("Operators: %s\n", operators[0] ? operators : "None");
    printf("Constants counted (approx): %d\n", cc);
    return 0;
}
