// 192411237
//  Trailing Operator-Precedence Parser (Toy Example)
//  This demonstrates how "trailing" operator precedence works
//  Accepts single-character operands (a, b, 1, 2...) and:
//      +  -  *  /  (  ) 
// 

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXSTACK 100

// Trailing-precedence table
//   <  means SHIFT
//   >  means REDUCE
//   =  means MATCH (for parentheses)
//   ?  means invalid combination

char trailingPrecTable[7][7] = {
/*          +    -    *    /    (    )    id */
/* + */   { '>', '>', '<', '<', '<', '>', '<' },
/* - */   { '>', '>', '<', '<', '<', '>', '<' },
/* * */   { '>', '>', '>', '>', '<', '>', '<' },
/* / */   { '>', '>', '>', '>', '<', '>', '<' },
/* ( */   { '<', '<', '<', '<', '<', '=', '<' },
/* ) */   { '>', '>', '>', '>', '?', '>', '?' },
/* id*/   { '>', '>', '>', '>', '?', '>', '?' }
};

// Map symbol to table index
int getIndex(char c) {
    switch (c) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        default:  return 6;  // id
    }
}

// Stack for parser
char stack[MAXSTACK];
int top = 0;

void push(char c) { stack[top++] = c; }
char pop()        { return stack[--top]; }

// Returns the closest terminal symbol from right of stack
char topTerminal() {
    for (int i = top - 1; i >= 0; i--) {
        // If alphanumeric then treat as ID
        if (isalnum(stack[i])) return 'i';
        // Operator or parenthesis
        if (strchr("+-*/()", stack[i])) return stack[i];
    }
    return '$';
}

int main(void) {
    printf("Trailing Operator-Precedence Parser (Toy Example)\n");
    printf("Enter expression (e.g., a+b*c): ");

    char input[100];
    scanf("%s", input);

    strcat(input, "$");       // End marker
    push('$');                // Start stack

    int i = 0;
    char a = input[i];        // Current input symbol

    while (1) {
        char t = topTerminal(); 
        char op = trailingPrecTable[getIndex(t)][getIndex(a)];

        if (op == '<' || op == '=') {
            // SHIFT
            printf("SHIFT: %c\n", a);
            push(a);
            a = input[++i];
        }
        else if (op == '>') {
            // REDUCE (toy version: only pop one symbol)
            printf("REDUCE on stack element: %c\n", stack[top - 1]);
            pop();
        }
        else {
            printf("ERROR: invalid expression (conflict between %c and %c)\n", t, a);
            return 1;
        }

        // Accepting condition:
        if (a == '$' && top == 1 && stack[0] == '$') {
            printf("ACCEPT: valid expression!\n");
            break;
        }
    }

    return 0;
}
