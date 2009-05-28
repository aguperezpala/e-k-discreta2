#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>

#include "consts.h"

typedef struct s_edge {
	u32 capacity;
	u32 flow;
	u32 nodeOrig;
	u32 nodeDest;
	/*! Podriamos probar con short */
} edge_t;

/* Creamos una arista
	REQUIRES:
		0 <= nodeOrig, nodeDest < 7000
*/
edge_t * edge_create (u32 capacity, u32 nodeOrig, u32 nodeDest);


/* destructor
 	REQUIRES:
		e != NULL
*/
void edge_destroy (edge_t * e);



#endif
