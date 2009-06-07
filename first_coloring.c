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
bool HayConflicto (EstadoNetwork *estado, u32 node_i);

/* Dado un vértice 'N' busca el menor color aún libre entre sus vecinos
 *
 * PRE: estado != NULL && "existe el N-ésimo vértice de estado"
 * POS: el color hallado para N no genera conflictos con sus vecinos
 */
Color MenorColorLibre (EstadoNetwork *estado, u32 node_i);


bool HayConflicto (EstadoNetwork *estado, u32 node_i)
{
	unsigned short d, i;
	node_t vert;
	edge_t *edge = NULL;
	
	ASSERT (estado != NULL)
	
	vert = estado->nodes[node_i];

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


Color MenorColorLibre (EstadoNetwork *estado, u32 node_i)
{
	Color c = 0;
	Color *usedColors = NULL;
	unsigned short i;
	node_t vert;
	u32 vecino;
	
	vert = estado->nodes[node_i];
	
	/* Creo el arreglo de los colores actuales */
	usedColors = (Color *) calloc (estado->colores + 1, sizeof (Color));
	
	/* Registramos los colores de los vecinos forward */
	if (el_get_size(vert.forwardList) > 0){
		el_start (vert.forwardList);
		do{
			vecino = (el_get_actual (vert.forwardList))->nodeDest;
			c = estado->nodes[vecino].color;
			usedColors[c]++; /* Registramos el color hallado */
		}while(el_avance(vert.forwardList) == 0);
	}
	
	/* Registramos los colores de los vecinos backward */
	if (el_get_size(vert.backwardList) > 0){
		el_start (vert.backwardList);
		do{
			vecino = (el_get_actual(vert.backwardList))->nodeOrig;
			c = estado->nodes[vecino].color;
			usedColors[c]++; /* Registramos el color hallado */
		}while(el_avance(vert.backwardList) == 0);
	}
	
	/* Llevamos el índice 'i' hasta la menor posición libre */
	for (i = 1 ; (i <= estado->colores) && usedColors[i] ; i++);
	/* (el color 0 no existe) */
	
#ifdef __DEBUG
	if (HayConflicto (estado, node_i)) {
		   fprintf (stderr, "Se generó un conflicto al buscar un"
				    " color para el vértice %u\nSe le otorgó"
				    " el color %d\n", node_i, (int) i);
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
unsigned short ResolverConflictos (EstadoNetwork *estado)
{
	Color c = 0;  /* Nuevo color escogido para un nodo */
	u32 v1;  /* Vértice de origen  de un lado */
	u32 v2;  /* Vértice de destino de un lado */
	edge_t *edge;
	
	
	ASSERT (estado != NULL)
	
	if (el_get_size(estado->l_con) > 0){
		el_start (estado->l_con);
		do{
		
			edge = el_get_actual (estado->l_con);
			
			v1 = edge->nodeOrig;
			v2 = edge->nodeDest;

			/* ¡No había conflicto! */
			if (estado->nodes[v1].color != estado->nodes[v2].color) continue;
			
			/* Buscamos el vértice de menor grado, para otorgarle
			 * el menor color posible no-conflictivo */
			if (estado->nodes[v1].degree < estado->nodes[v2].degree) {
				c = MenorColorLibre (estado, v1);
				
				estado->nodes[v1].color = c;
			} else {
				c = MenorColorLibre (estado, v2);
				estado->nodes[v2].color = c;
			}
			
			estado->colores = max(estado->colores , c);
		
		}while(el_avance(estado->l_con) == 0);
	}
	
	return estado->colores;
}

