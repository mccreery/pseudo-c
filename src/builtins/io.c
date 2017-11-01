#include <builtins.h>
#include <environment.h>
#include <list.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <util.h>
#include <value.h>
#include <gpio.h>

#ifdef _WIN32
	// windows.h contains clashing macros
	void Sleep(int16_t milliseconds);
#else
	#include <unistd.h>
#endif

expr_val *sleep_func(list *args) {
	convert(args->items[0], UINT32);

#ifdef _WIN32
	Sleep(((expr_val *)args->items[0])->value.uint32);
#else
	usleep(((expr_val *)args->items[0])->value.uint32 * 1000);
#endif

	expr_val *result = malloc(sizeof(expr_val));
	result->type = INT32;
	result->value.int32 = 0;

	return result;
}
function sleep_ib = {"sleep", 1, sleep_func};

expr_val *print_func(list *args) {
	print_value(args->items[0]);
	putchar('\n');

	expr_val *result = malloc(sizeof(expr_val));
	result->type = INT32;
	result->value.int32 = 0;

	return result;
}
function print_ib = {"print", 1, print_func};

expr_val *export_pin_func(list *args) {
	expr_val *x = args->items[0];
	convert(x, INT32);

	expr_val *result = malloc(sizeof(expr_val));
	result->type = INT32;
	result->value.int32 = exportp(x->value.int32);

	return result;
}
function export_pin_ib = {"exportpin", 1, export_pin_func};

expr_val *unexport_pin_func(list *args) {
	expr_val *x = args->items[0];
	convert(x, INT32);

	expr_val *result = malloc(sizeof(expr_val));
	result->type = INT32;
	result->value.int32 = unexportp(x->value.int32);

	return result;
}
function unexport_pin_ib = {"unexportpin", 1, unexport_pin_func};

expr_val *direct_pin_func(list *args) {
	expr_val *x = args->items[0];
	convert(x, INT32);
	expr_val *y = args->items[1];
	convert(y, INT32);

	expr_val *result = malloc(sizeof(expr_val));
	result->type = INT32;
	result->value.int32 = directp(y->value.int32, x->value.int32);

	return result;
}
function direct_pin_ib = {"directpin", 2, direct_pin_func};

expr_val *write_pin_func(list *args) {
	expr_val *x = args->items[0];
	convert(x, INT32);
	expr_val *y = args->items[1];
	convert(y, INT32);

	expr_val *result = malloc(sizeof(expr_val));
	result->type = INT32;
	result->value.int32 = writep(y->value.int32, x->value.int32);

	return result;
}
function write_pin_ib = {"writepin", 2, write_pin_func};

expr_val *read_pin_func(list *args) {
	expr_val *x = args->items[0];
	convert(x, INT32);

	expr_val *result = malloc(sizeof(expr_val));
	result->type = INT32;
	result->value.int32 = readp(x->value.int32);

	return result;
}
function read_pin_ib = {"readpin", 1, read_pin_func};
