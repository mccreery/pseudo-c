#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <stdarg.h>

const char *types[] = {
	"int8", "int16", "int32", "int64", "uint8", "uint16", "uint32", "uint64",
	"float32", "float64"
};
const int precision[] = {
	1, 2, 4, 8, 1, 2, 4, 8, 16, 32
};

int find_in_arr(const char **haystack, int count, const char *needle) {
	for(int i = 0; i < count; i++) {
		if(strcmp(haystack[i], needle) == 0) return i;
	}
	return -1;
}

void error(const char *reason, ...) {
	va_list args;
	va_start(args, reason);
	vfprintf(stderr, reason, args);
	va_end(args);
	exit(1);
}

/** @return true if the given character x is whitespace. */
bool is_whitespace(char x) {
	return x == ' ' || x == '\t' || x == '\n' || x == '\r';
}

const char *symbols = "(){}[]<>=!+-*/%,.&|~^\"';";
/** @return true if the given character is a valid symbol. */
bool is_symbol(char x) {
	int i;
	for(i = 0; i < strlen(symbols); i++) {
		if(symbols[i] == x) return 1;
	}
	return 0;
}

const char *operators[] = {
	"+", "-", "<<", ">>", "/", "*", "^", "&", "|",
	"==", ">=", "<=", ">", "<", "!="
};
bool is_operator(char *x) {
	int i;
	for(i = 0; i < 15; i++) {
		if(strcmp(operators[i], x) == 0) return 1;
	}
	return 0;
}

bool is_name(char *x) {
	if(x[0] == '\0' || ((x[0] < 'A' || x[0] > 'Z') && (x[0] < 'a' || x[0] > 'z'))) {
		return false;
	} else {
		for(int i = 0; x[i] != '\0'; i++) {
			if((x[i] < 'A' || x[i] > 'Z') && (x[i] < 'a' || x[i] > 'z') && (x[i] < '0' || x[i] > '9')) {
				return false;
			}
		}
		return true;
	}
}

bool is_int(char *str) {
	int i = 0;
	if(str[i] == '-') i++;
	if(str[i] == '\0') return false;
	for(; str[i] != '\0'; i++) {
		if(str[i] < '0' || str[i] > '9') return false;
	}
	return true;
}
int64_t parse_int(char *str) {
	int neg = 0;

	int64_t x = 0;
	int i = 0;
	if(str[i] == '-') {
		neg = 1;
		i++;
	}
	for(; str[i] != '\0'; i++) {
		if(str[i] < '0' || str[i] > '9') error("Invalid value for int with base 10");
		x *= 10;
		x += str[i] - '0';
	}
	if(neg) x = -x;
	return x;
}

bool is_float(char *str) {
	int i = 0;
	int point = false;
	if(str[i] == '-') i++;
	if(str[i] == '\0') return false;
	for(; str[i] != '\0'; i++) {
		if((str[i] < '0' || str[i] > '9') && str[i] != '.') return false;
		if(str[i] == '.') {
			if(point) return false;
			else      point = true;
		}
	}
	return true;
}
double parse_float(char *str) {
	int neg = 0;
	int point = -1;

	double x = 0;
	int i = 0;
	if(str[i] == '-') {
		neg = 1;
		i++;
	}
	for(; str[i] != '\0'; i++) {
		if((str[i] < '0' || str[i] > '9') && str[i] != '.') error("Invalid value for float with base 10");
		if(str[i] == '.') {
			point = i;
		} else {
			x *= 10;
			x += str[i] - '0';
		}
	}
	if(point != -1) {
		x /= pow(10, i - point - 1);
	}
	if(neg) x = -x;
	return x;
}
