#include "first_coloring.h"
#include "node.h"
#include "edge.h"

/* Estudia la lista de aristas conflictivas de (estado) para ir resolviendo
 * los conflictos de color uno por uno
 *
 * PRE: estado != NULL
 *
 *	K = ResolverConflictos (estado)
 *
 * POS: "estado posee coloreo propio" && "el coloreo emplea K colores"
 */
short ResolverConflictos (EstadoNetwork *estado)
{
	short K = 0;  /* Nº de colores final empleado */
	short M = 0;  /* Nº de aristas conflictivas */
	int i;
	u32 v1;  /* Vértice de origen  de un lado */
	u32 v2;  /* Vértice de destino de un lado */
	edge_t *edge = NULL;
	edge_list_t list = NULL;
	
	ASSERT (estado != NULL)
	
	list = estado->l_con;
	M = el_get_size (list);
	
	for (i = 0 ; i < M ; i++) {
		
		edge = el_get_actual (list);
		
		v1 = edge->nodeOrig;
		v2 = edge->nodeDest;
		
		
	}
	
}

