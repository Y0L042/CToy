#ifndef CVEC_H
#define CVEC_H

#include "memory.h"

typedef struct {
	int count;
	int capacity;
	int* data;
} CVecInt;

void cvec_int_init(CVecInt* cvec);
void cvec_int_free(CVecInt* cvec);
void cvec_int_add_item(CVecInt* cvec, int data);
void cvec_int_remove_idx(CVecInt* cvec, int idx);

#endif
