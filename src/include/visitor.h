#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"
typedef struct VISITOR_STRUCT{
    AST_T** visitor_variable_contents;
    size_t visitor_variable_contents_size;
}visitor_T;

visitor_T* init_visitor();

AST_T* visitor_visit(AST_T* node, visitor_T* visitor);

AST_T* visitor_visit_variable(AST_T* node, visitor_T* visitor);

AST_T* visitor_visit_variable_contents(AST_T* node, visitor_T* visitor);

AST_T* visitor_visit_func_call(AST_T* node, visitor_T* visitor);

AST_T* visitor_visit_str(AST_T* node, visitor_T* visitor);

AST_T* visitor_visit_statement_list(AST_T* node, visitor_T* visitor);

// BUILTIN FUNCTIONS //

static AST_T* builtin_func_print(AST_T** args, int arg_size, visitor_T* visitor);
#endif
