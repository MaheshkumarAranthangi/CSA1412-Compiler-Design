// #192424420
/*
 // ============================================================
//  Leading-Operator-Precedence Parser (Toy Example)
//  Demonstrates how operator precedence parsing works
//  Accepts single-character operands and + - * / ( )
// ============================================================

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXSTACK 100

// Precedence relation table
//   < means SHIFT
//   > means REDUCE
//   = means MATCH (for parentheses)
//   ? means invalid combination

char precedenceTable[7][7] = {
/*          +    -    *    /    (    )    id */
/* + */   { '>', '>', '<', '<', '<', '>', '<' },
/* - */   { '>', '>', '<', '<', '<', '>', '<' },
/* * */   { '>', '>', '>', '>', '<', '>', '<' },
/* / */   { '>', '>', '>', '>', '<', '>', '<' },
/* ( */   { '<', '<', '<', '<', '<', '=', '<' },
/* ) */   { '>', '>', '>', '>', '?', '>', '?' },
/* id*/   { '>', '>', '>', '>', '?', '>', '?' }
};

// Map characters to table indices
int getIndex(char c) {
    switch(c) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        default:  return 6;  // id
    }
}

char stack[MAXSTACK];
int top = 0;

void push(char c) {
    stack[top++] = c;
}

char pop() {
    return stack[--top];
}

char topTerminal() {
    // Return rightmost terminal in stack
    for (int i = top - 1; i >= 0; i--) {
        if (!isalpha(stack[i]) && !isdigit(stack[i])) return stack[i];
        return 'i'; // treat operands as id
    }
    return '$';
}

int main(void) {

    printf("Leading Operator-Precedence Parser (Toy Example)\n");
    printf("Enter expression (e.g., a+b*c): ");

    char input[100];
    scanf("%s", input);

    // Append $ as input end marker
    strcat(input, "$");

    push('$');  // stack bottom

    int i = 0;
    char a = input[i];
    
    while (1) {
        char t = topTerminal();
        char op = precedenceTable[getIndex(t)][getIndex(a)];

        if (op == '<' || op == '=') {
            // SHIFT
            printf("SHIFT: %c\n", a);
            push(a);
            a = input[++i];
        }
        else if (op == '>') {
            // REDUCE
            printf("REDUCE\n");
            pop(); // reduce one symbol (toy version)
        }
        else {
            printf("ERROR: invalid expression\n");
            return 1;
        }

        if (a == '$' && top == 1) {
            printf("ACCEPT: valid expression\n");
            break;
        }
    }

    return 0;
}


