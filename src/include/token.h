#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT{
    enum{
        token_id,
        token_equals,
        token_string,
        token_leftbrack,
        token_rightbrack,
        token_eof
    }type;

    char* val;
} token_T;

token_T* init_token(int type, char* val);

#endif
