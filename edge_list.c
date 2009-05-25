#include "edge_list.h"


/* vamos a definir el tipo celda para la lista */
struct edgeCeld {
	struct edgeCeld * next;
	edge_t* edge;		/* no lo definimos como puntero por "eficiencia" */
}


struct s_edgeList {
	struct edgeCeld first;		/* celda dummy */
	struct edgeCeld * prev; 	/* el visor, en realidad es el anterior */
	short size;
};



INLINE edgeList_t * el_create (void)
{
	edgeList_t * list = (edgeList_t) malloc (sizeof (struct s_edgeList));
	
	ASSERT (list != NULL)
	
	list->prev = list->first.next = NULL;
	list->size = 0;
	
	return list;
}
	

/* destructor cuando la lista era dinámica
REQUIRES:
el != NULL
*/
INLINE void el_dinamic_destroy (edgeList_t * el)
{
	struct edgeCeld * aux = NULL;
	struct edgeCeld * delCeld = NULL;
	
	ASSERT (el != NULL)
	
	aux = el->first.next;
	/* borramos todas las celdas */
	while (aux != NULL){
		delCeld = aux;
		aux = aux->next;
		free(delCeld);
	}
	/* borramos la estructura */
	free (el);
}

/* destructor cuando la lista era estática
REQUIRES:
el != NULL
*/
INLINE void el_normal_destroy (edgeList_t * el)
{
	struct edgeCeld * aux = NULL;
	struct edgeCeld * delCeld = NULL;
	
	ASSERT (el != NULL)
	
	aux = el->first.next;
	/* borramos todas las celdas */
	while (aux != NULL){
		delCeld = aux;
		aux = aux->next;
		free(delCeld);
	}
}

/* Funcion que obtiene el edge acutal al que actualmente apunta la lista 
REQUIRES:
el != NULL
RETURNS:
NULL 	si no hay elemento
edge 	cc
*/
INLINE edge_t * el_get_actual (edgeList_t * el)
{
	ASSERT (el != NULL)
	return el->prev->next->edge;
}


/* Funcion que agrega un elemento al edge_list "el" del nodo "n".
 * Vamos a usar estructuras fijas, NO dinamicas (por eficiencia...).
 * Agregamos al comienzo de la lista "SI"
 * Inicializa el flujo en 0
	REQUIRES:
		el	!= NULL
		n	!= NULL
*/
INLINE void el_add_edge (edgeList_t * el,  u32 capacity, node_t * n);
{
	struct edgeCeld * celd = (struct edgeCeld *) malloc (sizeof (struct edgeCeld));
	/* pre */
	ASSERT (el != NULL)
	ASSERT (n != NULL)
	
	el->size++;
	celd->edge.capacity = capacity;
	celd->edge.node = n;
	celd->edge.flow = 0;
	
	/* ahora lo agregamos a la lista, comienzo de si */
	celd->next = el->si->next;
	el->si->next = celd;
}


/*NOTE:la misma que antes solo que inicializa el flow en "flow" */
INLINE void el_add_edge_with_flow (edgeList_t * el, u32 flow, u32 capacity, node_t * n);
{
	struct edgeCeld * celd = (struct edgeCeld *) malloc (sizeof (struct edgeCeld));
	/* pre */
	ASSERT (el != NULL)
	ASSERT (n != NULL)
	
	el->size++;
	/*! estamos accediendo de forma directa a la estructura... verificar como
	 * arreglar esto */
	celd->edge.flow = flow;
	celd->edge.capacity = capacity;
	celd->edge.node = n;
	
	/* ahora lo agregamos a la lista, comienzo de si */
	celd->next = el->si->next;
	el->si->next = celd;
}

	
	


/* Funcion que devuelve el tamaño de la lista, osea delta
REQUIRES:
el != NULL
*/
unsigned int el_get_size (edgeList_t * el)
{
	ASSERT (el != NULL)
	return el->size;
}
