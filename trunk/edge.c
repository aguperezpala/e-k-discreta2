#include "edge.h"


/* Creamos una arista
REQUIRES:
0 <= nodeOrig, nodeDest < 7000
*/
INLINE edge_t * edge_create (u32 capacity, u32 nodeOrig, u32 nodeDest)
{
	edge_t * result = (edge_t *) malloc (sizeof (edge_t));
	
	/* pres */
	ASSERT (nodeOrig < 7000 && nodeDest < 7000);
	
	result->flow = 0;
	result->capacity = capacity;
	result->nodeOrig = nodeOrig;
	result->nodeDest = nodeDest;
	
	return result;
}

/* destructor
 	REQUIRES:
		e != NULL
*/
INLINE void edge_destroy (edge_t * e)
{
	ASSERT (e != NULL)
	free (e);
}


