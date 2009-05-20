#include "edge_list.h"


/* vamos a definir el tipo celda para la lista */
struct edgeCeld {
	struct edgeCeld * next;
	edge_t edge;		/* no lo definimos como puntero por "eficiencia" */
	unsigned int size;
}


struct s_edgeList {
	struct edgeCeld first;		/* celda dummy */
	struct edgeCeld * actual;	/* el visor, en realidad es el anterior */
	struct edgeCeld * si;		/* el puntero al "anterior" del SI */
	struct edgeCeld * no;		/* el puntero al "anterior" del NO */
};



edgeList_t * el_create (void)
{
	edgeList_t * list = (edgeList_t) calloc (1, sizeof (struct s_edgeList));
	list->size = 0;

/* destructor 
REQUIRES:
el != NULL
*/
void el_destroy (edgeList_t * el);


/* Funcion que obtiene el edge acutal al que actualmente la lista 
REQUIRES:
el != NULL
RETURNS:
NULL 	si no hay elemento
edge 	cc
*/
edge_t * el_get_actual (edgeList_t * el);

/* Funcion que agrega un elemento al edge_list. Vamos a usar estructuras fijas,
* NO dinamicas (por eficiencia...) 
REQUIRES:
el	!= NULL
n	!= NULL
*/
void el_add_edge (edgeList_t * el, unsigned int flow, unsigned int capacity, node_t * n);
/*NOTE:la misma que antes solo que inicializa el flow en 0 */
void el_add_edge_no_flow (edgeList_t * el,  unsigned int capacity, node_t * n);


/* Funcion que devuelve el tamaño de la lista, osea delta
REQUIRES:
el != NULL
*/
unsigned int el_get_size (edgeList_t * el);


/* Funcion que manda el edge actual de la parte SI a la parte NO
REQUIRES:
el != NULL
*/
void el_swap_to_si_edge (edgeList_t * el);


/* Funcion que manda el edge actual de la parte NO a la parte SI
REQUIRES:
el != NULL
*/
void el_swap_to_no_edge (edgeList_t * el);




#endif
