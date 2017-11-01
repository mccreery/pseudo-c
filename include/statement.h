#ifndef STATEMENT_H_
	#define STATEMENT_H_

	#include <list.h>
	#include <util.h>

	/** Represents the function to be called when a statement is ran,
	 *  and the data it should operate on. */
	typedef struct {
		void (*func)(void *);
		/** A pointer to a relevant struct of data to the statement,
		 *  depending on the function */
		void *data;
	} statement;

	/** Builds statements from the given list of tokens until it reaches the end. */
	void statement_builder(list *ls, list *statements);
#endif
