#ifndef PARSER_H_
	#define PARSER_H_

	#include <environment.h>
	#include <list.h>
	#include <stdint.h>
	#include <stdio.h>

	#define TOKEN_COUNT 16

	extern execution_environment env;

	typedef struct {
		char *text;
		unsigned length, capacity;
	} text_builder;

	int is_symbol(char x);
	int is_whitespace(char x);
	void tokeniser(FILE *file, list *ls);
	void complete_symbol(FILE *file, text_builder *builder);

	void add_char(text_builder *builder, const char c);

	void read_string(FILE *file, text_builder *builder, const char quote);
	char read_char(FILE *file);

	char get_escape(FILE *file);
	int read_hex(FILE *src, uint8_t *dest, int digits);
#endif
