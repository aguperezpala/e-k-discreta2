#include "edge_list.h"


/* vamos a definir el tipo celda para la lista */
struct edgeCeld {
	struct edgeCeld * next;
	edge_t* edge;		/* no lo definimos como puntero por "eficiencia" */
};


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
		edge	!= NULL
*/
INLINE void el_add_edge (edgeList_t * el,  edge_t * edge);
{
	struct edgeCeld * celd = (struct edgeCeld *) malloc (sizeof (struct edgeCeld));
	/* pre */
	ASSERT (el != NULL)
	ASSERT (edge != NULL)
	
	el->size++;
	
	celd->edge = edge;
	celd->next = el->prev->next;
	el->prev->next = celd;
}


/* Funcion que devuelve el tamaño de la lista, osea delta
*/
INLINE short el_get_size (edgeList_t * el)
{
	if (el == NULL)
		return 0;
	return el->size;
}



/* Funcion que sirve para eliminar el elemento actual
REQUIRES:
el != NULL
el_get_size (el) >= 1
*/
INLINE void el_del_edge (edgeList_t * el)
{
	struct edgeCeld * celd;
	
	/* pres */
	ASSERT (el != NULL)
	ASSERT (el->size >= 1)
	
	
	/* actualizamos los punteros */
	celd = el->prev->next;
	el->prev->next = celd->next;
	
	/* liberamos el edge */
	ASSERT (el->prev->next->edge != NULL)
	free (celd->edge);
	/* liberamos la celda */
	free (celd);
}

/* Funcion que avanza al siguiente elemento, si esta en el ultimo elemento
* entonces el "visor" vuelve al comienzo. (una especie de lista circular)
REQUIRES:
el != NULL
*/
INLINE void el_avance (edgeList_t * el)
{
	
	/* pres */
	ASSERT (el != NULL);
	
	if (el->prev->next == NULL)
		/* debemos empezar del principio */
		el->prev = &(el->first);
	else
		/* avanzamos asi nomas */
		el->prev = el->prev->next;

}


