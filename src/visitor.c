#include <stdio.h>
#include "include/visitor.h"

AST_T* visitor_visit(AST_T* node){
    switch (node->type){
        case ast_variable: return visitor_visit_variable(node); break;
        case ast_variable_contents: return visitor_visit_variable_contents(node); break;
        case ast_func_call: return visitor_visit_func_call(node); break;
        case ast_str: return visitor_visit_str(node); break;
        case ast_statement_list: return visitor_visit_statement_list(node); break;
        case ast_end_of_operations: return node; break;
    }
    printf("Unexpected statement type of %d \n", node->type);
    exit(1);

}

AST_T* visitor_visit_variable(AST_T* node){

}

AST_T* visitor_visit_variable_contents(AST_T* node){

}

AST_T* visitor_visit_func_call(AST_T* node){

}

AST_T* visitor_visit_str(AST_T* node){

}

AST_T* visitor_visit_statement_list(AST_T* node){
    for (int i = 0; i < node->ast_statement_list_size; ++i){
        visitor_visit(node->ast_statement_list_value[i]);
    }
    return init_ast(ast_end_of_operations);
}
