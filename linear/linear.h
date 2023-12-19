#ifndef _LINEAR_H__
#define _LINEAR_H__

#include <stdlib.h>

#include "../types/types.h"
#include "../types/ds_error.h"

#include "../vector/vector.h"
#include "../linked_list/linked_list.h"

/**
 * The top function returns the element on top of a stack (aka, the last element 
 * in a linear structure). If ds isn't a linear structure or ds is empty, the 
 * function returns NULL.
 */
void *top(DS *ds);

/**
 * The pop function deletes and returns the element on top of a stack (aka, the
 * last element in a linear structure). If ds isn't a linear structure or ds is
 * empty, the function returns NULL.
 */
void *pop(DS *ds);

/**
 * The push function add one element to the top of a stack (aka, the last position
 * of a linear structure). If ds isn't a linear structure, the function returns a
 * dserr, otherwise, it returns NOE.
 */
dserr_t push(DS *ds, void *element);

/**
 * The front function returns the first element in a queue (aka, the first element
 * in a linear structure). If ds isn't a linear structure or ds is empty, the 
 * function returns NULL.
 */
void *front(DS *ds);

/**
 * The enqueue function add one element to the end of a queue (aka, the last pos-
 * ition of a linear structure). If ds isn't a linear structure, the function 
 * returns a dserr, otherwise, it returns NOE.
 */
dserr_t enqueue(DS *ds, void *element);

/**
 * The dequeue function deletes and returns the element at head of a queue (aka, 
 * the first position of a linear structure). If ds isn't a linear structure or 
 * ds is empty, the function returns NULL.
 */
void *dequeue(DS *ds);

#endif
