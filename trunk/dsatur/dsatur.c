#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "dsatur.h"
#include "debug.h"
#include "edge_list.h"

/* Funciones internas.
 * Duda : Conviene pasar el nodo o el indice del nodo ? */
Color min_color(node_t node , node_t * nodes , Color max);
void increase_satur(node_t node , node_t * nodes);
int equal_max_dsatur(struct alist_vert **heap);

/* Incrementa el grado de saturacion de todos los vecinos de node.
 */
void increase_satur(node_t node , node_t * nodes)
{
	short i = 0;
	short size = 0;
	edge_t * edge = NULL;

	/* Pre */
	ASSERT(node_array != NULL)
	
	/* Saturando los vecinos forward */
	size = el_get_size(node.forwardList);
	for(i=0 ; i < size ; i++){
		
		edge = el_get_actual(node.forwardList);
		node_array[edge->nodeDest].satur++;
		el_avance(node.forwardList);
	}

	/* Saturando los vecinos backward */
	size = el_get_size(node.backwardList);
	for(i=0 ; i < size ; i++){
		
		edge = el_get_actual(node.backwardList);
		node_array[edge->nodeOrig].satur++;
		el_avance(node.backwardList);
	}
}

/* Obtiene el menor color para el vertice , lo colorea con este y lo devuelve
 * Podemos evitar los realloc si nos aseguramos que max sea el mayor color
 * actual en el network.
 */
Color min_color(node_t node , node_t * nodes , Color max)
{
	Color max_color = max;
	unsigned short i= 0;
	unsigned short size = 0; 
	Color *colors = NULL;
	
	/* Pre */
	ASSERT(node_array != NULL)

	/* Creo el arreglo de los colores actuales */
	colors = calloc(maxcolor + 1, sizeof(Color));

	/* Obtengo los colores de los vecinos forward */
	size = el_get_size(node.forwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual(node.forwardList);
		
		if(node_array[edge->nodeDest].colour > max_color)
			maxcolor = node_array[edge->nodeDest].colour;

		colors[node_array[edge->nodeDest].colour]++;
		el_avance(node.forwardList);
	}

	/* Obtengo los colores de los vecinos backward */
	size = el_get_size(node.backwardList);
	for(i=0 ; i < size ; i++){
		edge = el_get_actual(node.backwardList);
		
		if(node_array[edge->nodeOrig].colour > max_color)
			maxcolor = node_array[edge->nodeOrig].colour;
			
		colors[node_array[edge->nodeOrig].colour]++;
		el_avance(node.backwardList);
	}
	
#ifdef DEBUG
	printf("maxcolor: %d\n", maxcolor);
	printf("colortab: ");
	for (i = 1; i <= maxcolor; i++) {
		printf("%d ", colors[i]);
	}
	printf("\n");
#endif

	/* Buscando el minimo color no usado */
	for (i = 1; (i <= maxcolor) && colors[i]; i++);
	node->colour = (Color) i;

#ifdef DEBUG
	printf("mincolor: %d\n", i);
#endif

	free(colors);

	if (i > maxcolor)
		return i;
	else 
		return maxcolor;
}

/* checking if there are vertices with equal max. saturation degree. Heap hack ;)
 * Vamos a tener que usar heap si o si.
 */
int equal_max_dsatur(struct alist_vert **heap)
{
	/* Pre */
	ASSERT( heap != NULL)
	
	return (heap[0]->dsatur == heap[left(0)]->dsatur || heap[0]->dsatur == heap[right(0)]->dsatur);
}

int dsatur(node_t node , node_t * nodes , short delta)
{

	int m, n, i, maxdeg, maxsatur, maxcolor = 1, heapsize, check_eq = 1;
	struct graph *graph;
	struct alist_vert **vertheap;


	/* (1) Arrange the vertices by decreasing order of degrees.
	 * In fact, I build a heap since I always need only max. degree or max.
	 * saturation degree
	 */

	vertheap = build_max_deg_heap(vertheap, heapsize);

	/* (2) Color a vertex of maximal degree with color 1. */

	vertex = extract_max_deg(vertheap, &heapsize);
	vertex->color = 1;
	dsatur(vertex);		/* changing saturation degree of adj. vertices */

	/* rebuilding heap (by saturation degree) */
	vertheap = build_max_dsatur_heap(vertheap, heapsize);

	/* (3) Choose a vertex with a maximal saturation degree.... */

	for (i = 2; i <= n; i++) {

	 	/* If there is an equality, choose any vertex of maximal degree in the
		 * uncolored subgraph.
		 */
		if (equal_max_dsatur(vertheap) && check_eq) {
			/* sad but true ;) rebuilding again...*/
			vertheap = build_max_deg_heap(vertheap, heapsize);	
			vertex = extract_max_deg(vertheap, &heapsize);
			/* (4) Color the chosen vertex with the least possible
			 * (lowest numbered) color.
			 */
			maxcolor = min_color(vertex, maxcolor);
			increase_satur(vertex);	/* changing saturation degree of adj. vertices */
			/* sad but true ;) rebuilding again...*/
			vertheap = build_max_dsatur_heap(vertheap, heapsize);	
		} else {
			vertex = extract_max_dsatur(vertheap, &heapsize);
			/* (4) Color the chosen vertex with the least possible (lowest numbered) color.*/
			maxcolor = min_color(vertex, maxcolor);
			increase_satur(vertex);	/* changing saturation degree of adj. vertices */
		}
		/* (5) If all the vertices are colored, stop. Otherwise, return to 3.  */
	}

	printf("maxcolor %d\n", maxcolor);

	free(graph);
	free(vertheap);
	freelist(adjlist, n);
	return 0;
}


