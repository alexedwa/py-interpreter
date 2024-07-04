#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

lexer_T* init_lexer(char* text){
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->text = text;
    lexer->i = 0;
    lexer->c = text[lexer->i];

    return lexer;
}


void lexer_cont(lexer_T* lexer){
    if (lexer->c != '\0' && lexer->i < strlen(lexer->text)){
        lexer->i++;
        lexer->c = lexer->text[lexer->i];
    }
}

void lexer_whitespace(lexer_T* lexer){
    while(lexer->c == ' ' || lexer->c == 10){
        lexer_cont(lexer);
    }
}

token_T* lexer_get_token(lexer_T* lexer){
    while (lexer->c != '\0' && lexer->i < strlen(lexer->text)){
        if (lexer->c == ' '){
            lexer_whitespace(lexer);
        }

        if (lexer->c == '"'){
            return lexer_get_string(lexer);
        }

        if (isalnum(lexer->c)){
            return lexer_get_id(lexer);
        }

        switch(lexer->c){
            case '=': return lexer_cont_with_token(lexer, init_token(token_equals, lexer_get_char_as_str(lexer))); break;
            case '(': return lexer_cont_with_token(lexer, init_token(token_leftbrack, lexer_get_char_as_str(lexer))); break;
            case ')': return lexer_cont_with_token(lexer, init_token(token_rightbrack, lexer_get_char_as_str(lexer))); break;
            case 10: return lexer_cont_with_token(lexer, init_token(token_eol, lexer_get_char_as_str(lexer))); break;

        }
    }
    return 0;
}

token_T* lexer_get_id(lexer_T* lexer){
    char* val = calloc(1, sizeof(char));
    val[0] = '\0';

    while(isalnum(lexer->c)){
        char* string = lexer_get_char_as_str(lexer);
        val = realloc(val, (strlen(val) + strlen(string) + 1) * sizeof(char));
        strcat(val, string);
        lexer_cont(lexer);
    }

    return init_token(token_id, val);
}

token_T* lexer_get_string(lexer_T* lexer){
    lexer_cont(lexer);

    char* val = calloc(1, sizeof(char));
    val[0] = '\0';

    while(lexer->c != '"'){
        char* string = lexer_get_char_as_str(lexer);
        val = realloc(val, (strlen(val) + strlen(string) + 1) * sizeof(char));
        strcat(val, string);
        lexer_cont(lexer);
    }

    lexer_cont(lexer);

    return init_token(token_string, val);
}

token_T* lexer_cont_with_token(lexer_T* lexer, token_T* token){
    lexer_cont(lexer);
    return token;
}

char* lexer_get_char_as_str(lexer_T* lexer){
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';
    return str;
}
