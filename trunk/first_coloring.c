#include <stdbool.h>
#include "consts.h"
#include "node.h"
#include "edge.h"
#include "first_coloring.h"


/* Indica si el color actual del vértice N está generando conflicto de colores.
 * Es decir, si algún vecino (hacia adelante o hacia atrás) comparte su color.
 *
 * PRE: estado != NULL && "existe el N-ésimo vértice de estado"
 */
static bool HayConflicto (EstadoNetwork *estado, u32 N)
{
	unsigned short d, i;
	node_t vert;
	edge_t *edge = NULL;
	
	ASSERT (estado != NULL)
	
	vert = estado->nodes[N];

	/* Revisamos los vecinos forward */
	d = el_get_size (vert.forwardList);
	for(i = 0 ; i < d ; i++) {
		edge = el_get_actual(vert.forwardList);
		if (estado->nodes[edge->nodeDest].color == vert.color)
			return false;
		else
			el_avance(vert.forwardList);
	}

	/* Revisamos los vecinos backward */
	d = el_get_size(vert.backwardList);
	for(i = 0 ; i < d ; i++) {
		edge = el_get_actual(vert.backwardList);
		if (estado->nodes[edge->nodeOrig].color == vert.color)
			return false;
		else
			el_avance(vert.backwardList);
	}

	return true;
}




/* Dado un vértice 'N' busca el menor color aún libre entre sus vecinos
 *
 * PRE: estado != NULL && "existe el N-ésimo vértice de estado"
 * POS: el color hallado para N no genera conflictos con sus vecinos
 */
static Color MenorColorLibre (EstadoNetwork *estado, u32 N)
{
	Color c = 0;
	Color *usedColors = NULL;
	short d, i;
	node_t vert;
	u32 vecino;
	edge_t *edge = NULL;
	
	vert = estado->nodes[N];
	
	/* La heurística aplicada exige el uso de calloc */
	usedColors = (Color *) calloc (estado->colores + 1, sizeof (Color));
	
	/* Registramos los colores de los vecinos hacia adelante */
	d = el_get_size (vert.forwardList);
	for (i = 0 ; i < d ; i++) {
		edge = el_get_actual (vert.forwardList);
		usedColors[edge->nodeDest.color]++; /* Registramos el color hallado */
		el_avance (vert.forwardList);
	}
	
	/* Registramos los colores de los vecinos hacia atrás */
	d = el_get_size (vert.backwardList);
	for (i = 0 ; i < d ; i++) {
		edge = el_get_actual (vert.backwardList);
		usedColors[edge->nodeOrig.color]++; /* Registramos el color hallado */
		el_avance (vert.backwardList);
	}
	
	/* Llevamos el índice 'i' hasta la menor posición libre */
	for (i = 1 ; (i < estado->colores) && usedColors[i] ; i++);
	/* (el color 0 no existe) */
	
#ifdef __DEBUG
	if (HayConflicto (estado, N)) {
		   fprintf (stderr, "Se generó un conflicto al buscar un "
				   "color para el vértice %u\n", N);
		   fprintf (stderr, "Se le otorgó el color %d\n", (int) i);
	}
#endif
	
	return i;
}



/* Estudia la lista de aristas conflictivas de (estado) para ir
 * resolviendo los conflictos de color uno por uno.
 * Básicamente es una corrida de Greedy restringida a los nodos
 * de las aristas conflictivas
 * Actualiza el EstadoNetwork para reflejar el resultado.
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
			c = MenorColorLibre (estado, v1);
			estado->nodes[v1].color = c;
		} else {
			c = MenorColorLibre (estado, v2);
			estado->nodes[v2].color = c;
		}
		
		if (estado->colores < c)
			estado->colores = c;
		if (K < c)
			K = c;
		
		el_avance (estado->l_con);
	}
	
	return K;
}

