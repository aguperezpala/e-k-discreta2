#include "consts.h"
#include "node.h"

/* recordemos que tenemos tambien el caso alfabetico, podriamos usar entero
 * para el alfabetico simplemente casteandolo o usando atoi...
 */
/* ¿¿¿¿¿¿ ?????? */


/* Creamos una arista
REQUIRES:
0 <= nodeOrig, nodeDest < 7000
*/
INLINE edge_t * edge_create (u32 capacity, u32 nodeOrig, u32 nodeDest)
{
	edge_t * result = (edge_t *) malloc (1, sizeof (edge_t));
	
	/* pres */
	ASSERT (nodeOrig < 7000 && nodeDest < 7000);
	
	result->flow = 0;
	result->capacity = capacity;
	result->nodeOrig = nodeOrig;
	result->nodeDest = nodeDest;
	
	return result;
}

