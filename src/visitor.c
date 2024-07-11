#include "include/visitor.h"
#include <stdio.h>
#include <string.h>


visitor_T* init_visitor()
{
    visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
    visitor->visitor_variable_contents = (void*) 0;
    visitor->visitor_variable_contents_size = 0;

    return visitor;
}

AST_T* visitor_visit(AST_T* node, visitor_T* visitor)
{
    switch (node->type)
    {
        case ast_variable_contents: return visitor_visit_variable_contents(node, visitor); break;
        case ast_variable: return visitor_visit_variable(node, visitor); break;
        case ast_func_call: return visitor_visit_func_call(node, visitor); break;
        case ast_str: return visitor_visit_str(node, visitor); break;
        case ast_statement_list: return visitor_visit_statement_list(node, visitor); break;
        case ast_end_of_operations: return node; break;
    }

    printf("Uncaught statement of type `%d`\n", node->type);
    exit(1);

    return init_ast(ast_end_of_operations);
}

AST_T* visitor_visit_variable_contents(AST_T* node, visitor_T* visitor)
{
    if (visitor->visitor_variable_contents == (void*) 0)
    {
        visitor->visitor_variable_contents = calloc(1, sizeof(struct AST_STRUCT*));
        visitor->visitor_variable_contents[0] = node;
        visitor->visitor_variable_contents_size += 1;
    }
    else
    {
        visitor->visitor_variable_contents_size += 1;
        visitor->visitor_variable_contents = realloc(visitor->visitor_variable_contents, visitor->visitor_variable_contents_size * sizeof(struct AST_STRUCT*)
        );
        visitor->visitor_variable_contents[visitor->visitor_variable_contents_size-1] = node;
    }

    return node;
}

AST_T* visitor_visit_variable(AST_T* node, visitor_T* visitor)
{
    for (int i = 0; i < visitor->visitor_variable_contents_size; i++)
    {
        AST_T* vardef = visitor->visitor_variable_contents[i];

        if (strcmp(vardef->ast_variable_contents_name, node->ast_variable_name) == 0)
        {
            return visitor_visit(vardef->ast_variable_contents_value, visitor);
        }
    }

    printf("Undefined variable `%s\n`", node->ast_variable_name);
    return node;
}

AST_T* visitor_visit_func_call(AST_T* node, visitor_T* visitor)
{
    if (strcmp(node->ast_func_call_name, "print") == 0)
    {
        return builtin_func_print(node->ast_func_call_args, node->ast_func_call_args_size, visitor);
    }

    printf("Undefined method `%s`\n", node->ast_func_call_name);
    exit(1);
}

AST_T* visitor_visit_str(AST_T* node, visitor_T* visitor)
{
    return node;
}

AST_T* visitor_visit_statement_list(AST_T* node, visitor_T* visitor)
{
    for (int i = 0; i < node->ast_statement_list_size; i++)
    {
        visitor_visit(node->ast_statement_list_value[i], visitor);
    }

    return init_ast(ast_end_of_operations);
}

// builtin functions //

static AST_T* builtin_func_print(AST_T** args, int args_size, visitor_T* visitor)
{
    for (int i = 0; i < args_size; i++)
    {
        args = calloc(1, sizeof(struct AST_STRUCT**));
        printf("%d\n", args[i]->type);
        AST_T* visited_ast = visitor_visit(args[i], visitor);

        switch (visited_ast->type)
        {
            case ast_str: printf("%s\n", visited_ast->ast_string_value); break;
            default: printf("%p\n", visited_ast); break;
        }
    }

    return init_ast(ast_end_of_operations);
}
