#include "greedy.h"
#include "edge_list.h"
#include <stdbool.h>

bool color_propio(node_t node, node_t * nodes)
{
	unsigned short i= 0;
	unsigned short size = 0;

	/* Chequeo los colores de los vecinos forward */
	size = el_get_size(node.forwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual(node.forwardList);
		if (nodes[edge->nodeDest].color == node.color)
			return false;
		el_avance(node.forwardList);
	}

	/* Chequeo los colores de los vecinos backward */
	size = el_get_size(node.backwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual(node.backwardList);
		if (nodes[edge->nodeOrig].color == node.color)
			return false;
		el_avance(node.backwardList);
	}

	return true;
}


Color min_free_color(node_t node, node_t * nodes , Color max_color)
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
		colors[nodes[edge->nodeDest].color]++;
		el_avance(node.forwardList);
	}

	/* Obtengo los colores de los vecinos backward */
	size = el_get_size(node.backwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual(node.backwardList);
		colors[nodes[edge->nodeOrig].color]++;
		el_avance(node.backwardList);
	}
	
	/* Buscando el minimo color no usado */
	for (i = 1; (i <= max_color) && colors[i]; i++);
	node.color = (Color) i;

	/* Destruyo la lista de colores */
	free(colors);
	colors = NULL;

	/* Pos */
	ASSERT(color_propio(node, nodes));

	return ((i > max_color) ? i : max_color);
}  

Color color_greedy (node_t * nodes, int size)
{
	int i = 0;
	Color max_color = 1;

	for(i = 0; i < size; i++ ){
		nodes[i].color = min_free_color(i, nodes, max_color);
		if(nodes[i].color > max_color) max_color = nodes[i].color;
	}

	return max_color;
}


