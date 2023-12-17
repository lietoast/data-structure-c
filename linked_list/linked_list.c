#include "linked_list.h"

/**
 * The linked_list_init function creates a linked list and returns it.
 * If there is not enough room to create it, the function returns NULL.
 * Any data stored in the linked list must be able to compared with 
 * cmpdata.
 * 
 * The cmpdata function must return an integer less than, equal to, or 
 * greater than zero if the first argument is considered to be repectively
 * less than, equal to, ro greater than the second.
 */
DS *linked_list_init(int (*cmpdata)(const void *, const void *))
{
	DS *r;
	lklist_t *l;

	r = malloc(sizeof(DS));
	if (r == NULL)
		return r;
	
	r->cmpdata = cmpdata;
	r->type = DS_TYPE_LINKED_LIST;

	l = malloc(sizeof(lklist_t));
	if (l == NULL)
	{
		free(r);
		return NULL;
	}

	l->head = NULL;
	l->tail = NULL;
	l->len = 0;

	r->structure = l;

	return r;
}

/**
 * The linked_list_destroy function frees all the memory that was allocated
 * to the linked list. If ds isn't a linked list, no operation is performed.
 */
void linked_list_destroy(DS *ds)
{
	lklist_t *l;
	LLN *np, *cur;

	if (!ds_is_linked_list(ds))
		return;

	l = ds->structure;

	np = l->head;
	if (np != NULL)
	{
		for (cur = np->next; cur != np; cur = np->next)
		{
			np->next = cur->next;
			free(cur);
		}
		free(np);
	}

	free(l);
	free(ds);

}

/**
 * The linked_list_get function returns the ith element stored in the list. 
 * If index i is out of range or ds is not a linked list, the function
 * returns NULL and a dserr will be set.
 */
void *linked_list_get(DS *ds, int64_t i, dserr_t *e)
{
	lklist_t *l;
	LLN **np;
	int64_t j;

	if (!ds_is_linked_list(ds))
	{
		panic(&e, &ERROR_DS_TYPE);
		return NULL;
	}

	l = ds->structure;

	if (i < 0 || i >= l->len)
	{
		panic(&e, &ERROR_OUT_OF_RANGE);
		return NULL;
	}

	np = &(l->head);
	for (j = 0; j < i; j ++)
	{
		np = (*np)->next;
	}

	return (*np)->data;
}

/**
 * The linked_list_find function returns the first position that key appears
 * in the linked list, if key doesn't exist in the linked list or ds isn't a 
 * linked list, the function returns -1.
 */
int64_t linked_list_find(DS *ds, void *key)
{
	int64_t i;
	lklist_t *l;
	LLN **np;

	if (!ds_is_linked_list(ds))
		return -1;
	
	l = ds->structure;
	
	np = &(l->head);
	i = 0;
	for (i = 0; i < l->len; i ++)
	{
		if (ds->cmpdata((*np)->data, key) == 0)
			return i;
		*np = (*np)->next;
	}

	return -1;
}

/**
 * The linked_list_insert function insert one element into the linked list; if
 * ds isn't a linked list or the insert position i isn't availabe, a dserr will
 * be set.
 */
void linked_list_insert(DS *ds, int64_t i, void *ele, dserr_t *e)
{
	int64_t j;
	lklist_t *l;
	LLN *prev, *cur;

	if (!ds_is_linked_list(ds))
	{
		panic(&e, &ERROR_DS_TYPE);
		return;
	}
	l = ds->structure;
	if (i < 0 || i > l->len)
	{
		panic(&e, &ERROR_OUT_OF_RANGE);
		return;
	}

	// TODO: finish this function
}


















