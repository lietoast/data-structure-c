#ifndef _VECTOR_H__
#define _VECTOR_H__

#include <stdbool.h>

#include "../types/types.h"
#include "../types/ds_error.h"

#define DEFAULT_VEC_CAP 16

/**
 * The init_vector function creates a vector(aka, sequence list) with 
 * default vector capacity(16) and returns it.
 * If there is not enough room to create it, the function returns NULL.
 * Any data stored in the vector must be able to compared with cmpdata.
 *
 * cmpdata: compare two elements stored in the vector, retuns 0 when they
 * are equal, -1 when the first element is smaller than the second one, 1
 * when the first is larger than the second.
 */
DS *vector_init(int (*cmpdata)(const void *, const void *));

/**
 * Get element stored in the vector with index i.
 * If it's not available, the function restuns NULL and a dserr will be set.
 * If ds is not a vector, the function returns NULL and a dserr will be set.
 */
void *vector_get(DS *ds, int64_t i, dserr_t *e);

/**
 * The vector_length function returns the number of valid data stored in the
 * vector. If ds is not a vector, the function retuns -1.
 */
int64_t vector_length(DS *ds);

/**
 * Insert one element into the vector.
 * If ds is not a vector, do nothing except setting the dserr.
 * If position i is not available, the dserr will be set.
 */
void vector_insert(DS *ds, int64_t i, void *data, dserr_t *e);

/**
 * The vector_empty function checks if the vector is empty, returns false when
 * ds isn't a vector.
 */
bool vector_empty(DS *ds);

/**
 * The vector_delete function deletes the element in position i and returns the element
 * that was deleted.
 * If position i is not available, the function restuns NULL and a dserr will be set.
 * If ds is not a vector, the function returns NULL and a dserr will be set.
 */
void *vector_delete(DS *ds, int64_t i, dserr_t *e);

/**
 * Updates the element value in position i and returns the old value.
 * If position i is not available, the function restuns NULL and a dserr will be set.
 * If ds is not a vector, the function returns NULL and a dserr will be set.
 */
void *vector_update(DS *ds, int64_t i, void *val, dserr_t *e);

/**
 * The vector_clear function deletes all the elements that's stored in the vector.
 * The deleted elements will NOT be found again so the user has to make sure that
 * all the pointers in the vector have been backed up or freeed before the calling
 * vector_clear. If ds isn't a vector, no operation is performed.
 */
void vector_clear(DS *ds);

/**
 * The vector_destroy function frees all the memory that is allocated to
 * ds. If ds isn't a vector, no operation is performed.
 */
void vector_destroy(DS *ds);

/**
 * The vector_sort function sorts list elements into ascending order.
 * If ds isn't a vector, a dserr will be set.
 */
void vector_sort(DS *ds, dserr_t *e);

/**
 * Reverse the elements in vector.
 * If ds isn't a vector, a dserr will be set.
 */
void vector_reverse(DS *ds, dserr_t *e);

/**
 * The vector_find function checks if the given element exists in the
 * vector. If it does exist, vector_find() returns the position where
 * the element first appear; if it doesn't, the function returns -1.
 * If ds is not a vector, a dserr will be set.
 */
int64_t vector_find(DS *ds, void *element, dserr_t *e);

#endif
