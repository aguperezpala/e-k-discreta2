#ifndef __HEAP_H
#define __HEAP_H

#include "node.h"
#include "../const.h"

/* heap */
struct alist_vert **build_max_deg_heap(struct alist_vert **A, int size);
struct alist_vert **build_max_dsatur_heap(struct alist_vert **A, int size);
void max_heapify_deg(struct alist_vert **A, int i, int heapsize);
void max_heapify_dsatur(struct alist_vert **A, int i, int heapsize);
struct alist_vert * extract_max_deg(struct alist_vert **A, int *heapsize);
struct alist_vert * extract_max_dsatur(struct alist_vert **A, int *heapsize);
int left(int i);
int right(int i);
int parent(int i);


#endif
