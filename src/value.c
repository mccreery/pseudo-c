#include <stdint.h>
#include <stdio.h>
#include <util.h>
#include <value.h>

void promote(expr_val *a, expr_val *b) {
	if(precision[a->type] > precision[b->type]) {
		convert(b, a->type);
	} else if(precision[a->type] < precision[b->type]) {
		convert(a, b->type);
	}
}

void print_value(expr_val *x) {
	switch(x->type) {
		case INT8:    printf("%d", x->value.int8); break;
		case INT16:   printf("%d", x->value.int16); break;
		case INT32:   printf("%d", x->value.int32); break;
		case INT64:   printf("%d", x->value.int64); break;
		case UINT8:   printf("%u", x->value.uint8); break;
		case UINT16:  printf("%u", x->value.uint16); break;
		case UINT32:  printf("%u", x->value.uint32); break;
		case UINT64:  printf("%u", x->value.uint64); break;
		case FLOAT32: printf("%f", x->value.float32); break;
		case FLOAT64: printf("%f", x->value.float64); break;
	}
}

bool is_truthy(expr_val *x) {
	switch(x->type) {
		case INT8:    return x->value.int8 != 0; break;
		case INT16:   return x->value.int16 != 0; break;
		case INT32:   return x->value.int32 != 0; break;
		case INT64:   return x->value.int64 != 0; break;
		case UINT8:   return x->value.uint8 != 0; break;
		case UINT16:  return x->value.uint16 != 0; break;
		case UINT32:  return x->value.uint32 != 0; break;
		case UINT64:  return x->value.uint64 != 0; break;
		case FLOAT32: return x->value.float32 != 0; break;
		case FLOAT64: return x->value.float64 != 0; break;
		default: error("Unknown variable type");
	}
}

void convert(expr_val *a, int type) {
	if(a->type == type) return;

	if(type <= UINT64) {
		int64_t temp;
		switch(a->type) {
			case INT8:    temp = a->value.int8; break;
			case INT16:   temp = a->value.int16; break;
			case INT32:   temp = a->value.int32; break;
			case INT64:   temp = a->value.int64; break;
			case UINT8:   temp = a->value.uint8; break;
			case UINT16:  temp = a->value.uint16; break;
			case UINT32:  temp = a->value.uint32; break;
			case UINT64:  temp = a->value.uint64; break;
			case FLOAT32: temp = a->value.float32; break;
			case FLOAT64: temp = a->value.float64; break;
		}

		switch(type) {
			case INT8:    a->value.int8 = temp; break;
			case INT16:   a->value.int16 = temp; break;
			case INT32:   a->value.int32 = temp; break;
			case INT64:   a->value.int64 = temp; break;
			case UINT8:   a->value.uint8 = temp; break;
			case UINT16:  a->value.uint16 = temp; break;
			case UINT32:  a->value.uint32 = temp; break;
			case UINT64:  a->value.uint64 = temp; break;
		}
	} else {
		double temp;
		switch(a->type) {
			case INT8:    temp = a->value.int8; break;
			case INT16:   temp = a->value.int16; break;
			case INT32:   temp = a->value.int32; break;
			case INT64:   temp = a->value.int64; break;
			case UINT8:   temp = a->value.uint8; break;
			case UINT16:  temp = a->value.uint16; break;
			case UINT32:  temp = a->value.uint32; break;
			case UINT64:  temp = a->value.uint64; break;
			case FLOAT32: temp = a->value.float32; break;
			case FLOAT64: temp = a->value.float64; break;
		}

		if(type == FLOAT32) {
			a->value.float32 = temp;
		} else {
			a->value.float64 = temp;
		}
	}
	a->type = type;
}
