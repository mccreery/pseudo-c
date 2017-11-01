#ifndef EXPRESSION_H_
	#define EXPRESSION_H_

	#include <list.h>
	#include <util.h>

	int build_expr(list *ls, int offset, list *output);
	int build_expr_(list *ls, int offset, list *output, const char *terminator);
	expr_val *evaluate(list *input);
	int get_precedence(const char *operator);
	bool right_assoc(const char *operator);
#endif
