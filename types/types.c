#include "types.h"

/**
 * Check if ds is a vector.
 */
bool ds_is_vector(DS *ds)
{
	return ds->type == DS_TYPE_VECTOR;
}

/**
 * Check if ds is a linked list.
 */
bool ds_is_linked_list(DS *ds)
{
	return ds->type == DS_TYPE_LINKED_LIST;
}



