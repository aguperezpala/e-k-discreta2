#include "consts.h"
#include "node.h"
#include "edge.h"
#include "first_coloring.h"


/* Dado un vértice revisa sus vecinos para hallar el menor color aún libre */
static Color MenorColorLibre (node_t vert)
{
	Color c = 0;
}



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
	short i;
	Color c = 0;  /* Nuevo color escogido para un nodo */
	u32 v1;  /* Vértice de origen  de un lado */
	u32 v2;  /* Vértice de destino de un lado */
	
	
	ASSERT (estado != NULL)
	
	M = el_get_size (estado->l_con);
	
	for (i = 0 ; i < M ; i++) {
		
		edge = el_get_actual (estado->l_con);
		
		v1 = edge->nodeOrig;
		v2 = edge->nodeDest;
		
		if (estado->nodes[v1].color != estado->nodes[v2].color) {
			/* ¡No había conflicto! */
			el_avance (estado->l_con);
			continue;
		}
		
		/* Buscamos el vértice de menor grado, para otorgarle
		 * el menor color posible no-conflictivo */
		if (estado->nodes[v1].degree < estado->nodes[v2].degree) {
			c = MenorColorLibre (estado->nodes[v1]);
			estado->nodes[v1].color = c;
		} else {
			c = MenorColorLibre (estado->nodes[v1]);
			estado->nodes[v1].color = c;
		}
		
		if (estado->colores < c)
			estado->colores = c;
		if (K < c)
			K = c;
		
		el_avance (estado->l_con);
	}
	
	return K;
}

