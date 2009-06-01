#include <stdbool.h>
#include "consts.h"
#include "edge_list.h"
#include "greedy.h"
#include "node_stack.h"

extern Color greedy_max_color = 0;

static bool color_propio(node_t node, node_t * nodes)
{
	unsigned short i= 0;
	unsigned short size = 0;
	edge_t *edge = NULL;

	/* Pre */
	ASSERT(nodes != NULL)

	/* Chequeo los colores de los vecinos forward */
	size = el_get_size (node.forwardList);
	if (size > 0) el_start (node.forwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual (node.forwardList);
		if (nodes[edge->nodeDest].color == node.color)
			return false;
		el_avance (node.forwardList);
	}

	/* Chequeo los colores de los vecinos backward */
	size = el_get_size (node.backwardList);
	if (size > 0) el_start (node.backwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual (node.backwardList);
		if (nodes[edge->nodeOrig].color == node.color)
			return false;
		el_avance (node.backwardList);
	}

	return true;
}

/* Dado un el nodo busca el menor color aún libre entre sus vecinos
 *
 * PRE: nodes != NULL && max_color < 0
 * POS: color_propio(node, nodes) && retorna el mayor color usado.
 */
static Color coloring_node(node_t node, node_t * nodes)
{
	unsigned short i= 0;
	unsigned short size = 0; 
	Color *colors = NULL;
	edge_t *edge = NULL;
	
	/* Pre */
	ASSERT(nodes != NULL)
	ASSERT(greedy_max_color < 0)

	/* Creo el arreglo de los colores actuales */
	colors = (Color *) calloc ( (greedy_max_color*(-1) ) + 1, sizeof(Color));

	/* Obtengo los colores de los vecinos forward */
	size = el_get_size (node.forwardList);
	if (size > 0) el_start (node.forwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual (node.forwardList);
		if ( nodes[edge->nodeDest].color < 0 )
			colors[(nodes[edge->nodeDest].color*(-1))]++;
		el_avance (node.forwardList);
	}

	/* Obtengo los colores de los vecinos backward */
	size = el_get_size (node.backwardList);
	if (size > 0) el_start (node.backwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual (node.backwardList);
		if ( nodes[edge->nodeOrig].color < 0 )
			colors[(nodes[edge->nodeOrig].color*(-1))]++;
		el_avance (node.backwardList);
	}
	
	/* Buscando el minimo color no usado */
	for (i = 1; (i <= max_color) && colors[i]; i++);
	node.color = (Color) -i;

	/* Destruyo la lista de colores */
	free (colors);
	colors = NULL;

	/* Pos */
	ASSERT(color_propio(node, nodes))

	greedy_max_color = (node.color < greedy_max_color) ? node.color : greedy_max_color;
}  

Color color_greedy (node_s node_stack , node_t * nodes)
{
	int i = 0;
	Color max_color = -1;

	
		 coloring_node (nodes[i], nodes, max_color);
	
	return last_color;
}


