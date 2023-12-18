#ifndef _LINKED_LIST_H__
#define _LINKED_LIST_H__

#include <stdlib.h>

#include "../types/types.h"
#include "../types/ds_error.h"

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
DS *linked_list_init(int (*cmpdata)(const void *, const void *));

/**
 * The linked_list_destroy function frees all the memory that was allocated
 * to the linked list. If ds isn't a linked list, no operation is performed.
 */
void linked_list_destroy(DS *ds);

/**
 * The linked_list_get function returns the ith element stored in the list. 
 * If index i is out of range or ds is not a linked list, the function
 * returns NULL and a dserr will be set.
 */
void *linked_list_get(DS *ds, int64_t i, dserr_t *e);

/**
 * The linked_list_find function returns the first position that key appears
 * in the linked list, if key doesn't exist in the linked list or ds isn't a 
 * linked list, the function returns -1.
 */
int64_t linked_list_find(DS *ds, void *key);

/**
 * The linked_list_insert function insert one element into the linked list; if
 * ds isn't a linked list or the insert position i isn't availabe, a dserr will
 * be set.
 */
void linked_list_insert(DS *ds, int64_t i, void *ele, dserr_t *e);

/**
 * The linked_list_length function returns number of elements stored in the linked
 * list. If ds isn't a linked list, the function returns -1.
 */
int64_t linked_list_length(DS *ds);

#endif
