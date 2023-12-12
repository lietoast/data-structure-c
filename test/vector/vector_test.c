#include <stdlib.h>
#include <stdio.h>

#include "../../vector/vector.h"

int cmpdata(const void *fele, const void *sele);
void print_vector(DS *ds);

int main(void)
{
	DS *ds;
	dserr_t e = NOE;
	int64_t i;
	int *element;
	int mock_data[10] = {32, 98, 101, 42, 92, 80, 77, 56, 908, 11};

	ds = vector_init(cmpdata);
	printf("init success\n");

	for (i = 0; i < 40; i ++)
	{	
		vector_insert(ds, i, &mock_data[i%10], &e);
		if (dscatch(e))
		{
			pdserr(e, "vector_insert() failed");
			vector_destroy(ds);
			exit(1);
		}
	}
	printf("insertion completed\n");
	printf("len: ");
	printf("%lld\n", vector_length(ds));
	printf("content: ");
	print_vector(ds);
	
	e = NOE;
	for (i = 0; i < 20; i ++)
	{
		vector_delete(ds, 0, &e);
		if (dscatch(e))
		{
			pdserr(e, "vector_delete() failed");
			vector_destroy(ds);
			exit(1);
		}
	}
	printf("delete success\n");
	print_vector(ds);

	vector_update(ds, 1, &mock_data[0], &e);
	printf("vector updated\n");
	print_vector(ds);

	vector_reverse(ds, &e);
	printf("vector reversed\n");
	print_vector(ds);

	vector_sort(ds, &e);
	printf("vector sorted\n");
	print_vector(ds);

	vector_clear(ds);
	printf("clear success\n");
	printf("len: ");
	printf("%lld\n", vector_length(ds));
	print_vector(ds);	
	printf("empty: %d\n", vector_empty(ds));

	e = NOE;
	vector_insert(ds, 10, &mock_data[0], &e);
	if (dscatch(e))
	{
		pdserr(e, "debug success");
	}

	vector_destroy(ds);	

	exit(0);
}

int cmpdata(const void *fele, const void *sele)
{
	const int *x, *y;

	x = *((const void **)fele);
	y = *((const void **)sele);

	return *x - *y;
}

void print_vector(DS *ds)
{
	int64_t i;
	int *cur_ele;
	dserr_t e = NOE;

	for (i = 0; i < vector_length(ds); i ++)
	{
		cur_ele = vector_get(ds, i, &e);
		if (dscatch(e))
		{
			pdserr(e, "vector_get() failed");
		}
		printf("%d ", *cur_ele);
	}
	printf("\n");
}
