/*! vamos a hacer directamente el tipo de lista arista para agilizar las cosas */

/*! Practicamente lo que es esta lista consta de 4 punteros y un entero (tamaño)
 * El primer puntero señala el comienzo de la lista, el 2 señala el final de los
 * "NO", el 3 el comienzo de los SI  y el 4 el elemento "actual".
 * <podriamos utilizar solo 2 punteros (ya que el comienzo de NO es el comienzo
 * de la lista en si, y el comienzo de la lista si es el final + 1 de la lista
 * NO>
 * Tanto en el momento de la creacion como cuando se agregan elementos, estos son
 * puestos en la cola de "SI".
*/
#ifndef EDGE_LIST_H
#define EDGE_LIST_H

#include <stdlib.h>
#include <stdbool.h>

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
INLINE edgeList_t * el_create (void);

/* destructor para la lista allocada dinamicamente
	REQUIRES:
		el != NULL
*/
INLINE void el_dinamic_destroy (edgeList_t * el);

/* destructor para la lista NO allocada dinamicamente, osea practicamente libera
 * todas las celdas de la lista, menos la estructura misma de la celda
	REQUIRES:
		el != NULL
*/
INLINE void el_normal_destroy (edgeList_t * el);


/* Funcion que obtiene el edge acutal al que actualmente apunta la lista 
	REQUIRES:
		el != NULL
	RETURNS:
		NULL 	si no hay elemento
		edge 	cc
*/
INLINE edge_t * el_get_actual (edgeList_t * el);

/* Funcion que agrega un elemento al edge_list "el" del nodo "n".
 * Vamos a usar estructuras fijas, NO dinamicas (por eficiencia...).
 * Agregamos al comienzo de la lista "SI"
 * Inicializa el flujo en 0
	REQUIRES:
		el	!= NULL
		n	!= NULL
*/
INLINE void el_add_edge (edgeList_t * el,  u32 capacity, node_t * n);

/*NOTE:la misma que antes solo que inicializa el flow en "flow" */
INLINE void el_add_edge_with_flow (edgeList_t * el, u32 flow, u32 capacity, node_t * n);

/* Funcion que devuelve el tamaño de la lista, osea delta
	REQUIRES:
		el != NULL
*/
unsigned int el_get_size (edgeList_t * el);


/* Funcion que manda el edge actual (el que apunta el visor) de la parte SI a la
 * parte NO
	REQUIRES:
		el != NULL
*/
void el_swap_to_si_edge (edgeList_t * el);


/* Funcion que manda el edge actual (el que apunta el visor) de la parte NO a la
 * parte SI
	REQUIRES:
		el != NULL
*/
void el_swap_to_no_edge (edgeList_t * el);


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



/*! Funciones para chequear si las listas estan vacias (tienen la misma pre/pos)
	REQUIRES:
		el != NULL
	RETURNS:
		true 	si esta vacia
		false 	caso contrario
*/
/* global list */
bool el_is_empty (edgeList_t * el);
/* SI list */
bool el_si_is_empty (edgeList_t * el);
/* NO list */
bool el_no_is_empty (edgeList_t * el);



#endif