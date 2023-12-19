#include <stdlib.h>
#include <stdio.h>

#include "../../linear/linear.h"

int cmpdata(const void *fele, const void *sele);
void show_linear(DS *ds);

int main(void)
{
	DS *l, *v;
	int mock_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	dserr_t e;
	int *ele, i;

	v = vector_init(cmpdata);
	l = linked_list_init(cmpdata);

	for (i = 0; i < 10; i ++)
		if (dscatch(e = push(v, &mock_data[i])))
		{
			pdserr(e, "failed to push data into vector");
			exit(-1);
		}
	
	for (i = 0; i < 10; i ++)
		if (dscatch(e = push(l, &mock_data[i])))
		{
			pdserr(e, "failed to push data into linked list");
			exit(-1);
		}
	
	ele = front(v);
	printf("%d is the first element of vector\n", *ele);
	ele = front(l);
	printf("%d is the first element of linked list\n", *ele);

	ele = top(v);
	printf("%d is the last element of vector\n", *ele);
	ele = top(l);
	printf("%d is the last element of linked list\n", *ele);

	printf("After pushing 1-10 into linked list: ");
	show_linear(l);
	printf("After pushing 1-10 into vector: ");
	show_linear(v);

	vector_destroy(v);
	linked_list_destroy(l);

	exit(0);
}

int cmpdata(const void *fele, const void *sele)
{
	return 0;
}

void show_linear(DS *ds)
{
	int *ele;

	while ((ele = dequeue(ds)) != NULL)
	{
		printf("%d ", *ele);
	}
	printf("\n");
}
