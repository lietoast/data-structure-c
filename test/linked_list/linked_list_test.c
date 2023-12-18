#include <stdlib.h>
#include <stdio.h>

#include "../../linked_list/linked_list.h"

int cmpdata(const void *fele, const void *sele);
void print_linked_list(DS *ds);

int main(void)
{
	DS *ds;
	int mock_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int64_t i, idx;
	dserr_t e = NOE;

	// init linked list
	ds = linked_list_init(cmpdata);

	// insert some data
	for (i = 0; i < 50; i ++)
	{
		linked_list_insert(ds, i, &mock_data[i%10], &e);
		if (dscatch(e))
		{
			pdserr(e, "failed to insert data");
			exit(-1);
		}
	}
	printf("inserted some data\n");
	print_linked_list(ds);

	// test find()
	for (i = 0; i < 10; i ++)
	{
		idx = linked_list_find(ds, &mock_data[i]);
		if (idx >= 0)
		{
			printf("%d in position %lld\n", mock_data[i], idx);
		}
		else
		{
			printf("%d doesn't exist in the list\n", mock_data[i]);
		}
	}

	// free linked list
	linked_list_destroy(ds);

	exit(0);
}

int cmpdata(const void *fele, const void *sele)
{
	const int *x, *y;
	x = fele;
	y = sele;

	return *x - *y;
}

void print_linked_list(DS *ds)
{
	int64_t i;
	int *ele;
	dserr_t e = NOE;

	for (i = 0; i < linked_list_length(ds); i ++)
	{
		ele = linked_list_get(ds, i, &e);
		if (dscatch(e))
		{
			pdserr(e, "failed to print linked list");
			return;
		}
		printf("%d ", *ele);
	}
	printf("\n");
}


