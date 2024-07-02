#include "include/ast.h"
AST_T* init_ast(int type){
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;

    //ast_variable//
    ast->ast_variable_name = (void*)0;

    //ast_variable_contents//
    ast->ast_variable_contents_name = (void*)0;
    ast->ast_variable_contents_value = (void*)0;

    //ast_func_call//
    ast->ast_func_call_name = (void*)0;
    ast->ast_func_call_args = (void*)0;
    ast->ast_func_call_args_size = 0;

    //ast_str//
    ast->string_value = (void*)0;

    return ast;
}
