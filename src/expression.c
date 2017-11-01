#include <environment.h>
#include <expression.h>
#include <list.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <value.h>

int get_precedence(const char *operator) {
	if(strcmp(operator, "==") == 0 ||
			strcmp(operator, ">=") == 0 ||
			strcmp(operator, "<=") == 0 ||
			strcmp(operator, ">") == 0 ||
			strcmp(operator, "<") == 0 ||
			strcmp(operator, "!=") == 0) {
		return 0;
	} else if(strcmp(operator, "|") == 0) {
		return 1;
	} else if(strcmp(operator, "&") == 0) {
		return 2;
	} else if(strcmp(operator, "<<") == 0 ||
			strcmp(operator, ">>") == 0) {
		return 3;
	} else if(strcmp(operator, "+") == 0 ||
			strcmp(operator, "-") == 0) {
		return 4;
	} else if(strcmp(operator, "*") == 0 ||
			strcmp(operator, "/") == 0) {
		return 5;
	} else if(strcmp(operator, "^") == 0) {
		return 6;
	}
	return -1;
}
bool right_assoc(const char *operator) {
	return strcmp(operator, "^") == 0;
}

bool is_comparison(char *token) {
	return strcmp(token, "==") == 0 ||
		strcmp(token, ">=") == 0 ||
		strcmp(token, "<=") == 0 ||
		strcmp(token, ">") == 0 ||
		strcmp(token, "<") == 0 ||
		strcmp(token, "!=") == 0;
}

expr_val *evaluate(list *input) {
	list stack;
	init_list(&stack);

	for(int i = 0; i < input->count; i++) {
		if(((expr_val *)input->items[i])->type <= FLOAT64) {
			// Copy because we don't want to alter the original values
			expr_val *copy = malloc(sizeof(expr_val));
			memcpy(copy, input->items[i], sizeof(expr_val));
			list_add(&stack, copy);
		} else { // Token is string
			char *token = (char *)input->items[i];

			if(is_operator(token)) {
				expr_val *b = list_pop(&stack);
				expr_val *a = list_pop(&stack);

				promote(a, b);
				if(a->type != b->type)
					error("Unable to promote for calculation");

				expr_val *result = malloc(sizeof(expr_val));
				result->type = a->type;
				if(result->type <= UINT64) {
					if(a->type != INT64) {
						convert(a, INT64);
						convert(b, INT64);
					}

					int64_t temp;
					if(strcmp(token, "+") == 0) {
						temp = a->value.int64 + b->value.int64;
					} else if(strcmp(token, "-") == 0) {
						temp = a->value.int64 - b->value.int64;
					} else if(strcmp(token, "<<") == 0) {
						temp = a->value.int64 << b->value.int64;
					} else if(strcmp(token, ">>") == 0) {
						temp = a->value.int64 >> b->value.int64;
					} else if(strcmp(token, "/") == 0) {
						temp = a->value.int64 / b->value.int64;
					} else if(strcmp(token, "*") == 0) {
						temp = a->value.int64 * b->value.int64;
					} else if(strcmp(token, "^") == 0) {
						temp = pow(a->value.int64, b->value.int64);
					} else if(strcmp(token, "&") == 0) {
						temp = a->value.int64 & b->value.int64;
					} else if(strcmp(token, "|") == 0) {
						temp = a->value.int64 | b->value.int64;
					} else if(strcmp(token, "==") == 0) {
						temp = a->value.int64 == b->value.int64;
					} else if(strcmp(token, ">=") == 0) {
						temp = a->value.int64 >= b->value.int64;
					} else if(strcmp(token, "<=") == 0) {
						temp = a->value.int64 <= b->value.int64;
					} else if(strcmp(token, ">") == 0) {
						temp = a->value.int64 > b->value.int64;
					} else if(strcmp(token, "<") == 0) {
						temp = a->value.int64 < b->value.int64;
					} else if(strcmp(token, "!=") == 0) {
						temp = a->value.int64 != b->value.int64;
					}
					switch(result->type) {
						case INT8:   result->value.int8 = temp; break;
						case INT16:  result->value.int16 = temp; break;
						case INT32:  result->value.int32 = temp; break;
						case INT64:  result->value.int64 = temp; break;
						case UINT8:  result->value.int8 = temp; break;
						case UINT16: result->value.int16 = temp; break;
						case UINT32: result->value.int32 = temp; break;
						case UINT64: result->value.int64 = temp; break;
					}
				} else {
					if(a->type != FLOAT64) {
						convert(a, FLOAT64);
						convert(b, FLOAT64);
					}
					double temp;
					if(strcmp(token, "+") == 0) {
						temp = a->value.float64 + b->value.float64;
					} else if(strcmp(token, "-") == 0) {
						temp = a->value.float64 - b->value.float64;
					} else if(strcmp(token, "<<") == 0
							|| strcmp(token, ">>") == 0) {
						error("Unable to bitshift floating-point values");
					} else if(strcmp(token, "/") == 0) {
						temp = a->value.float64 / b->value.float64;
					} else if(strcmp(token, "*") == 0) {
						temp = a->value.float64 * b->value.float64;
					} else if(strcmp(token, "^") == 0) {
						temp = pow(a->value.float64, b->value.float64);
					} else if(strcmp(token, "&") == 0
							|| strcmp(token, "|") == 0) {
						error("Unable to perform bitwise operations on floating-point values");
					} else if(strcmp(token, "==") == 0) {
						temp = a->value.float64 == b->value.float64;
					} else if(strcmp(token, ">=") == 0) {
						temp = a->value.float64 >= b->value.float64;
					} else if(strcmp(token, "<=") == 0) {
						temp = a->value.float64 <= b->value.float64;
					} else if(strcmp(token, ">") == 0) {
						temp = a->value.float64 > b->value.float64;
					} else if(strcmp(token, "<") == 0) {
						temp = a->value.float64 < b->value.float64;
					} else if(strcmp(token, "!=") == 0) {
						temp = a->value.float64 != b->value.float64;
					}
					switch(result->type) {
						case FLOAT32: result->value.float32 = temp; break;
						case FLOAT64: result->value.float64 = temp; break;
					}
				}
				if(is_comparison(token)) {
					convert(result, INT32);
				}
				list_add(&stack, result);
			} else if(is_var(token)) {
				variable *var = get_var(token);
				if(var == NULL) error("Variable resolution error, not found");

				// Variable value resolution
				expr_val *val = malloc(sizeof(expr_val));
				memcpy(val, &var->value, sizeof(expr_val));
				list_add(&stack, val);
			} else if(is_func(token)) {
				list args;
				init_list(&args);
				function *f = get_func(token);
				if(f == NULL) error("Function resolution error, not found");

				for(int i = 0; i < f->arg_count; i++) {
					list_add(&args, list_pop(&stack));
				}
				list_add(&stack, f->func(&args));
			} else {
				printf("Leaked token: %s\n", token);
			}
		}
	}

	expr_val *item = malloc(sizeof(expr_val));
	memcpy(item, stack.items[0], sizeof(expr_val));
	destroy_list(&stack);
	return item;
}

