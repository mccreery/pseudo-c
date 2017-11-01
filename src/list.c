#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <util.h>
//#define DEBUG_INFO

void init_list(list *ls) {
	ls->count = 0;
	ls->capacity = 16;
	ls->items = malloc(sizeof(void *) * ls->capacity);
}
void destroy_list(list *ls) {
	int i;
	for(i = 0; i < ls->count; i++) {
		if(ls->items[i]) free(ls->items[i]);
	}
}

void list_add(list *ls, void * const item) {
	if(ls->count >= ls->capacity) {
		while(ls->count >= ls->capacity) {
			ls->capacity <<= 1;
		}
		ls->items = realloc(ls->items, sizeof(void *) * ls->capacity);
	}
	ls->items[ls->count++] = item;

#ifdef DEBUG_INFO
	fputs("Add: ", stdout);
	print_list(ls);
#endif
}

void *list_pop(list *ls) {
	if(ls->count == 0) error("Nothing to pop from list");
	void *item = LIST_LAST(*ls);
	LIST_LAST(*ls) = NULL;
	ls->count--;

#ifdef DEBUG_INFO
	fputs("Pop! ", stdout);
	print_list(ls);
#endif

	return item;
}

void print_list(list *ls) {
	for(int i = 0; i < ls->count; i++) {
		if(((expr_val *)ls->items[i])->type <= FLOAT64) {
			print_value((expr_val *)ls->items[i]);
		} else {
			fputs((char *)ls->items[i], stdout);
		}

		if(i != ls->count - 1) {
			putchar(',');
			putchar(' ');
		}
	}
	putchar('\n');
}
