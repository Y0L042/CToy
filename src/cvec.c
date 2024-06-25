#include "cvec.h"

#include <stdlib.h>

void cvec_int_init(CVecInt* cvec)
{
	cvec->count = 0;
	cvec->capacity = 0;
	cvec->data = NULL;
}

void cvec_int_free(CVecInt* cvec)
{
	FREE_ARRAY(int, cvec, cvec->capacity);
	cvec_int_init(cvec);
}

void cvec_int_add_item(CVecInt* cvec, int data)
{
	if (cvec->capacity  < cvec->count + 1)
	{
		int oldCapacity = cvec->capacity;
		cvec->capacity = GROW_CAPACITY(oldCapacity);
		cvec->data = GROW_ARRAY(int, cvec->data, oldCapacity, cvec->capacity);
	}

	cvec->data[cvec->count] = data;
	cvec->count++;
}

void cvec_int_remove_idx(CVecInt* cvec, int idx)
{
}

