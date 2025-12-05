// #192411237
/*
 Exp 16 - Generate three address code for simple expression like out = in1 + in2 + in3 - in4
 This is a simple translator that creates temporaries for left-to-right evaluation.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    char line[256];
    printf("Enter expression like out = in1 + in2 + in3 - in4\\n");
    if(!fgets(line,sizeof(line),stdin)) return 0;
    // For simplicity, tokenise by spaces
    char *tokens[64]; int nt=0;
    char *p = strtok(line, " \t\n");
    while(p){ tokens[nt++]=p; p=strtok(NULL," \t\n"); }
    // find '='
    int eq = -1; for(int i=0;i<nt;i++) if(strcmp(tokens[i],"=")==0){ eq=i; break; }
    if(eq==-1){ printf("No assignment found\\n"); return 0; }
    char *target = tokens[0];
    // process RHS tokens from eq+1
    int tempcnt=1;
    char prev_temp[32] = {0};
    // build list of operands and operators
    char *ops[64]; int opn=0;
    for(int i=eq+1;i<nt;i++) ops[opn++]=tokens[i];
    // very naive left-to-right handling: a op b -> t1=a op b; then t2=t1 op c etc.
    char tname[32];
    int first = 1;
    for(int i=0;i<opn;){
        if(first){
            char *a = ops[i++];
            char *op = (i<opn?ops[i++]:NULL);
            char *b = (i<opn?ops[i++]:NULL);
            if(!op || !b) break;
            snprintf(tname, sizeof(tname), "t%d", tempcnt++);
            printf("%s = %s %s %s\n", tname, a, op, b);
            strcpy(prev_temp, tname);
            first = 0;
        } else {
            char *op = (i<opn?ops[i++]:NULL);
            char *b = (i<opn?ops[i++]:NULL);
            if(!op || !b) break;
            snprintf(tname, sizeof(tname), "t%d", tempcnt++);
            printf("%s = %s %s %s\n", tname, prev_temp, op, b);
            strcpy(prev_temp, tname);
        }
    }
    printf("%s = %s\n", target, prev_temp);
    return 0;
}
