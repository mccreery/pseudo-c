#ifndef BUILTINS_H_
	#define BUILTINS_H_

	#include <environment.h>
	#include <list.h>
	#include <value.h>

	expr_val *sin_func(list *args);
	expr_val *cos_func(list *args);
	expr_val *tan_func(list *args);

	expr_val *radians_func(list *args);

	expr_val *print_func(list *args);

	extern function sin_ib, cos_ib, tan_ib,
		radians_ib, degrees_ib, print_ib,
		export_pin_ib, unexport_pin_ib, direct_pin_ib, write_pin_ib, read_pin_ib,
		sleep_ib;
#endif
