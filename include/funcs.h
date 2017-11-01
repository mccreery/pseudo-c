#ifndef FUNCS_H_
	#define FUNCS_H_

	#include <environment.h>
	#include <list.h>

	typedef struct {
		char *name;
		int type;
	} declare_variable_a;

	typedef struct {
		char *name;
		list *expr;
	} set_variable_a;

	typedef struct {
		list *cond_expr;
		list *block;
	} while_loop_a;

	variable *get_variable(const char *name);
	void fill_value(char *str, void **value, int type);
	void set_variable(void *data);
	void declare_variable(void *data);
	void while_loop(void *data);
	void if_block(void *data);
	void eval_expr(void *data);

	#define INIT_ARGS(x) x args = *((x*)data)
	#define CREATE_ARGS(x) x *args = malloc(sizeof(x))
#endif
