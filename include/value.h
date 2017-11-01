#ifndef VALUE_H_
	#define VALUE_H_

	#include <stdint.h>
	#include <util.h>

	typedef struct {
		unsigned type;
		union {
			int8_t   int8;
			int16_t  int16;
			int32_t  int32;
			int64_t  int64;

			uint8_t  uint8;
			uint16_t uint16;
			uint32_t uint32;
			uint64_t uint64;

			float    float32;
			double   float64;
		} value;
	} expr_val;

	typedef int bool;

	void print_value(expr_val *x);
	bool is_truthy(expr_val *x);

	// Promotes the value of the lower precision to the higher precision
	void promote(expr_val *a, expr_val *b);
	// Converts the given value to a new type
	void convert(expr_val *a, int type);
#endif
