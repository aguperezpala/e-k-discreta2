#include "node.h"
#include "edge_list.h"
#include <stdio.h>
#include <stdlib.h>

/* Heap global con los indices de los nodos */
static int nodes_heap[7000];

struct alist_vert **build_max_deg_heap(struct alist_vert **A, int size)
{
        int i, heapsize = size;

        for (i = size / 2; i > 0; i--) {
                max_heapify_deg(A, i, heapsize);
        }

        return A;
}


struct alist_vert **build_max_dsatur_heap(struct alist_vert **A, int size)
{
        int i, heapsize = size;

        for (i = size / 2; i > 0; i--) {
                max_heapify_dsatur(A, i, heapsize);
        }

        return A;
}


void max_heapify_deg(struct alist_vert **A, int i, int heapsize)
{
        int l, r, largest;
        struct alist_vert * tmp;

        l = left(i);
        r = right(i);

        if (l <= heapsize && A[l - 1]->deg > A[i - 1]->deg) {
                largest = l;
        } else {
                largest = i;
        }

        if (r <= heapsize && A[r - 1]->deg > A[largest - 1]->deg)
                largest = r;

        if (largest != i) {

                tmp = A[i - 1];
                A[i - 1] = A[largest - 1];
                A[largest - 1] = tmp;
                
		max_heapify_deg(A, largest, heapsize);
        }

}

void max_heapify_dsatur(struct alist_vert **A, int i, int heapsize)
{
        int l, r, largest;
        struct alist_vert * tmp;

        l = left(i);
        r = right(i);

        if (l <= heapsize && A[l - 1]->dsatur > A[i - 1]->dsatur) {
                largest = l;
        } else {
                largest = i;
        }

        if (r <= heapsize && A[r - 1]->dsatur > A[largest - 1]->dsatur)
                largest = r;

        if (largest != i) {

                tmp = A[i - 1];
                A[i - 1] = A[largest - 1];
                A[largest - 1] = tmp;
                
		max_heapify_dsatur(A, largest, heapsize);
        }

}


struct alist_vert * extract_max_deg(struct alist_vert **A, int *heapsize)
{
        struct alist_vert * max;

        if (*heapsize < 1) {
                printf("EXTRACT_MIN FATAL ERROR!!!");
                return NULL;    
        }

        max = A[0];
        A[0] = A[*heapsize - 1];
        *heapsize -= 1;
        max_heapify_deg(A, 1, *heapsize);

#ifdef DEBUG
        printf("EXTRACT_MAX %d\n", max->deg);
#endif
        return max;
}


struct alist_vert * extract_max_dsatur(struct alist_vert **A, int *heapsize)
{
        struct alist_vert * max;

        if (*heapsize < 1) {
                printf("EXTRACT_MIN FATAL ERROR!!!");
                return NULL;    
        }

        max = A[0];
        A[0] = A[*heapsize - 1];
        *heapsize -= 1;
        max_heapify_dsatur(A, 1, *heapsize);

#ifdef DEBUG
        printf("EXTRACT_MAX %d\n", max->dsatur);
#endif
        return max;
}


int left(int i)
{
        return i << 1;
}

int right(i)
{
        return i << 1 | 1;
}

int parent(i)
{
        return i >> 1;
}
