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
	tripleList_t * list = (tripleList_t *) malloc (sizeof (struct s_tripleList));
	/* cochinada nos asegura un invariante y muchos chequeos */
	struct tripleCeld * celd = (struct tripleCeld *) malloc (sizeof (struct tripleCeld));
	ASSERT (list != NULL)
	
	list->first.next = celd;
	celd->next = NULL;
	celd->pparent = celd;
	list->prev =  &(list->first);
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
void tl_initialize (tripleList_t * tl, u32 indexNode)
{
	ASSERT (tl != NULL)
	
	tl->size = 0;
	tl->prev = tl->plast = &(tl->first);
	tl->first.node = indexNode;
	tl->first.pparent = NULL;
	
}

/*! ~~~~~~~~~~~~  Funciones para obtener elementos ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que obtiene el nodo actual (NOTE:indice del nodo actual)
	REQUIRES:
		tl != NULL
	RETURNS:
		indice
*/
u32 tl_get_actual_node (tripleList_t * tl)
{
	ASSERT (tl != NULL)
	ASSERT (tl->size >= 1)
	return tl->prev->next->node;
}

/* Funcion que obtiene el el flujo actual 
	REQUIRES:
		tl != NULL
	RETURNS:
		flow
*/
u32 tl_get_actual_flow (tripleList_t * tl)
{
	ASSERT (tl != NULL)
	return tl->prev->next->flow;
}


/* Funcion que devuelve el tamaño de la lista
 * NOTE: si tl == NULL ==> size = 0
*/
short tl_get_size (tripleList_t * tl)
{
	if (tl == NULL)
		return 0;
	return tl->size;
}



/*! ~~~~~~~~~~~~~~~~  Funciones de "movimientos" ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que avanza el visor al siguiente elemento
 * Si esta en el ultimo elemento no avanzamos.
 *	REQUIRES:
 *		tl != NULL
 *	RETURNS:
 *		0, si avanzamos normalmente
 *		1, si estamos al final de la cola
 */
int tl_avance (tripleList_t * tl)
{
	ASSERT (tl != NULL)
			
	if (tl->prev->next->next == NULL)
		return 1;
	else {
		tl->prev = tl->prev->next;
		return 0;
	}
}


/* Funcion que mueve el visor al padre del elemento actual
	REQUIRES:
		el != NULL
*/
void tl_go_parent (tripleList_t * tl)
{
	ASSERT (tl != NULL)
	tl->prev = tl->prev->next->pparent;
}


/* Funcion que mueve el visor al comienzo de la lista
	REQUIRES:
		el != NULL
*/
void tl_start (tripleList_t * tl)
{
	ASSERT (tl != NULL)
	tl->prev = tl->plast = &(tl->first);
}




/* Funcion que mueve el actual al final de la lista
REQUIRES:
el != NULL
NOTE: cuando terminamos t se encuentra en el ultimo lugar, primero debemos
avanzar el "visor" (actual) al final.
*/
void tl_move_last (tripleList_t * tl)
{
	ASSERT (tl != NULL)
	tl->prev = tl->plast;
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
	struct tripleCeld * celd;
	/* pre */
	ASSERT (tl != NULL)
	ASSERT (indexNode <= MAX_N_NODES)
	
	tl->size++;
	/* tenemos 2 casos posibles, que exista una celda o que no exista, si
	 * existe la celda entonces solo la usamos, si no la creamos */
	/* seteamos el flow */
	if (tl->plast->next->next != NULL) {
		celd = tl->plast->next->next;
		
	} else {
		celd = (struct tripleCeld *) malloc (sizeof (struct tripleCeld));
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

