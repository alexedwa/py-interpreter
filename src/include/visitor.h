#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"
AST_T* visitor_visit(AST_T* node);

AST_T* visitor_visit_variable(AST_T* node);

AST_T* visitor_visit_variable_contents(AST_T* node);

AST_T* visitor_visit_func_call(AST_T* node);

AST_T* visitor_visit_str(AST_T* node);

AST_T* visitor_visit_statement_list(AST_T* node);
#endif
