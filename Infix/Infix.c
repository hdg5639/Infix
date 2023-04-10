#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

char postfix[MAX_STACK_SIZE];
char stack[MAX_STACK_SIZE];
int top = -1;

int Priority(char ch) {
    switch (ch) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

int Parentheses(char* infix) {
    int i, len;
    len = strlen(infix);
    for (i = 0; i < len; i++) {
        if (infix[i] == '(') {
            stack[++top] = infix[i];
        }
        else if (infix[i] == ')') {
            if (top < 0 || stack[top--] != '(') {
                return 0;
            }
        }
    }

    return top == -1;
}

void infix_to_postfix(int len, char infix[MAX_STACK_SIZE]) {
    int i, j;
    top = -1;
    for (i = 0, j = 0; i < len; i++) {
        if (isspace(infix[i])) {
            continue;
        }
        else if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            i--;
            postfix[j++] = ' ';
        }
        else if (infix[i] == '(') {
            stack[++top] = infix[i];
        }
        else if (infix[i] == ')') {
            while (stack[top] != '(') {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }
            top--;
        }
        else if (Priority(infix[i]) > 0) {
            while (top >= 0 && Priority(stack[top]) >= Priority(infix[i])) {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }
            stack[++top] = infix[i];
        }
        else {
            printf("Error: Invalid character.\n");
            system("pause");
            exit(1);
        }
    }

    while (top >= 0) {
        postfix[j++] = stack[top--];
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);
}

int eval(int len) {
    int i, j, k;
    for (i = 0, j = 0; i < len; i++) {
        if (isspace(postfix[i])) {
            continue;
        }
        else if (isdigit(postfix[i])) {
            k = 0;
            while (isdigit(postfix[i])) {
                k = k * 10 + postfix[i] - '0';
                i++;
            }
            i--;
            stack[++top] = k;
        }
        else if (Priority(postfix[i]) > 0) {
            if (top < 1) {
                printf("Error: Invalid expression.\n");
                system("pause");
                exit(1);
            }
            int b = stack[top--];
            int a = stack[top--];
            switch (postfix[i]) {
            case '+':
                stack[++top] = a + b;
                break;
            case '-':
                stack[++top] = a - b;
                break;
            case '*':
                stack[++top] = a * b;
                break;
            case '/':
                if (b == 0) {
                    printf("Error: Invalid expression.\n");
                    system("pause");
                    exit(1);
                }
                stack[++top] = a / b;
                break;
            }
        }
        else {
            printf("Error: Invalid character.\n");
            system("pause");
            exit(1);
        }
    }

    if (top != 0) {
        printf("Error: Invalid expression.\n");
        system("pause");
        exit(1);
    }
    int result = stack[top];
    top = 0;
    return result;
}

int main() {
    char infix[MAX_STACK_SIZE];
    int i, j, k, len;

    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    len = strlen(infix);

    if (!Parentheses(infix)) {
        printf("Error: Mismatched parentheses.\n");
        system("pause");
        exit(1);
    }

    infix_to_postfix(len, infix);


    len = strlen(postfix);

    int result = eval(len);

    printf("Result: % d\n", result);

    return 0;
}