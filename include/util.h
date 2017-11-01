#ifndef UTIL_H_
	#define UTIL_H_

	#include <list.h>
	#include <stdint.h>
	#include <value.h>

	typedef int bool;
	#define false (0)
	#define true  (!false)

	void error(const char *reason, ...);
	bool is_whitespace(char x);
	bool is_symbol(char x);
	bool is_operator(char *x);
	bool is_name(char *x);
	int find_in_arr(const char **haystack, int count, const char *needle);

	extern const int precision[];
	extern const char *types[];
	#define INT8    0
	#define INT16   1
	#define INT32   2
	#define INT64   3

	#define UINT8   4
	#define UINT16  5
	#define UINT32  6
	#define UINT64  7

	#define FLOAT32 8
	#define FLOAT64 9

	bool is_int(char *str);
	bool is_float(char *str);
	int64_t parse_int(char *str);
	double parse_float(char *str);
#endif
