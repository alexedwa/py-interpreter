#include "include/parser.h"
#include <stdio.h>

char *variable_array[100];
int array_size = 0;

parser_T* init_parser(lexer_T* lexer){
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->curr_token = lexer_get_token(lexer);
    return parser;
}

    //used to identify if the token as the token given, else throws err
void parser_identify_token(parser_T* parser, int token_type){
    if (parser->curr_token->type == token_type)
        parser->curr_token = lexer_get_token(parser->lexer);
    else
        printf("ERROR: Unexpected token '%s', with type '%d'",parser->curr_token->val, parser->curr_token->type); exit(1);
}

AST_T* parser_parse(parser_T* parser){
    return parser_parse_multiple_statements(parser);
}

AST_T* parser_parse_statement(parser_T* parser){
    switch(parser->curr_token->type){
        case token_id: return parser_parse_id(parser);
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
    switch (parser->curr_token->type){
        case token_string: return parser_parse_str(parser);
    }
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
    AST_T* string = init_ast(ast_str);
    string->ast_string_value = parser->curr_token->val;

    parser_identify_token(parser, token_string);

    return string;
}

AST_T* parser_parse_id(parser_T* parser){
    parser_T* id_name = parser;
    if(parser->lexer->i + 1 == '='){        //checking for variable defining or returning
        if (parser_check_variable_array(parser) == 1){
            parser_parse_variable(parser);
        }
        else{
            parser_append_variable_array(parser);
            parser_parse_variable_contents(parser);
        }
    }

    else if(parser->lexer->i + 1 == '('){
        return parser_parse_func_call(parser);
    }
}

int parser_check_variable_array(parser_T* parser){
    int arr_size = sizeof(variable_array) / sizeof(variable_array[0]);
    for(int i = 0; i < arr_size; ++i){
        if (parser->curr_token->val == variable_array[i]) return 1;
    }
    return 0;
}

void parser_append_variable_array(parser_T* parser){
    variable_array[array_size] = parser->curr_token->val;
    array_size++;
}
