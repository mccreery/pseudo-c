#include <environment.h>
#include <list.h>
#include <parser.h>
#include <string.h>
#include <util.h>

execution_environment env;

void init_environment() {
	init_list(&env.functions);
	init_list(&env.variables);
}

bool is_var(const char *name) {
	for(int i = 0; i < env.variables.count; i++) {
		if(strcmp(name, ((variable *)env.variables.items[i])->name) == 0) return true;
	}
	return false;
}
bool is_func(const char *name) {
	for(int i = 0; i < env.functions.count; i++) {
		if(strcmp(name, ((function *)env.functions.items[i])->name) == 0) return true;
	}
	return false;
}

variable *get_var(const char *name) {
	for(int i = 0; i < env.variables.count; i++) {
		if(strcmp(name, ((variable *)env.variables.items[i])->name) == 0) {
			return env.variables.items[i];
		}
	}
	return NULL;
}
function *get_func(const char *name) {
	for(int i = 0; i < env.functions.count; i++) {
		if(strcmp(name, ((function *)env.functions.items[i])->name) == 0) {
			return env.functions.items[i];
		}
	}
	return NULL;
}
