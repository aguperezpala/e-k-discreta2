#include "edge_list.h"


/* vamos a definir el tipo celda para la lista */
struct edgeCeld {
	struct edgeCeld * next;
	edge_t* edge;		/* no lo definimos como puntero por "eficiencia" */
};


struct s_edgeList {
	struct edgeCeld first;		/* celda dummy */
	struct edgeCeld * prev; 	/* el visor, en realidad es el anterior */
	unsigned short size;
};



edgeList_t * el_create (void)
{
	edgeList_t * list = (edgeList_t *) calloc (1, sizeof (struct s_edgeList));
	
	ASSERT (list != NULL)
	
	list->first.next = NULL;
	list->prev = &(list->first);
	list->size = 0;
	
	return list;
}
	

/* destructor cuando la lista era dinámica
	REQUIRES:
		el != NULL
*/
void el_dinamic_destroy (edgeList_t * el)
{
	struct edgeCeld * aux = NULL;
	struct edgeCeld * delCeld = NULL;
	
	ASSERT (el != NULL)
	
	aux = el->first.next;
	/* borramos todas las celdas */
	while (aux != NULL){
		free (aux->edge);
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
void el_normal_destroy (edgeList_t * el)
{
	struct edgeCeld * aux = NULL;
	struct edgeCeld * delCeld = NULL;
	
	ASSERT (el != NULL)
	
	aux = el->first.next;
	/* borramos todas las celdas */
	while (aux != NULL){
		free (aux->edge);
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
		edge 	caso contrario
*/
edge_t * el_get_actual (edgeList_t * el)
{
	ASSERT (el != NULL)
	ASSERT (el->size >= 1)
	return el->prev->next->edge;
}


/* Funcion que agrega un elemento al edge_list "el" del nodo "n".
 * Vamos a usar estructuras fijas, NO dinamicas (por eficiencia...).
 * Inicializa el flujo en 0
	REQUIRES:
		el	!= NULL
		edge	!= NULL
*/
void el_add_edge (edgeList_t * el,  edge_t * edge)
{
	struct edgeCeld * celd = (struct edgeCeld *) calloc (1, sizeof (struct edgeCeld));
	/* pre */
	ASSERT (el != NULL)
	ASSERT (edge != NULL)
	
	el->size++;
	
	celd->edge = edge;
	celd->next = el->prev->next;
	el->prev->next = celd;
}


/* Funcion que devuelve el tamaño de la lista */
short el_get_size (edgeList_t * el)
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
void el_del_edge (edgeList_t * el)
{
	struct edgeCeld * celd = NULL;
	
	/* pres */
	ASSERT (el != NULL)
	ASSERT (el->size >= 1)
	
	el->size--;
	/* actualizamos los punteros */
	celd = el->prev->next;
	el->prev->next = celd->next;
	
	/* liberamos el edge */
	if (celd->edge != NULL)
		free (celd->edge);
	/* liberamos la celda */
	free (celd);
}

/* Funcion que avanza al siguiente elemento, si esta en el ultimo elemento
 * entonces el "visor" vuelve al comienzo. (una especie de lista circular)
 *	REQUIRES:
 *		el != NULL
 *	RETURNS:
 *		0, si se avanzó normalmente
 *		1, si al avanzar volvimos al comienzo
 */
int el_avance (edgeList_t * el)
{
	
	/* pres */
	ASSERT (el != NULL)
	
	if (el->prev->next->next == NULL) {
		/* debemos empezar del principio */
		el->prev = &(el->first);
		return 1;
	} else {
		/* avanzamos asi nomas */
		el->prev = el->prev->next;
		return 0;
	}

}



/* Mueve el "visor" al primero elemento de la lista
 * 	REQUIRES:
 *		el != NULL
 */
void el_start (edgeList_t * el) {
	ASSERT (el != NULL);
	el->prev = &(el->first);
}
