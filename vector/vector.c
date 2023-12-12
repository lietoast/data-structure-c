#include <stdlib.h>

#include "vector.h"

/**
 * The increase_capacity function allocates more memory to the vector and returns
 * the new capacity of it.
 */
static int64_t increase_capacity(vec_t *vec);

/**
 * The decrease_capacity function reduces the memory usage of the vector and
 * returns the new capacity of it.
 */
static int64_t decrease_capacity(vec_t *vec);

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
DS *vector_init(int (*cmpdata)(const void *, const void *))
{
	vec_t *vec;
	DS *r = malloc(sizeof(DS));
	if (r == NULL)
		return NULL;
	
	r->cmpdata = cmpdata;
	r->type = DS_TYPE_VECTOR;

	vec = malloc(sizeof(vec_t));
	if (vec == NULL)
	{
		free_all(1, r);
		return NULL;
	}

	vec->array = malloc(DEFAULT_VEC_CAP * sizeof(ELETYPE));
	if (vec->array == NULL)
	{
		free_all(2, vec, r);
		return NULL;
	}

	vec->cap = DEFAULT_VEC_CAP;
	vec->len = 0;
	
	r->structure = vec;

	return r;
}

/**
 * Get element stored in the vector with index i.
 * If it's not available, the function restuns NULL and a dserr will be set.
 * If ds is not a vector, the function returns NULL and a dserr will be set.
 */
void *vector_get(DS *ds, int64_t i, dserr_t *e)
{
	vec_t *vec;

	if (!ds_is_vector(ds))
	{
		panic(&e, &ERROR_DS_TYPE);
		return NULL;
	}

	vec = ds->structure;
	if (i < 0 || i >= vec->len)
	{
		panic(&e, &ERROR_OUT_OF_RANGE);
		return NULL;
	}

	return vec->array[i];
}

/**
 * The vector_length function returns the number of valid data stored in the
 * vector. If ds is not a vector, the function retuns -1.
 */
int64_t vector_length(DS *ds)
{
	vec_t *vec;

	if (!ds_is_vector(ds))
		return -1;
	
	vec = ds->structure;
	
	return vec->len;
}

/**
 * Insert one element into the vector.
 * If ds is not a vector, do nothing except setting the dserr.
 * If position i is not available, the dserr will be set.
 */
void vector_insert(DS *ds, int64_t i, void *data, dserr_t *e)
{	
	vec_t *vec = NULL;
	int j;

	if (!ds_is_vector(ds))
	{
		panic(&e, &ERROR_DS_TYPE);
		return;
	}

	vec = ds->structure;

	if (i < 0 || i > vec->len)
	{
		panic(&e, &ERROR_OUT_OF_RANGE);
		return;
	}

	// check the capacity of this vector
	if (vec->len >= vec->cap)
		increase_capacity(vec);

	for (j = vec->len; j > 0 && j > i; j --)
	{
		vec->array[j] = vec->array[j-1];
	}
	vec->array[i] = data;

	vec->len ++;
}

/**
 * The vector_empty function checks if the vector is empty, returns false when
 * ds isn't a vector.
 */
bool vector_empty(DS *ds)
{
	if (!ds_is_vector(ds))
		return false;
	
	vec_t *vec = ds->structure;
	return vec->len == 0;
}

/**
 * The vector_delete function deletes the element in position i and returns the element
 * that was deleted.
 * If position i is not available, the function restuns NULL and a dserr will be set.
 * If ds is not a vector, the function returns NULL and a dserr will be set.
 */
void *vector_delete(DS *ds, int64_t i, dserr_t *e)
{
	vec_t *vec;
	void *r;

	if (!ds_is_vector(ds))
	{
		panic(&e, &ERROR_DS_TYPE);
		return NULL;
	}

	vec = ds->structure;
	
	if (i < 0 || i >= vec->len)
	{
		panic(&e, &ERROR_OUT_OF_RANGE);
		return NULL;
	}

	r = vec->array[i];
	
	for (; i < vec->len-1; i ++)
	{
		vec->array[i] = vec->array[i+1];
	}
	
	vec->len --;
	if (vec->cap > DEFAULT_VEC_CAP && vec->len <= (vec->cap >> 1))
		decrease_capacity(vec);

	return r;
}

