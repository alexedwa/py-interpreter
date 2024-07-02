#include "include/parser.h"
#include <stdio.h>

parser_T* init_parser(lexer_T* lexer){
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->curr_token = lexer_get_token(lexer);
    return parser;
}

void parser_identify_token(parser_T* parser, int token_type){
    if (parser->curr_token->type == token_type)
        parser->curr_token = lexer_get_token(parser->lexer);
    else
        printf("ERROR: Unexpected token '%s', with type '%d'",parser->curr_token->val, parser->curr_token->type); exit(1);
}

AST_T* parser_parse(parser_T* parser){

}

AST_T* parser_parse_statement(parser_T* parser){

}

AST_T* parser_parse_multiple_statements(parser_T* parser){

}

AST_T* parser_parse_expression(parser_T* parser){

}

AST_T* parser_parse_factor(parser_T* parser){

}

AST_T* parser_parse_term(parser_T* parser){

}

AST_T* parser_parse_func_call(parser_T* parser){

}

AST_T* parser_parse_variable(parser_T* parser){

}

AST_T* parser_parse_str(parser_T* parser){

}
