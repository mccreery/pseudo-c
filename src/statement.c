#include <environment.h>
#include <expression.h>
#include <funcs.h>
#include <statement.h>
#include <stdlib.h>
#include <string.h>

/** Builds a declare variable statement */
void build_declare(statement *s, char * const name, const int type);
/** Builds an if statement with empty condition and block */
void build_if(statement *s);
/** Builds a while loop statement with an empty condition and block */
void build_while(statement *s);
int build_block(list *ls, int i, list *block);

int build_statement(list *ls, int i, list *statements) {
	int type_index;

	if((type_index = find_in_arr(types, 10, ls->items[i])) != -1) {
		statement *s = malloc(sizeof(statement));
		build_declare(s, ls->items[++i], type_index);
		list_add(statements, s);

		char *next_token = ls->items[++i];
		if(strcmp(next_token, "=") == 0) {
			i = build_statement(ls, i - 1, statements);
		} else if(strcmp(next_token, ";") != 0) {
			error("No terminator following declaration");
		}
	} else if(strcmp(ls->items[i], "while") == 0) {
		statement *s = malloc(sizeof(statement));
		build_while(s);

		if(strcmp(ls->items[++i], "(") != 0) error("Loop keyword must be followed by a set of brackets");
		i = build_expr_(ls, ++i, ((while_loop_a *)s->data)->cond_expr, ")");

		i = build_block(ls, i, ((while_loop_a *)s->data)->block);
		list_add(statements, s);
	} else if(strcmp(ls->items[i], "for") == 0) {
		if(strcmp(ls->items[++i], "(") != 0) error("Loop keyword must be followed by a set of brackets");
		i = build_statement(ls, ++i, statements);

		statement *s = malloc(sizeof(statement));
		build_while(s);
		i = build_expr(ls, ++i, ((while_loop_a *)s->data)->cond_expr);
		i = build_statement(ls, ++i, ((while_loop_a *)s->data)->block);
		statement *temp = list_pop(((while_loop_a *)s->data)->block);

		if(strcmp(ls->items[++i], ")") != 0) error("Must close )");
		i = build_block(ls, i, ((while_loop_a *)s->data)->block);
		list_add(((while_loop_a *)s->data)->block, temp);

		list_add(statements, s);
	} else if(strcmp(ls->items[i], "if") == 0) {
		statement *s = malloc(sizeof(statement));
		build_if(s);

		if(strcmp(ls->items[++i], "(") != 0) error("If keyword must be followed by a set of brackets");
		i = build_expr_(ls, ++i, ((while_loop_a *)s->data)->cond_expr, ")");

		i = build_block(ls, i, ((while_loop_a *)s->data)->block);
		list_add(statements, s);
	} else if(is_name(ls->items[i])) {
		if(is_func(ls->items[i])) {
			statement *s = malloc(sizeof(statement));
			s->func = eval_expr;
			CREATE_ARGS(list);
			init_list(args);
			i = build_expr(ls, i, args);
			s->data = args;
			list_add(statements, s);
		} else {
			statement *s = malloc(sizeof(statement));
			s->func = set_variable;

			CREATE_ARGS(set_variable_a);
			args->name = (char *)ls->items[i];
			if(strcmp(ls->items[++i], "=") != 0) {
				error("Variable name must be followed by equals");
			}
			args->expr = malloc(sizeof(list));
			init_list(args->expr);
			i = build_expr(ls, ++i, args->expr);

			s->data = args;
			list_add(statements, s);
		}
	}
	return i;
}

void statement_builder(list *ls, list *statements) {
	for(int i = 0; i < ls->count; i++) {
		i = build_statement(ls, i, statements);
	}
}

void build_declare(statement *s, char * const name, const int type) {
	if(!is_name(name)) error("Invalid variable name");
	s->func = declare_variable;

	declare_variable_a *args = malloc(sizeof(declare_variable_a));
	args->name = name;
	args->type = type;

	s->data = args;
}
void build_while(statement *s) {
	s->func = while_loop;

	while_loop_a *args = malloc(sizeof(while_loop_a));
	args->cond_expr = malloc(sizeof(list));
	init_list(args->cond_expr);
	args->block = malloc(sizeof(list));
	init_list(args->block);

	s->data = args;
}
void build_if(statement *s) {
	s->func = if_block;

	while_loop_a *args = malloc(sizeof(while_loop_a));
	args->cond_expr = malloc(sizeof(list));
	init_list(args->cond_expr);
	args->block = malloc(sizeof(list));
	init_list(args->block);

	s->data = args;
}
int build_block(list *ls, int i, list *block) {
	if(strcmp(ls->items[++i], "{") == 0) {
		while(strcmp(ls->items[++i], "}") != 0) {
			i = build_statement(ls, i, block);
		}
	} else if(strcmp(ls->items[i], ";") != 0) {
		error("Loop must either open a block or end with a terminator");
	}
	return i;
}
