#ifndef _TYPES_H__
#define _TYPES_H__

#include <stdbool.h>
#include <sys/types.h>

struct data_structrue
{
	void *structure;
	int (*cmpdata)(const void *, const void *);
	unsigned char type;
};

typedef struct data_structrue DS;

static const unsigned char DS_TYPE_VECTOR = (unsigned char)0x00;
static const unsigned char DS_TYPE_LINKED_LIST = (unsigned char)0x01;

typedef void *ELETYPE;

struct vector
{
	ELETYPE *array;
	int64_t cap;
	int64_t len;
};

typedef struct vector vec_t;

/**
 * Check if ds is a vector.
 */
bool ds_is_vector(DS *ds);

#endif
