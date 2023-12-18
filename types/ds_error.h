#ifndef _DS_ERROR_H__
#define _DS_ERROR_H__

#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

struct ds_error
{
	int errno;
	char *errmsg;
};

typedef struct ds_error dserr_t;

static const dserr_t ERROR_DS_TYPE = {0, "data structure type mismatch"};
static const dserr_t ERROR_OUT_OF_RANGE = {1, "index out of range"};
static const dserr_t ERROR_NO_MEMORY = {2, "out of memory"};

static const dserr_t NOE = {-1, "everything is fine"};

/**
 * The panic function lets e points to dserr.
 */
void panic(dserr_t **e, const dserr_t *dserr);

/**
 * The pdserr function prints errmsg of e to stderr.
 */
int pdserr(const dserr_t e, const char *msg);

/**
 * The free_all function free()s all the poniters.
 */
void free_all(int pnum, ...);

/**
* The dscatch function returns if e is a real error.
*/
bool dscatch(dserr_t e); 

#endif
