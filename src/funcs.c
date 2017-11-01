#include <expression.h>
#include <funcs.h>
#include <parser.h>
#include <statement.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <value.h>

variable *get_variable(const char *name) {
	int i;
	for(i = 0; i < env.variables.count; i++) {
		if(strcmp(env.variables.items[i], name) == 0) {
			return (variable *)env.variables.items[i];
		}
	}
	return NULL;
}

void fill_value(char *str, void **value, int type) {
	union {
		uint64_t i;
		int64_t  u;
		double   f;
	} _val;

	if(type < UINT8) {
		_val.i = parse_int(str);
	} else if(type < FLOAT32) {
		_val.u = parse_int(str);
	} else {
		_val.f = parse_float(str);
	}
	*value = (uint64_t *)&_val;
}

void declare_variable(void *data) {
	INIT_ARGS(declare_variable_a);
	variable *var = malloc(sizeof(variable));
	var->name = args.name;
	var->value.type = args.type;
	if(args.type <= UINT64) {
		var->value.value.int64 = 0;
	} else {
		var->value.value.float64 = 0.0;
	}
	list_add(&(env.variables), var);
}

void set_variable(void *data) {
	INIT_ARGS(set_variable_a);
	if(!is_var(args.name)) error("Variable resolution error, not found");

	variable *x = get_var(args.name);

	expr_val *val = evaluate(args.expr);
	convert(val, x->value.type);
	x->value.value = val->value;
	fflush(stdout);
}

void while_loop(void *data) {
	INIT_ARGS(while_loop_a);
	expr_val *cond;

	while(true) {
		cond = evaluate(args.cond_expr);
		if(!is_truthy(cond)) break;
		free(cond);

		for(int i = 0; i < args.block->count; i++) {
			statement *s = args.block->items[i];
			s->func(s->data);
		}
	}
	free(cond);
}

void if_block(void *data) {
	INIT_ARGS(while_loop_a);
	expr_val *cond;

	cond = evaluate(args.cond_expr);
	if(is_truthy(cond)) {
		for(int i = 0; i < args.block->count; i++) {
			statement *s = args.block->items[i];
			s->func(s->data);
		}
	}
	free(cond);
}

void eval_expr(void *data) {
	INIT_ARGS(list);
	evaluate(&args);
}
