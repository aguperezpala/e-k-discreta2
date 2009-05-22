#include "edge_list.h"


/* vamos a definir el tipo celda para la lista */
struct edgeCeld {
	struct edgeCeld * next;
	edge_t edge;		/* no lo definimos como puntero por "eficiencia" */
}


struct s_edgeList {
	struct edgeCeld first;		/* celda dummy */
	struct edgeCeld * prev; 	/* el visor, en realidad es el anterior */
	struct edgeCeld * si;		/* el puntero al "anterior" del SI,
	 				   es el comienzo de la lista */
	struct edgeCeld * no;		/* el puntero al "anterior" del NO */
	short size;
};



INLINE edgeList_t * el_create (void)
{
	edgeList_t * list = (edgeList_t) malloc (sizeof (struct s_edgeList));
	/*! en teoria calloc rellena todo con 0 (size = 0)*/
	ASSERT (list != NULL)
	
	list.prev = &list.first;
	list.si = list.prev;
	list.no = list.prev;
	list.size = 0;
	
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
	return &(el->prev->next.edge);
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


/* Funcion que manda el edge actual de la parte SI a la parte NO
REQUIRES:
el != NULL
*/
void el_swap_to_si_edge (edgeList_t * el)
{
	struct edgeCeld * aux;
	
	ASSERT (el != NULL)
	
	/* hacemos el "swap" */
	aux = el->actual->next;
	/*! debemos tener en cuenta que el visor nunca se puede caer (ser null) */
	el->actual->next = aux->next;
	aux->next = el->si->next;
	el->si->next = aux;
}


/* Funcion que manda el edge actual de la parte NO a la parte SI
REQUIRES:
el != NULL
*/
void el_swap_to_no_edge (edgeList_t * el)
{
	struct edgeCeld * aux;
	ASSERT (el != NULL)
	
	/* hacemos el "swap" */
	aux = el->actual->next;
	/*! debemos tener en cuenta que el visor nunca se puede caer (ser null) */
	el->actual->next = aux->next;
	aux->next = el->no->next;
	el->no->next = aux;
}


/* Funcion que obtiene un elemento de la lista "NO"
REQUIRES:
el != NULL
RETURNS:
NULL si no hay elemento
edget_t * si existe
*/
edge_t * el_get_no_edge (edgeList_t * el)
{
	ASSERT (el != NULL)
	return &(el->no->next.edge);
}


/* Funcion que obtiene un elemento de la lista "SI"
REQUIRES:
el != NULL
RETURNS:
NULL si no hay elemento
edget_t * si existe
*/
edge_t * el_get_si_edge (edgeList_t * el)
{
	ASSERT (el != NULL)
	return &(el->si->next.edge);
}

/* Funcion que manda el primero de la lista NO a la lista SI (lo pone al principio
* de la lista SI)
REQUIRES:
el != NULL
exista elemento en NO
*/
void el_send_no_to_si (edgeList_t * el)
{
	struct edgeCeld * aux;
	
	ASSERT (el != NULL)
	
	/* hacemos el "swap" */
	/* NOTE: podriamos hacerlo mas eficiente metiendolo como precondicion
	 * alomejor... (si es que no habria que chequearlo arriba */
	if ((aux = el->no->next) != NULL){
		/*! debemos tener en cuenta que el visor nunca se puede caer (ser null) */
		el->no->next = aux->next;
		aux->next = el->si->next;
		el->si->next = aux;
	}
}


/* Funcion que manda el primero de la lista SI a la lista NO (lo pone al principio
* de la lista NO)
REQUIRES:
el != NULL
exista elemento en SI
*/
void el_send_no_to_si (edgeList_t * el)
{
	struct edgeCeld * aux;
	
	ASSERT (el != NULL)
	
	/* hacemos el "swap" */
	/* NOTE: podriamos hacerlo mas eficiente metiendolo como precondicion
	* alomejor... (si es que no habria que chequearlo arriba */
	if ((aux = el->si->next) != NULL){
		/*! debemos tener en cuenta que el visor nunca se puede caer (ser null) */
		el->si->next = aux->next;
		aux->next = el->no->next;
		el->no->next = aux;
	}
}


/*! Funciones para chequear si las listas estan vacias (tienen la misma pre/pos)
REQUIRES:
el != NULL
RETURNS:
true 	si esta vacia
false 	caso contrario
*/
/* global list */
bool el_is_empty (edgeList_t * el)
{
	/* pre */
	ASSERT (el != NULL)
	return (el->size == 0);
}
/* SI list */
bool el_si_is_empty (edgeList_t * el)
{
	/* pre */
	ASSERT (el != NULL)
	return (el->si->next == NULL);
}
/* NO list */
bool el_no_is_empty (edgeList_t * el)
{
	/* pre */
	ASSERT (el != NULL)
	return (el->no->next == NULL);
}





#endif
