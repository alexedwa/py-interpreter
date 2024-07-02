#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct LEXER_STRUCT{
    char c;
    unsigned int i;
    char* text;
} lexer_T;

lexer_T* init_lexer(char* text);

void lexer_cont(lexer_T* lexer);

void lexer_whitespace(lexer_T* lexer);

token_T* lexer_get_token(lexer_T* lexer);

token_T* lexer_get_id(lexer_T* lexer);

token_T* lexer_get_string(lexer_T* lexer);

token_T* lexer_cont_with_token(lexer_T* lexer, token_T* token);

char* lexer_get_char_as_str(lexer_T* lexer);
#endif
