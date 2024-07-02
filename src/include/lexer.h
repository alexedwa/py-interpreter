#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct LEXER_STRUCT{
    char c;
    unsigned int i;
    char* text;
} lexer_Type;

lexer_Type* init_lexer(char* text);

void lexer_cont(lexer_Type* lexer);

void lexer_whitespace(lexer_Type* lexer);

token_Type* lexer_get_token(lexer_Type* lexer);

token_Type* lexer_get_id(lexer_Type* lexer);

token_Type* lexer_get_string(lexer_Type* lexer);

token_Type* lexer_cont_with_token(lexer_Type* lexer, token_Type* token);

char* lexer_get_char_as_str(lexer_Type* lexer);
#endif
