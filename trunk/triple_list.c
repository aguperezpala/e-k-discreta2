#include "triple_list.h"


/* vamos a definir el tipo celda para la lista */
struct tripleCeld {
	struct tripleCeld * next;
	struct tripleCeld * pparent;	/* puntero al anterior del padre */
	u32 node;			/* nodo actual */
	u32 flow;			/* flujo actual */
};


struct s_tripleList {
	struct tripleCeld first;	/* celda dummy */
	struct tripleCeld * prev; 	/* el visor, en realidad es el anterior */
	struct tripleCeld * plast;	/* ultima celda */
	short size;
};





/* Funcion que crea una lista (en caso de que usemos dinamica) 
 * constructor
 */
tripleList_t * tl_create (void)
{
	tripleList_t * list = (tripleList_t) malloc (sizeof (struct s_tripleList));
	
	ASSERT (list != NULL)
	
	list->prev = list->first.next = NULL;
	list->plast = list->prev;
	list->size = 0;
	
	return list;
}


/* destructor para la lista allocada dinamicamente
	REQUIRES:
		el != NULL
*/
void tl_dinamic_destroy (tripleList_t * tl)
{
	struct tripleCeld * aux = NULL;
	struct tripleCeld * delCeld = NULL;
	
	ASSERT (tl != NULL)
	
	aux = tl->first.next;
	/* borramos todas las celdas */
	while (aux != NULL){
		delCeld = aux;
		aux = aux->next;
		free(delCeld);
	}
	/* borramos la estructura */
	free (tl);
}


/* destructor para la lista NO allocada dinamicamente, osea practicamente libera
 * todas las celdas de la lista, menos la estructura misma de la celda
	REQUIRES:
		el != NULL
*/
void tl_normal_destroy (tripleList_t * tl)
{
	struct tripleCeld * aux = NULL;
	struct tripleCeld * delCeld = NULL;
	
	ASSERT (tl != NULL)
	
	aux = tl->first.next;
	/* borramos todas las celdas */
	while (aux != NULL){
		delCeld = aux;
		aux = aux->next;
		free(delCeld);
	}
}


/* Funcion para inicializar la lista
	REQUIRES:
		tl != NULL
NOTE: antes de cada corrida debemos inicializar la estructura 
*/
void tl_initialize (tripleList_t * tl)
{
	ASSERT (tl != NULL)
	tl->size = 0;
	tl->prev = tl->plast = &(tl->first);
}

/*! ~~~~~~~~~~~~  Funciones para obtener elementos ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que obtiene el nodo actual (NOTE:indice del nodo actual)
	REQUIRES:
		tl != NULL
	RETURNS:
		indice
*/
INLINE u32 tl_get_actual_node (tripleList_t * tl)
{
	ASSERT (tl != NULL)
	return tl->prev->next->node;
}

/* Funcion que obtiene el el flujo actual 
	REQUIRES:
		tl != NULL
	RETURNS:
		flow
*/
INLINE u32 tl_get_actual_flow (tripleList_t * tl)
{
	ASSERT (tl != NULL)
	return tl->prev->next->flow;
}


/* Funcion que devuelve el tamaño de la lista
 * NOTE: si tl == NULL ==> size = 0
*/
INLINE short tl_get_size (tripleList_t * tl);
{
	ASSERT (tl != NULL)
	return tl->size;
}



/*! ~~~~~~~~~~~~~~~~  Funciones de "movimientos" ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que avanza el visor al siguiente elemento, si esta en el ultimo elemento
 * entonces el "visor" vuelve al comienzo. (una especie de lista circular)
	REQUIRES:
		tl != NULL
*/
INLINE void tl_avance (tripleList_t * tl)
{
	ASSERT (tl != NULL)
	if (tl->prev->next == NULL)
		tl->prev = &(tl->first);
	else
		tl->prev = tl->prev->next;
}


/* Funcion que mueve el visor al padre del elemento actual
	REQUIRES:
		el != NULL
*/
INLINE void tl_go_parent (tripleList_t * tl)
{
	ASSERT (tl != NULL)
	tl->prev = tl->prev->pparent;
}


/* Funcion que mueve el visor al comienzo de la lista
	REQUIRES:
		el != NULL
*/
INLINE void tl_start (tripleList_t * tl);
{
	ASSERT (tl != NULL)
	tl->prev = tl->plast = &(tl->first);
}


/*! ~~~~~~~~~~~~~~~~  Funciones de agregado/quitado ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que agrega una tripleta (nodo, padre, flow).
 NOTE: tener en cuenta que el padre va a ser el elemento actual
	REQUIRES:
		tl		!= NULL
		indexNode	<= MAX_N_NODES
*/
void tl_add_triple (tripleList_t * tl,  u32 flow, u32 indexNode)
{	
	/* pre */
	ASSERT (tl != NULL)
	ASSERT (indexNode <= MAX_N_NODES)
	
	tl->size++;
	/* tenemos 2 casos posibles, que exista una celda o que no exista, si
	 * existe la celda entonces solo la usamos, si no la creamos */
	/* seteamos el flow */
	if (tl->plast->next->next != NULL) {
		struct tripleCeld * celd = tl->plast->next;
		
	} else {
		struct tripleCeld * celd = (struct tripleCeld *) malloc (sizeof (struct tripleCeld));
		celd->next = NULL;
		tl->plast->next->next = celd;
	}
	
	
	/* seteamos el nodo y el flow*/
	celd->node = indexNode;
	celd->flow = flow;
	
	/* ahora seteamos el parent, en realidad el pparent */
	celd->pparent = tl->prev;
	
	/* actualizamos el ultimo puntero */
	tl->plast = tl->plast->next;
}

