#include "include/parser.h"
#include <stdio.h>

parser_T* init_parser(lexer_T* lexer){
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->curr_token = lexer_get_token(lexer);
    parser->prev_token = parser->curr_token;

    return parser;
}

    //used to identify if the token as the token given, else throws err
void parser_identify_token(parser_T* parser, int token_type){
    if (parser->curr_token->type == token_type){
        parser->prev_token = parser->curr_token;
        parser->curr_token = lexer_get_token(parser->lexer);
    }
    else{
        printf("ERROR: Unexpected token '%s', with type '%d'",parser->curr_token->val, parser->curr_token->type);
        exit(1);
    }
}

AST_T* parser_parse(parser_T* parser){
    char** var_arr = calloc(1, sizeof(char*));
    int arr_size = 0;
    return parser_parse_multiple_statements(parser, var_arr, arr_size);
}

AST_T* parser_parse_statement(parser_T* parser, char** var_arr, int arr_size){
    switch(parser->curr_token->type){
        case token_id: return parser_parse_id(parser, var_arr, arr_size); break;
    }

    return init_ast(ast_end_of_operations);
}
    //runs through the file and creates a compounded statement list until an eol token is found
AST_T* parser_parse_multiple_statements(parser_T* parser, char** var_arr, int arr_size){
    AST_T* statement_list = init_ast(ast_statement_list);
    statement_list->ast_statement_list_value = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* statement = parser_parse_statement(parser, var_arr, arr_size);
    statement_list->ast_statement_list_value[0] = statement;
    statement_list->ast_statement_list_size++;

    while(parser->curr_token->type == token_eol){
        parser_identify_token(parser, token_eol);

        AST_T* ast_statement = parser_parse_statement(parser, var_arr, arr_size);
        if (ast_statement){
            statement_list->ast_statement_list_size++;
            statement_list->ast_statement_list_value = realloc(statement_list->ast_statement_list_value, statement_list->ast_statement_list_size * sizeof(struct AST_STRUCT*));
            statement_list->ast_statement_list_value[statement_list->ast_statement_list_size - 1] = ast_statement;
        }
    }

    return statement_list;
}

AST_T* parser_parse_expression(parser_T* parser, char** var_arr, int arr_size){
    switch (parser->curr_token->type){
        case token_string: return parser_parse_str(parser, var_arr, arr_size);
        case token_id: return parser_parse_id(parser, var_arr, arr_size);
    }

    return init_ast(ast_end_of_operations);
}

AST_T* parser_parse_func_call(parser_T* parser, char** var_arr, int arr_size){
    AST_T* func_call = init_ast(ast_func_call);
    func_call->ast_func_call_args = calloc(1, sizeof(struct AST_STRUCT*));

    func_call->ast_func_call_name = parser->prev_token->val;

    parser_identify_token(parser, token_leftbrack);


    AST_T* expressions = parser_parse_statement(parser, var_arr, arr_size);


    func_call->ast_func_call_args[0] = expressions;

    func_call->ast_func_call_args_size++;

    while(parser->curr_token->type == token_comma){

        parser_identify_token(parser, token_comma);

        AST_T* expressions = parser_parse_statement(parser, var_arr, arr_size);
        func_call->ast_func_call_args_size++;
        func_call->ast_func_call_args = realloc(func_call->ast_func_call_args, func_call->ast_func_call_args_size * sizeof(struct AST_STRUCT*));
        func_call->ast_func_call_args[func_call->ast_func_call_args_size - 1] = expressions;
    }
    parser_identify_token(parser, token_rightbrack);
    return func_call;
}

AST_T* parser_parse_variable_contents(parser_T* parser, char** var_arr, int arr_size){

    char* variable_contents_name = parser->prev_token->val;
    parser_identify_token(parser, token_equals);
    AST_T* variable_contents_value = parser_parse_expression(parser, var_arr, arr_size);

    AST_T* variable_contents = init_ast(ast_variable_contents);

    variable_contents->ast_variable_contents_name = variable_contents_name;
    variable_contents->ast_variable_contents_value = variable_contents_value;

    return variable_contents;
}

AST_T* parser_parse_variable(parser_T* parser, char** var_arr, int arr_size){
    char* token_value = parser->curr_token->val;
    parser_identify_token(parser, token_id);

    if (parser->curr_token->type == token_leftbrack){
        return parser_parse_func_call(parser, var_arr, arr_size);
    }

    AST_T* variable = init_ast(ast_variable);
    variable->ast_variable_name = token_value;

    return variable;
}

AST_T* parser_parse_str(parser_T* parser, char** var_arr, int arr_size){
    AST_T* string = init_ast(ast_str);
    string->ast_string_value = parser->curr_token->val;

    parser_identify_token(parser, token_string);

    return string;
}

AST_T* parser_parse_id(parser_T* parser, char** var_arr, int arr_size){
    parser_T* prev_parser = parser;
    if (parser->curr_token->type == token_id)
        parser_identify_token(parser, token_id);

    if (parser->curr_token->type == token_leftbrack){   //identified a function call
        return parser_parse_func_call(parser, var_arr, arr_size);

    }

    else if (parser->curr_token->type == token_equals){
        if (parser_check_variable_array(prev_parser, var_arr, arr_size) == 1){
            return parser_parse_variable(prev_parser, var_arr, arr_size);
        }
        else{
            parser_append_variable_array(prev_parser, var_arr, arr_size);
            return parser_parse_variable_contents(prev_parser, var_arr, arr_size);
        }
    }

    else if (parser->curr_token->type != token_rightbrack){
        return parser_parse_variable(prev_parser, var_arr, arr_size);
    }

    return init_ast(ast_end_of_operations);
}

int parser_check_variable_array(parser_T* parser, char** var_arr, int arr_size){
    for(int i = 0; i < arr_size; ++i){
        printf("%s\n", parser->curr_token->val);
        if (parser->curr_token->val == var_arr[i]) return 1;
    }
    return 0;
}

void parser_append_variable_array(parser_T* parser, char** var_arr, int arr_size){
    arr_size++;
    var_arr = realloc(var_arr, arr_size * sizeof(char*));
}
