#include "include/token.h"
#include <stdlib.h>

token_Type* init_token(int type, char* val){
    token_Type* token = calloc(1, sizeof(struct TOKEN_STRUCT));

    token->type = type;
    token->val = val;

    return token;
}
