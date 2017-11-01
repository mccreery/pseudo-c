#ifndef ENVIRONMENT_H_
	#define ENVIRONMENT_H_

	#include <list.h>
	#include <util.h>
	#include <value.h>

	/** Contains all the data necessary to run a program */
	typedef struct {
		list variables;
		list functions;
	} execution_environment;

	typedef struct {
		char *name;
		expr_val value;
	} variable;

	typedef struct {
		char *name;
		int arg_count;
		expr_val *(*func)(list *args);
	} function;

	bool is_var(const char *name);
	bool is_func(const char *name);
	variable *get_var(const char *name);
	function *get_func(const char *name);

	void init_environment();
#endif
