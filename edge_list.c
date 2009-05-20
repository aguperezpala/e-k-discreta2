#include "edge_list.h"


/* vamos a definir el tipo celda para la lista */
struct edgeCeld {
	struct edgeCeld * next;
	edge_t edge;		/* no lo definimos como puntero por "eficiencia" */
}


struct s_edgeList {
	struct edgeCeld first;		/* celda dummy */
	struct edgeCeld * actual;	/* el visor, en realidad es el anterior */
	struct edgeCeld * si;		/* el puntero al "anterior" del SI */
	struct edgeCeld * no;		/* el puntero al "anterior" del NO */
	unsigned int size;
};



edgeList_t * el_create (void)
{
	edgeList_t * list = (edgeList_t) calloc (1, sizeof (struct s_edgeList));
	/*! en teoria calloc rellena todo con 0 (size = 0)*/
	list->actual = list->first;
	list->si = list->first;
	list->no = list->first;
	
	return list;
}
	

/* destructor 
REQUIRES:
el != NULL
*/
void el_destroy (edgeList_t * el)
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


void el_normal_destroy (edgeList_t * el)
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

/* Funcion que obtiene el edge acutal al que actualmente la lista 
REQUIRES:
el != NULL
RETURNS:
NULL 	si no hay elemento
edge 	cc
*/
edge_t * el_get_actual (edgeList_t * el)
{
	ASSERT (el != NULL)
	return el->actual.edge;
}

/* Funcion que agrega un elemento al edge_list. Vamos a usar estructuras fijas,
* NO dinamicas (por eficiencia...) 
REQUIRES:
el	!= NULL
n	!= NULL
*/
void el_add_edge (edgeList_t * el, unsigned int flow, unsigned int capacity, node_t * n)
{
	struct edgeCeld * celd = (struct edgeCeld *) calloc (1,sizeof (struct edgeCeld));
	struct edgeCeld * aux;	/* no inicializamos pa ahorrar 1 instruccion xD */
	/* pre */
	ASSERT (el != NULL)
	ASSERT (n != NULL)
	
	/*! estamos accediendo de forma directa a la estructura... verificar como
	 * arreglar esto */
	celd->edge.flow = flow;
	celd->edge.capacity = capacity;
	
	/* ahora lo agregamos a la lista, comienzo de si */
	aux = el->si->next;
	celd->next = aux;
	el->si->next = celd;
}

	
	
	
/*NOTE:la misma que antes solo que inicializa el flow en 0 */
void el_add_edge_no_flow (edgeList_t * el,  unsigned int capacity, node_t * n)
{
	struct edgeCeld * celd = (struct edgeCeld *) calloc (1,sizeof (struct edgeCeld));
	struct edgeCeld * aux;	/* no inicializamos pa ahorrar 1 instruccion xD */
	/* pre */
	ASSERT (el != NULL)
	ASSERT (n != NULL)
	
	/*! estamos accediendo de forma directa a la estructura... verificar como
	* arreglar esto */
	celd->edge.capacity = capacity;
	
	/* ahora lo agregamos a la lista, comienzo de si */
	aux = el->si->next;
	celd->next = aux;
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
	ASSERT (el != NULL);
	
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
	ASSERT (el != NULL);
	
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
edge_t * el_get_no_edge (edgeList_t * el);


/* Funcion que obtiene un elemento de la lista "SI"
REQUIRES:
el != NULL
RETURNS:
NULL si no hay elemento
edget_t * si existe
*/
edge_t * el_get_si_edge (edgeList_t * el);


/* Funcion que manda el primero de la lista NO a la lista SI (lo pone al principio
* de la lista SI)
REQUIRES:
el != NULL
exista elemento en NO
*/
void el_send_no_to_si (edgeList_t * el);


/* Funcion que manda el primero de la lista SI a la lista NO (lo pone al principio
* de la lista NO)
REQUIRES:
el != NULL
exista elemento en SI
*/
void el_send_no_to_si (edgeList_t * el);




#endif
