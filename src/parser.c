#include "include/parser.h"
#include <stdio.h>

parser_T* init_parser(lexer_T* lexer){
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->curr_token = lexer_get_token(lexer);
    return parser;
}

    //used to identify if the token as the token given, else throughs err
void parser_identify_token(parser_T* parser, int token_type){
    if (parser->curr_token->type == token_type)
        parser->curr_token = lexer_get_token(parser->lexer);
    else
        printf("ERROR: Unexpected token '%s', with type '%d'",parser->curr_token->val, parser->curr_token->type); exit(1);
}

AST_T* parser_parse(parser_T* parser){

}

AST_T* parser_parse_statement(parser_T* parser){
    switch(parser->curr_token->type){
        case token_id: parser_parse_variable(parser);
    }
}
    //runs through the file and creates a compounded statement list until an eol token is found
AST_T* parser_parse_multiple_statements(parser_T* parser){
    AST_T* statement_list = init_ast(ast_statement_list);
    statement_list->ast_statement_list_value = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* statement = parser_parse_statement(parser);
    statement_list->ast_statement_list_value[0] = statement;

    while(parser->curr_token->type == token_eol){
        parser_identify_token(parser, token_eol);

        AST_T* ast_statement = parser_parse_statement(parser);
        statement_list->ast_statement_list_size++;
        statement_list->ast_statement_list_value = realloc(statement_list->ast_statement_list_value, statement_list->ast_statement_list_size * sizeof(struct AST_STRUCT*));
        statement_list->ast_statement_list_value[statement_list->ast_statement_list_size - 1] = ast_statement;
    }
    return statement_list;
}

AST_T* parser_parse_expression(parser_T* parser){

}

AST_T* parser_parse_factor(parser_T* parser){

}

AST_T* parser_parse_term(parser_T* parser){

}

AST_T* parser_parse_func_call(parser_T* parser){

}

AST_T* parser_parse_variable_contents(parser_T* parser){
    char* variable_contents_name = parser->curr_token->val;
    parser_identify_token(parser, token_id);
    parser_identify_token(parser, token_equals);
    AST_T* variable_contents_value = parser_parse_expression(parser);

    AST_T* variable_contents = init_ast(ast_variable_contents);

    variable_contents->ast_variable_contents_name = variable_contents_name;
    variable_contents->ast_variable_contents_value = variable_contents_value;

    return variable_contents;
}

AST_T* parser_parse_variable(parser_T* parser){
    char* token_value = parser->curr_token->val;
    parser_identify_token(parser, token_id);
    if (parser->curr_token->type == token_leftbrack){
        return parser_parse_func_call(parser);
    }

    AST_T* variable = init_ast(ast_variable);
    variable->ast_variable_name = token_value;

    return variable;
}

AST_T* parser_parse_str(parser_T* parser){


}
