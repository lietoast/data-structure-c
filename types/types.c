#include "types.h"

/**
 * Check if ds is a vector.
 */
bool ds_is_vector(DS *ds)
{
	return ds->type == DS_TYPE_VECTOR;
}


