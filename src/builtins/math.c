#include <environment.h>
#include <list.h>
#include <math.h>
#include <stdlib.h>
#include <util.h>
#include <value.h>

#define M_PI 3.14159265358979323846264338327

expr_val *sin_func(list *args) {
	expr_val *rads = args->items[0];
	convert(rads, FLOAT64);

	expr_val *result = malloc(sizeof(expr_val));
	result->type = FLOAT64;
	result->value.float64 = sin(rads->value.float64);
	return result;
}
function sin_ib = {"sin", 1, sin_func};

expr_val *cos_func(list *args) {
	expr_val *rads = args->items[0];
	convert(rads, FLOAT64);

	expr_val *result = malloc(sizeof(expr_val));
	result->type = FLOAT64;
	result->value.float64 = cos(rads->value.float64);
	return result;
}
function cos_ib = {"cos", 1, cos_func};

expr_val *tan_func(list *args) {
	expr_val *rads = args->items[0];
	convert(rads, FLOAT64);

	expr_val *result = malloc(sizeof(expr_val));
	result->type = FLOAT64;
	result->value.float64 = tan(rads->value.float64);
	return result;
}
function tan_ib = {"tan", 1, tan_func};

expr_val *radians_func(list *args) {
	expr_val *degs = args->items[0];
	convert(degs, FLOAT64);

	expr_val *result = malloc(sizeof(expr_val));
	result->type = FLOAT64;
	result->value.float64 = degs->value.float64 / 180.0 * M_PI;
	return result;
}
function radians_ib = {"radians", 1, radians_func};

expr_val *degrees_func(list *args) {
	expr_val *rads = args->items[0];
	convert(rads, FLOAT64);

	expr_val *result = malloc(sizeof(expr_val));
	result->type = FLOAT64;
	result->value.float64 = rads->value.float64 / M_PI * 180.0;
	return result;
}
function degrees_ib = {"degrees", 1, degrees_func};
