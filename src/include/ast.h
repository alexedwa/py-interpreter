#ifndef AST_H
#define AST_H
#include <stdlib.h>
typedef struct AST_STRUCT{
    enum{
        ast_variable,
        ast_variable_contents,
        ast_func_call,
        ast_str
    } type;
    //ast_variable//
    char* ast_variable_name;

    //ast_variable_contents//
    char* ast_variable_contents_name;
    struct AST_STRUCT* ast_variable_contents_value;

    //ast_func_call//
    char* ast_func_call_name;
    struct AST_STRUCT* ast_func_call_args;
    size_t ast_func_call_args_size;

    //ast_str//
    char* string_value;

} AST_Type;

AST_Type* init_ast(int type);
#endif
