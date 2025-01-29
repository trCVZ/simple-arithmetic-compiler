#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTI,
    TOKEN_DIVI,
    TOKEN_END
} TokenType;

typedef struct {
    TokenType type;
    long value;
} Token;

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

    
    Token newTokens[256];
    int newPosition = 0;

    while (tokens[position].type != TOKEN_END) {
        if (tokens[position].type == TOKEN_MULTI || tokens[position].type == TOKEN_DIVI) {
            if (newPosition == 0) {
                return 0;
            }

            if (tokens[position].type == TOKEN_MULTI) {
                newTokens[newPosition - 1].value = newTokens[newPosition - 1].value * tokens[position + 1].value;
            } else if (tokens[position].type == TOKEN_DIVI) {
                if (tokens[position + 1].value == 0) {
                    printf("Error: Division by zero!\n");
                    return 0;
                }
                newTokens[newPosition - 1].value = newTokens[newPosition - 1].value / tokens[position + 1].value;
            }
            position += 2;
        } else {
            newTokens[newPosition] = tokens[position];
            position++;
            newPosition++;
        }
    }

    newTokens[newPosition].type = TOKEN_END;
    *result = newTokens[0].value;
    position = 1;

    while (newTokens[position].type != TOKEN_END) {
        if (newTokens[position].type == TOKEN_PLUS) {
            position++;
            if (newTokens[position].type != TOKEN_NUMBER) {
                return 0;
            }
            
            *result += newTokens[position].value;
        }
        else if (newTokens[position].type == TOKEN_MINUS) {
            position++;
            if (newTokens[position].type != TOKEN_NUMBER) {
                return 0;
            }
            *result -= newTokens[position].value;
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