int build_expr(list *ls, int offset, list *output) {
	return build_expr_(ls, offset, output, ";");
}
int build_expr_(list *ls, int offset, list *output, const char *terminator) {
	list operators;
	init_list(&operators);

	int i;
	for(i = offset; strcmp((char *)(ls->items[i]), terminator) != 0; i++) {
		char *token = (char *)ls->items[i];
		if(is_int(token)) {
			expr_val *x = malloc(sizeof(expr_val));
			x->type = INT64;
			x->value.int64 = parse_int(token);
			list_add(output, x);
		} else if(is_float(token)) {
			expr_val *x = malloc(sizeof(expr_val));
			x->type = FLOAT64;
			x->value.float64 = parse_float(token);
			list_add(output, x);
		} else if(is_func(token) || strcmp(token, "(") == 0) {
			list_add(&operators, token);
		} else if(strcmp(token, ")") == 0) {
			while(strcmp(LIST_LAST(operators), "(") != 0) {
				list_add(output, (char *)list_pop(&operators));
			}
			list_pop(&operators);
			if(operators.count != 0 && is_func(LIST_LAST(operators))) {
				list_add(output, list_pop(&operators));
			}
		} else if(strcmp(token, ",") == 0) {
			while(strcmp(LIST_LAST(operators), "(") != 0) {
				list_add(output, (char *)list_pop(&operators));
			}
		} else if(is_operator(token)) {
			while(operators.count != 0 && is_operator(LIST_LAST(operators)) && (
					right_assoc(token)
						? get_precedence(token) < get_precedence(LIST_LAST(operators))
						: get_precedence(token) <= get_precedence(LIST_LAST(operators)))) {
				list_add(output, list_pop(&operators));
			}
			list_add(&operators, token);
		} else {
			// Catch-all for variable names
			list_add(output, token);
		}
	}
	for(int j = operators.count - 1; j >= 0; j--) {
		list_add(output, operators.items[j]);
	}
	return i;
}
