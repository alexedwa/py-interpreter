#ifndef AST_H
#define AST_H
#include <stdlib.h>
typedef struct AST_STRUCT{
    enum{
        ast_variable,
        ast_variable_contents,
        ast_func_call,
        ast_str,
        ast_statement_list
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
    char* ast_string_value;

    //ast_statement_list//
    struct AST_STRUCT** ast_statement_list_value;
    size_t ast_statement_list_size;

} AST_T;

AST_T* init_ast(int type);
#endif
