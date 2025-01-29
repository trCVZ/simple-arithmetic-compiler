#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
<<<<<<< HEAD
    TOKEN_MULTI,
=======
    TOKEN_MULT,
>>>>>>> 60bd61883ef4931a000c671408f15d8823315780
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
<<<<<<< HEAD
            tokens[position].type = TOKEN_MULTI;
=======
            tokens[position].type = TOKEN_MULT;
>>>>>>> 60bd61883ef4931a000c671408f15d8823315780
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

Token* simplifiedTokens(Token* tokens, int* position) {
    int newPosition = 0;
    Token* newTokens = malloc(256 * sizeof(Token));

    while (tokens[*position].type != TOKEN_END) {
        if (tokens[*position].type == TOKEN_DIVI && tokens[*position+1].value != 0) {
            newTokens[newPosition].value = tokens[*position-1].value / tokens[*position+1].value;
            *position += 2;
        }
        else if (tokens[*position].type == TOKEN_MULT) {
            newTokens[newPosition].value = tokens[*position-1].value * tokens[*position+1].value;
            *position += 2;
        }
        else {
            newTokens[newPosition] = tokens[*position];
            newPosition++;
            (*position)++;
        }
    }

    newTokens[newPosition].type = TOKEN_END;
    *position = newPosition;
    return newTokens;
}

int parse(Token* tokens, long* result) {
    int position = 0;
    if (tokens[position].type != TOKEN_NUMBER) {
        return 0;
    }

<<<<<<< HEAD
    
    Token newTokens[256];
    int newPosition = 0;
=======
    position++;
>>>>>>> 60bd61883ef4931a000c671408f15d8823315780

    // Simplified
    Token* newTokens = malloc(256 * sizeof(Token));
    int newPosition = 0;
    while (tokens[position].type != TOKEN_END) {
<<<<<<< HEAD
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

=======
        if (tokens[position].type == TOKEN_DIVI && tokens[position + 1].type != TOKEN_NUMBER) {
            newTokens[newPosition].value = tokens[position-1].value / tokens[position+1].value;
            newTokens[newPosition].type = TOKEN_NUMBER;
            position+=2;
            newPosition++;
        } else if (tokens[position].type == TOKEN_MULT && tokens[position + 1].type != TOKEN_NUMBER) {
            newTokens[newPosition].value = tokens[position-1].value * tokens[position+1].value;
            newTokens[newPosition].type = TOKEN_NUMBER;
            position+=2;
            newPosition++;
        } else {
            newTokens[newPosition].type = tokens[position].type;
            newTokens[newPosition].value = tokens[position].value;
            newPosition++;
            position++;
        }
    }
    newTokens[newPosition].type = TOKEN_END;

    position = 0;
    *result = newTokens[position].value;

    position++;
    
    // Addition & subtraction
>>>>>>> 60bd61883ef4931a000c671408f15d8823315780
    while (newTokens[position].type != TOKEN_END) {
        if (newTokens[position].type == TOKEN_PLUS) {
            position++;
            if (newTokens[position].type != TOKEN_NUMBER) {
                return 0;
            }
<<<<<<< HEAD
            
=======
>>>>>>> 60bd61883ef4931a000c671408f15d8823315780
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
    free(newTokens);
    return 1;
}


void generateAssembly(Token* tokens) {
    int position = 0;
    printf("Assembly-like Instructions :\n");
    if (tokens[position].type == TOKEN_NUMBER) {
        printf("LOAD %d\n", tokens[position].value);
        position++;
    }

    while (tokens[position].type != TOKEN_END) {
        if (tokens[position].type == TOKEN_PLUS) {
            position++;
            if (tokens[position].type == TOKEN_NUMBER) {
                printf("ADD %d\n", tokens[position].value);
            }
        }
        else if (tokens[position].type == TOKEN_MINUS) {
            position++;
            if (tokens[position].type == TOKEN_NUMBER) {
                printf("SUB %d\n", tokens[position].value);
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
    if (parse(tokens, &result)) {
        printf("Result: %ld\n", result);
        generateAssembly(tokens);
    }
    else {
        printf("Invalid expression\n");
    }

    free(tokens);
    return 0;
}
