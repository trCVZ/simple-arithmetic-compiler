#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <header.h>

void printTokens(Token* tokens) {
    int position = 0;
    while (tokens[position].type != TOKEN_END) {
        switch (tokens[position].type) {
        case TOKEN_NUMBER:
            printf("TOKEN_NUMBER: %ld\n", tokens[position].value);
            break;
        case TOKEN_PLUS:
            printf("TOKEN_PLUS\n");
            break;
        case TOKEN_MINUS:
            printf("TOKEN_MINUS\n");
            break;
        case TOKEN_MULTI:
            printf("TOKEN_MULTI\n");
            break;
        case TOKEN_DIVI:
            printf("TOKEN_DIVI\n");
            break;
        case TOKEN_OPEN_PAREN:
            printf("TOKEN_OPEN_PAREN\n");
            break;
        case TOKEN_CLOSED_PAREN:
            printf("TOKEN_CLOSED_PAREN\n");
            break;
        default:
            break;
        }
        position++;
    }
}

Token* tokenize(const char* input) {
    Token* tokens = malloc(256 * sizeof(Token));
    int position = 0;

    while (*input) {
        if (isdigit(*input)) {
            tokens[position].type = TOKEN_NUMBER;
            tokens[position].value = strtol(input, (char**)&input, 10);
            position++;
        }
        else if (*input == '+') {
            tokens[position].type = TOKEN_PLUS;
            input++;
            position++;
        }
        else if (*input == '-') {
            tokens[position].type = TOKEN_MINUS;
            input++;
            position++;
        }
        else if (*input == '*') {
            tokens[position].type = TOKEN_MULTI;
            input++;
            position++;
        }
        else if (*input == '/') {
            tokens[position].type = TOKEN_DIVI;
            input++;
            position++;
        }
        else if (*input == '(') {
            tokens[position].type = TOKEN_OPEN_PAREN;
            input++;
            position++;
        }
        else if (*input == ')') {
            tokens[position].type = TOKEN_CLOSED_PAREN;
            input++;
            position++;
        }
        else {
            input++;
        }
    }
    tokens[position].type = TOKEN_END;
    return tokens;
}

int parsePrimary(Token* tokens, int* position, long* result) {
    if (tokens[*position].type == TOKEN_NUMBER) {
        *result = tokens[*position].value;
        (*position)++;
        return 1;
    }
    else if (tokens[*position].type == TOKEN_OPEN_PAREN) {
        (*position)++;
        if (!parseExpression(tokens, position, result)) {
            return 0;
        }
        if (tokens[*position].type != TOKEN_CLOSED_PAREN) {
            return 0;
        }
        (*position)++;
        return 1;
    }
    return 0;
}

int parseTerm(Token* tokens, int* position, long* result) {
    if (!parsePrimary(tokens, position, result)) {
        return 0;
    }

    while (tokens[*position].type == TOKEN_MULTI || tokens[*position].type == TOKEN_DIVI) {
        TokenType op = tokens[*position].type;
        (*position)++;
        long rhs;
        if (!parsePrimary(tokens, position, &rhs)) {
            return 0;
        }
        if (op == TOKEN_MULTI) {
            *result *= rhs;
        }
        else if (op == TOKEN_DIVI) {
            if (rhs == 0) {
                printf("Error: Division by zero!\n");
                return 0;
            }
            *result /= rhs;
        }
    }
    return 1;
}

int parseExpression(Token* tokens, int* position, long* result) {
    if (!parseTerm(tokens, position, result)) {
        return 0;
    }

    while (tokens[*position].type == TOKEN_PLUS || tokens[*position].type == TOKEN_MINUS) {
        TokenType op = tokens[*position].type;
        (*position)++;
        long rhs;
        if (!parseTerm(tokens, position, &rhs)) {
            return 0;
        }
        if (op == TOKEN_PLUS) {
            *result += rhs;
        }
        else if (op == TOKEN_MINUS) {
            *result -= rhs;
        }
    }
    return 1;
}

void generateAssembly(Token* tokens) {
    int position = 0;
    printf("Assembly-like Instructions :\n");
    if (tokens[position].type == TOKEN_NUMBER) {
        printf("LOAD %ld\n", tokens[position].value);
        position++;
    }

    while (tokens[position].type != TOKEN_END) {
        if (tokens[position].type == TOKEN_PLUS) {
            position++;
            if (tokens[position].type == TOKEN_NUMBER) {
                printf("ADD %ld\n", tokens[position].value);
            }
        }
        else if (tokens[position].type == TOKEN_MINUS) {
            position++;
            if (tokens[position].type == TOKEN_NUMBER) {
                printf("SUB %ld\n", tokens[position].value);
            }
        }
        position++;
    }
}

int main() {
    char input[256];
    printf("Enter an arithmetic expression: ");
    fgets(input, sizeof(input), stdin);

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    Token* tokens = tokenize(input);
    long result;
    int position = 0;
    if (parseExpression(tokens, &position, &result) && tokens[position].type == TOKEN_END) {
        printf("Result: %ld\n", result);
        generateAssembly(tokens);
    }
    else {
        printf("Invalid expression\n");
    }

    free(tokens);
    return 0;
}
