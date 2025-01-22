#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_END
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

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
        else {
            input++;
        }
    }
    tokens[position].type = TOKEN_END;
    return tokens;
}

int parse(Token* tokens, long* result) {
    int position = 0;
    if (tokens[position].type != TOKEN_NUMBER) {
        return 0;
    }

    *result = tokens[position].value;
    position++;

    while (tokens[position].type != TOKEN_END) {
        if (tokens[position].type == TOKEN_PLUS) {
            position++;
            if (tokens[position].type != TOKEN_NUMBER) {
                return 0;
            }
            *result += tokens[position].value;
        }
        else if (tokens[position].type == TOKEN_MINUS) {
            position++;
            if (tokens[position].type != TOKEN_NUMBER) {
                return 0;
            }
            *result -= tokens[position].value;
        }
        position++;
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
            if (tokens[position].type == TOKEN_MINUS) {
                printf("ADD %ld\n", tokens[position].value);
            }
        }
        else if (tokens[position].type == TOKEN_MINUS) {
            position++;
            if (tokens[position].type == TOKEN_NUMBER) {
                if (tokens[position].type == TOKEN_NUMBER) {
                    printf("SUB %ld\n", tokens[position].value);
                }
            }
        }
        position++;
    }
}

int main() {
    char input[256];
    printf("Enter an arithmetic :");
    fgets(input, sizeof(input), stdin);

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    Token* tokens = tokenize(input);
    long result;
    if (parse(tokens, &result)) {
        printf("Result : %ld\n", result);
        generateAssembly(tokens);
    }
    else {
        printf("Invalid expression");
    }

    free(tokens);
    return 0;
}