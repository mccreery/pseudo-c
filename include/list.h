#ifndef LIST_H_
	#define LIST_H_

	typedef struct {
		void **items;
		int count;
		int capacity;
	} list;

	void init_list(list *ls);
	void list_add(list *ls, void * const item);
	void *list_pop(list *ls);
	void destroy_list(list *ls);
	void print_list(list *ls);

	#define LIST_LAST(l) ((l).items[(l).count - 1])
#endif
