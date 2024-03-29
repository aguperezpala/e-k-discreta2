#include <stdbool.h>
#include "consts.h"
#include "edge_list.h"
#include "greedy.h"
#include "node_stack.h"


Color greedy_max_color = 0;

bool color_propio(u32 node_i , node_t * nodes)
{
	edge_t *edge = NULL;

	/* Pre */
	ASSERT(nodes != NULL)
	ASSERT(greedy_max_color >= 0)
	
	/* Chequeo los colores de los vecinos forward */
	if (el_get_size(nodes[node_i].forwardList) > 0){
		el_start (nodes[node_i].forwardList);
		do{
			edge = el_get_actual(nodes[node_i].forwardList);
			if ( nodes[edge->nodeDest].corrida == nodes[node_i].corrida )
				if (nodes[edge->nodeDest].color == nodes[node_i].color) return false;
		}while(el_avance(nodes[node_i].forwardList) == 0);
	}
	
	/* Chequeo los colores de los vecinos backward */
	if (el_get_size(nodes[node_i].backwardList) > 0){
		el_start (nodes[node_i].backwardList);
		do{
			edge = el_get_actual (nodes[node_i].backwardList);
			if ( nodes[edge->nodeOrig].corrida == nodes[node_i].corrida )
				if (nodes[edge->nodeOrig].color == nodes[node_i].color) return false;
		}while(el_avance(nodes[node_i].backwardList) == 0);
	}
	return true;
}

/* Dado un nodo busca el menor color aún libre entre sus vecinos
 *
 * PRE: nodes != NULL && max_color < 0
 * POS: color_propio(node, nodes) && retorna el mayor color usado.
 */
void coloring_node(u32 node_i, node_t * nodes )
{
	register unsigned short i = 0;
	Color *colors = NULL;
	edge_t *edge = NULL;
	
	/* Pre */
	ASSERT(nodes != NULL)
	ASSERT(greedy_max_color >= 0)

	nodes[node_i].corrida++;
	
	/* Creo el arreglo de los colores actuales */
	colors = (Color *) calloc ( (greedy_max_color ) + 1, sizeof(Color));

	/* Obtengo los colores de los vecinos forward */
	if (el_get_size(nodes[node_i].forwardList) > 0){
		el_start (nodes[node_i].forwardList);
		do{
			edge = el_get_actual (nodes[node_i].forwardList);
			if ( nodes[edge->nodeDest].corrida == nodes[node_i].corrida )
				colors[(nodes[edge->nodeDest].color)]++;
		}while(el_avance(nodes[node_i].forwardList) == 0);
	}
	
	/* Obtengo los colores de los vecinos backward */
	if (el_get_size(nodes[node_i].backwardList) > 0){
		el_start (nodes[node_i].backwardList);
		do{
			edge = el_get_actual (nodes[node_i].backwardList);
			if ( nodes[edge->nodeOrig].corrida == nodes[node_i].corrida)
				colors[(nodes[edge->nodeOrig].color)]++;
		}while(el_avance(nodes[node_i].backwardList) == 0);
	}
	
	/* Buscando el minimo color no usado */

	for (i = 1; (i <= greedy_max_color) && colors[i]; i++);
	nodes[node_i].color = (Color) i;

	/* Destruyo la lista de colores */
	free (colors);
	colors = NULL;


#ifdef __DEBUG
	if (!color_propio(node_i, nodes)) {
		   fprintf (stderr, "Se generó un conflicto al buscar un"
				    " color para el vértice %u\nSe le otorgó"
				    " el color %d\n", node_i, (int) i);
	}
#endif

	greedy_max_color = max(nodes[node_i].color, greedy_max_color);
}  

Color color_greedy (node_s node_stack , node_t * nodes)
{
	greedy_max_color = 0;
	
	ns_cmd (node_stack, nodes, coloring_node);
	
	return greedy_max_color;
}