/**
 * Updates the element value in position i and returns the old value.
 * If position i is not available, the function restuns NULL and a dserr will be set.
 * If ds is not a vector, the function returns NULL and a dserr will be set.
 */
void *vector_update(DS *ds, int64_t i, void *val, dserr_t *e)
{
	vec_t *vec;
	void *r;

	if (!ds_is_vector(ds))
	{
		panic(&e, &ERROR_DS_TYPE);
		return NULL;
	}
	
	vec = ds->structure;

	if (i < 0 || i >= vec->len)
	{
		panic(&e, &ERROR_OUT_OF_RANGE);
		return NULL;
	}

	r = vec->array[i];
	vec->array[i] = val;

	return r;
}

/**
 * The vector_clear function deletes all the elements that's stored in the vector.
 * The deleted elements will NOT be found again so the user has to make sure that
 * all the pointers in the vector have been backed up or freeed before the calling
 * vector_clear. If ds isn't a vector, no operation is performed.
 */
void vector_clear(DS *ds)
{
	vec_t *vec;

	if (!ds_is_vector(ds))
		return;

	vec = ds->structure;
	// reset cap and len of the vector
	vec->cap = DEFAULT_VEC_CAP;
	vec->len = 0;

	// clear the vector
	vec->array = realloc(vec->array, vec->cap * sizeof(ELETYPE));
}

/**
 * The vector_destroy function frees all the memory that is allocated to
 * ds. If ds isn't a vector, no operation is performed.
 */
void vector_destroy(DS *ds)
{
	vec_t *vec;

	if (!ds_is_vector(ds))
		return;
	
	vec = ds->structure;

	free(vec->array);
	free(vec);
	free(ds);
}

/**
 * The vector_sort function sorts list elements into ascending order.
 * If ds isn't a vector, a dserr will be set.
 */
void vector_sort(DS *ds, dserr_t *e)
{
	vec_t *vec;

	if (!ds_is_vector(ds))
	{
		panic(&e, &ERROR_DS_TYPE);
		return;
	}

	vec = ds->structure;

	qsort(vec->array, vec->len, sizeof(ELETYPE), ds->cmpdata);
}

/**
 * Reverse the elements in vector.
 * If ds isn't a vector, a dserr will be set.
 */
void vector_reverse(DS *ds, dserr_t *e)
{
	vec_t *vec;
	int i, j;
	ELETYPE tmp;

	if (!ds_is_vector(ds))
	{
		panic(&e, &ERROR_DS_TYPE);
		return;
	}

	vec = ds->structure;
	i = -1;
	j = vec->len;

	while (i ++ < j --)
	{
		tmp = vec->array[i];
		vec->array[i] = vec->array[j];
		vec->array[j] = tmp;
	}
}

/**
 * The increase_capacity function allocates more memory to the vector and returns
 * the new capacity of it.
 */
static int64_t increase_capacity(vec_t *vec)
{
	double incr_factor;

	if (vec->cap <= 500)
	{
		incr_factor = 2.0;
	}
	else
	{
		incr_factor = 1.25;
	}

	vec->cap = (int64_t)(vec->cap * incr_factor);
	vec->array = realloc(vec->array, vec->cap * sizeof(ELETYPE));

	return vec->cap;
}

/**
 * The decrease_capacity function reduces the memory usage of the vector and
 * returns the new capacity of it.
 */
static int64_t decrease_capacity(vec_t *vec)
{
	vec->cap -= (vec->cap >> 2);
	vec->array = realloc(vec->array, vec->cap * sizeof(ELETYPE));

	return vec->cap;
}

