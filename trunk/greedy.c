#include "edge_list.h"


INLINE Color min_free_color(node_t node, node_t * nodes , Color max_color)
{
	
	unsigned short i= 0;
	unsigned short size = 0; 
	Color *colors = NULL;
	
	/* Pre */
	ASSERT(nodes != NULL)

	/* Creo el arreglo de los colores actuales */
	colors = calloc(maxcolor + 1, sizeof(Color));

	/* Obtengo los colores de los vecinos forward */
	size = el_get_size(node.forwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual(node.forwardList);
		colors[nodes[edge->nodeDest].colour]++;
		el_avance(node.forwardList);
	}

	/* Obtengo los colores de los vecinos backward */
	size = el_get_size(node.backwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual(node.backwardList);
		colors[nodes[edge->nodeOrig].colour]++;
		el_avance(node.backwardList);
	}
	
	/* Buscando el minimo color no usado */
	for (i = 1; (i <= maxcolor) && colors[i]; i++);
	node->colour = (Color) i;

	/* Destruyo la lista de colores */
	free(colors);
	colors = NULL;

	return ((i > maxcolor) ? i : maxcolor);
}  

Color color_greedy (node_t * nodes, int size)
{
	int i = 0;
	Color max_color = 1;

	for(i = 0; i < size; i++ ){
		nodes[i].colour = min_free_color(i, nodes, max_color);
		if(nodes[i].colour > max_color) max_color = nodes[i].colour;
	}

	return max_color;
}


