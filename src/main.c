#include <stdio.h>
#include <string.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"

int main(int argc, char* argv[]){
	if (argc < 2){
		printf("Write: ./py-interpreter.out <filename>\n");
		exit(1);
	}
	else{
		lexer_T* lexer = init_lexer(get_file_contents(argv[1]));
		parser_T* parser = init_parser(lexer);
		AST_T* root = parser_parse(parser);
		visitor_T* visitor = init_visitor();
		visitor_visit(root, visitor);
	}
	return 0;
}

// example_files/testfile1.py
