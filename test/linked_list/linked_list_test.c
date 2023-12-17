#include <stdlib.h>
#include <stdio.h>

#include "../../linked_list/linked_list.h"

int cmpdata(const void *fele, const void *sele);

int main(void)
{
	DS *ds;

	// init linked list
	ds = linked_list_init(cmpdata);

	// free linked list
	linked_list_destroy(ds);
}

int cmpdata(const void *fele, const void *sele)
{
	return 1;
}
