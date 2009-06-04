#include "quad_list.h"
#include <stdbool.h>

/* vamos a definir el tipo celda para la lista */
struct quadCeld {
	struct quadCeld * next;
	struct quadCeld * pparent;	/* puntero al anterior del padre */
	u32 node;			/* nodo actual */
	u32 flow;			/* flujo actual */
	edge_t * edge;		/* arista que puso al nodo */
};


struct s_quadList {
	struct quadCeld first;	/* celda dummy */
	struct quadCeld * prev; 	/* el visor, en realidad es el anterior */
	struct quadCeld * plast;	/* ultima celda */
	short size;
};





/* Funcion que crea una lista (en caso de que usemos dinamica) 
 * constructor
 */
quadList_t * qt_create (void)
{
	quadList_t * list = (quadList_t *) malloc (sizeof (struct s_quadList));
	/* cochinada nos asegura un invariante y muchos chequeos */
	struct quadCeld * celd = (struct quadCeld *) malloc (sizeof (struct quadCeld));
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
void qt_dinamic_destroy (quadList_t * qt)
{
	struct quadCeld * aux = NULL;
	struct quadCeld * delCeld = NULL;
	
	ASSERT (qt != NULL)
	
	aux = qt->first.next;
	/* borramos todas las celdas */
	while (aux != NULL){
		delCeld = aux;
		aux = aux->next;
		free(delCeld);
	}
	/* borramos la estructura */
	free (qt);
}


/* destructor para la lista NO allocada dinamicamente, osea practicamente libera
 * todas las celdas de la lista, menos la estructura misma de la celda
	REQUIRES:
		el != NULL
*/
void qt_normal_destroy (quadList_t * qt)
{
	struct quadCeld * aux = NULL;
	struct quadCeld * delCeld = NULL;
	
	ASSERT (qt != NULL)
	
	aux = qt->first.next;
	/* borramos todas las celdas */
	while (aux != NULL){
		delCeld = aux;
		aux = aux->next;
		free(delCeld);
	}
}


/* Funcion para inicializar la lista
	REQUIRES:
		qt != NULL
NOTE: antes de cada corrida debemos inicializar la estructura 
*/
void qt_initialize (quadList_t * qt, u32 indexNode, u32 flow)
{
	ASSERT (qt != NULL)
	
	qt->size = 0;
	qt->prev = qt->plast = &(qt->first);
	qt->first.next->node = indexNode;
	qt->first.next->flow = flow;
	qt->first.next->pparent = NULL;
	qt->first.pparent = NULL;
	
}

/*! ~~~~~~~~~~~~  Funciones para obtener elementos ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que obtiene el nodo actual (NOTE:indice del nodo actual)
	REQUIRES:
		qt != NULL
	RETURNS:
		indice
*/
u32 qt_get_actual_node (quadList_t * qt)
{
	ASSERT (qt != NULL)
	ASSERT (qt->size >= 1)
	return qt->prev->next->node;
}

/* Funcion que obtiene el flujo actual 
	REQUIRES:
		qt != NULL
	RETURNS:
		flow
*/
u32 qt_get_actual_flow (quadList_t * qt)
{
	ASSERT (qt != NULL)
	return qt->prev->next->flow;
}

/* Funcion que obtiene la arista que agrego al nodo actual
	REQUIRES:
		qt != NULL
	RETURNS:
		edge
 */
edge_t * qt_get_actual_edge (quadList_t * qt)
{
	ASSERT (qt != NULL)
	return qt->prev->next->edge;
}

/* Funcion que devuelve el tamaño de la lista
 * NOTE: si qt == NULL ==> size = 0
 */
short qt_get_size (quadList_t * qt)
{
	if (qt == NULL)
		return 0;
	return qt->size;
}



/*! ~~~~~~~~~~~~~~~~  Funciones de "movimientos" ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que avanza el visor al siguiente elemento
 * Si esta en el ultimo elemento no avanzamos.
 *	REQUIRES:
 *		qt != NULL
 *	RETURNS:
 *		0, si avanzamos normalmente
 *		1, si estamos al final de la cola
 */
int qt_avance (quadList_t * qt)
{
	ASSERT (qt != NULL)
			
	if (qt->prev->next->next == NULL)
		return 1;
	else {
		qt->prev = qt->prev->next;
		return 0;
	}
}


/* Funcion que mueve el visor al padre del elemento actual
	REQUIRES:
		el != NULL
*/
void qt_go_parent (quadList_t * qt)
{
	ASSERT (qt != NULL)
	qt->prev = qt->prev->next->pparent;
}


/* Funcion que mueve el visor al comienzo de la lista
	REQUIRES:
		el != NULL
*/
void qt_start (quadList_t * qt)
{
	ASSERT (qt != NULL)
	qt->prev = qt->plast = &(qt->first);
}




/* Funcion que mueve el actual al final de la lista
REQUIRES:
el != NULL
NOTE: cuando terminamos t se encuentra en el ultimo lugar, primero debemos
avanzar el "visor" (actual) al final.
*/
void qt_move_last (quadList_t * qt)
{
	ASSERT (qt != NULL)
	qt->prev = qt->plast;
}


/*! ~~~~~~~~~~~~~~~~  Funciones de agregado/quitado ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que agrega una quatripleta (nodo, padre, flow).
 NOTE: tener en cuenta que el padre va a ser el elemento actual
	REQUIRES:
		qt		!= NULL
		edge	!= NULL
		indexNode	<= MAX_N_NODES
*/
void qt_add_quad (quadList_t * qt,  u32 flow, u32 indexNode , edge_t * edge )
{	
	struct quadCeld * celd;
	/* pre */
	ASSERT (qt != NULL)
	ASSERT (edge != NULL)
	ASSERT (indexNode <= MAX_N_NODES)
	ASSERT (nIsFromEdge(indexNode, edge))
	
	qt->size++;
	/* tenemos 2 casos posibles, que exista una celda o que no exista, si
	 * existe la celda entonces solo la usamos, si no la creamos */
	/* seteamos el flow */
	if (qt->plast->next->next != NULL) {
		celd = qt->plast->next->next;
	} else {
		celd = (struct quadCeld *) malloc (sizeof (struct quadCeld));
		celd->next = NULL;
		qt->plast->next->next = celd;
	}
	
	/* seteamos la celda */
	celd->node = indexNode;
	celd->flow = flow;
	celd->edge = edge;
	
	/* ahora seteamos el parent, en realidad el pparent */
	celd->pparent = qt->prev;
	
	/* actualizamos el ultimo puntero */
	qt->plast = qt->plast->next;
}

