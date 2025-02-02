#ifndef HEADER_H
#define HEADER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTI,
    TOKEN_DIVI,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSED_PAREN,
    TOKEN_END
} TokenType;

typedef struct {
    TokenType type;
    long value;
} Token;

void printTokens(Token* tokens);
Token* tokenize(const char* input);
int parseExpression(Token* tokens, int* position, long* result);
int parsePrimary(Token* tokens, int* position, long* result);
int parseTerm(Token* tokens, int* position, long* result);
void generateAssembly(Token* tokens);

#endif // HEADER_H