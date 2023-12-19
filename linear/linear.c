#include "linear.h"

/**
 * The top function returns the element on top of a stack (aka, the last element 
 * in a linear structure). If ds isn't a linear structure or ds is empty, the 
 * function returns NULL.
 */
void *top(DS *ds)
{
	dserr_t e;

	switch (ds->type)
	{
		case DS_TYPE_VECTOR:
		return vector_get(ds, vector_length(ds)-1, &e);
		case DS_TYPE_LINKED_LIST:
		return linked_list_get(ds, linked_list_length(ds)-1, &e);
		default:
		return NULL;
	}
}

/**
 * The pop function deletes and returns the element on top of a stack (aka, the
 * last element in a linear structure). If ds isn't a linear structure or ds is
 * empty, the function returns NULL.
 */
void *pop(DS *ds)
{
	dserr_t e;

	switch (ds->type)
	{
		case DS_TYPE_VECTOR:
		return vector_delete(ds, vector_length(ds)-1, &e);
		case DS_TYPE_LINKED_LIST:
		return linked_list_delete(ds, linked_list_length(ds)-1, &e);
		default:
		return NULL;
	}
}

/**
 * The push function add one element to the top of a stack (aka, the last position
 * of a linear structure). If ds isn't a linear structure, the function returns a
 * dserr, otherwise, it returns NOE.
 */
dserr_t push(DS *ds, void *element)
{
	dserr_t e = NOE;

	switch (ds->type)
	{
		case DS_TYPE_VECTOR:
		vector_insert(ds, vector_length(ds), element, &e);
		return e;

		case DS_TYPE_LINKED_LIST:
		linked_list_insert(ds, linked_list_length(ds), element, &e);
		return e;

		default:
		e = ERROR_DS_TYPE;
		return e;
	}
}

/**
 * The front function returns the first element in a queue (aka, the first element
 * in a linear structure). If ds isn't a linear structure or ds is empty, the 
 * function returns NULL.
 */
void *front(DS *ds)
{
	dserr_t e;

	switch (ds->type)
	{
		case DS_TYPE_VECTOR:
		return vector_get(ds, 0, &e);
		case DS_TYPE_LINKED_LIST:
		return linked_list_get(ds, 0, &e);
		default:
		return NULL;
	}
}

/**
 * The enqueue function add one element to the end of a queue (aka, the last pos-
 * ition of a linear structure). If ds isn't a linear structure, the function 
 * returns a dserr, otherwise, it returns NOE.
 */
dserr_t enqueue(DS *ds, void *element)
{
	return push(ds, element);
}

/**
 * The dequeue function deletes and returns the element at head of a queue (aka, 
 * the first position of a linear structure). If ds isn't a linear structure or 
 * ds is empty, the function returns NULL.
 */
void *dequeue(DS *ds)
{
	dserr_t e;

	switch (ds->type)
	{
		case DS_TYPE_VECTOR:
		return vector_delete(ds, 0, &e);
		case DS_TYPE_LINKED_LIST:
		return linked_list_delete(ds, 0, &e);
		default:
		return NULL;
	}
}


