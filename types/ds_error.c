#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "ds_error.h"

/**
 * The panic function lets e points to dserr.
 */
void panic(dserr_t **e, const dserr_t *dserr)
{
	**e = *((dserr_t *)dserr);
}

/**
 * The pdserr function prints errmsg of e to stderr.
 */
int pdserr(const dserr_t e, const char *msg)
{
	if (!dscatch(e))
		return -1;
	
	if (strcmp(msg, "") != 0)
		return fprintf(stderr, "%s: %s\n", msg, e.errmsg);
	else
		return fprintf(stderr, "%s\n", e.errmsg);
}

/**
 * The free_all function free()s all the poniters.
 */
void free_all(int pnum, ...)
{
	va_list ptrs;
	int i;

	va_start(ptrs, pnum);

	for (i = 0; i < pnum; i ++)
	{
		free(va_arg(ptrs, void *));
	}

	va_end(ptrs);
}

/**
* The dscatch function returns if e is a real error.
*/
bool dscatch(dserr_t e)
{
	return e.errno >= 0;
}
