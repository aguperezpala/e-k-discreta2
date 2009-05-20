/*! vamos a hacer directamente el tipo de lista arista para agilizar las cosas */

/*! Practicamente lo que es esta lista consta de 4 punteros y un entero (tamaño)
 * El primer puntero señala el comienzo de la lista, el 2 señala el final de los
 * "NO", el 3 el final de los SI  y el 4 el elemento "actual".
 * Tanto en el momento de la creacion como cuando se agregan elementos, estos son
 * puestos en la cola de "SI".
*/
#ifndef EDGE_LIST_H
#define EDGE_LIST_H

#include <stdlib.h>

#include "consts.h"
#include "node.h"	/* edge */

/* definimos el tipo */
typedef struct s_edgeList edgeList_t;


/*!<<debemos pasar todas las funciones a inline o hacer visible la estructura y
 * usamos #defines para definir las funciones (Algunas).
 * Si vamos a definir inline fijarse que alomejor en el .c deben estar declaradas
 * como "static inline ....".
 */

/* Funcion que crea una lista (en caso de que usemos dinamica) 
 * constructor
 */
edgeList_t * el_create (void);

/* destructor para la lista allocada dinamicamente
	REQUIRES:
		el != NULL
*/
void el_dinamic_destroy (edgeList_t * el);

/* destructor para la lista NO allocada dinamicamente, osea practicamente libera
 * todas las celdas de la lista, menos la estructura misma de la celda */
REQUIRES:
el != NULL
*/
void el_normal_destroy (edgeList_t * el);


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
