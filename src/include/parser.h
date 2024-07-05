#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "ast.h"
typedef struct PARSER_STRUCT{
    lexer_T* lexer;
    token_T* curr_token;
}parser_T;

parser_T* init_parser(lexer_T* lexer);

void parser_identify_token(parser_T* parser, int token_type);

AST_T* parser_parse(parser_T* parser);

AST_T* parser_parse_statement(parser_T* parser);

AST_T* parser_parse_multiple_statements(parser_T* parser);

AST_T* parser_parse_expression(parser_T* parser);

AST_T* parser_parse_func_call(parser_T* parser);

AST_T* parser_parse_variable(parser_T* parser);

AST_T* parser_parse_variable_contents(parser_T* parser);

AST_T* parser_parse_str(parser_T* parser);

AST_T* parser_parse_id(parser_T* parser);

int parser_check_variable_array(parser_T* parser);

void parser_append_variable_array(parser_T* parser);
#endif
