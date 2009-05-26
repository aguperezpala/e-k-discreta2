/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD edgeList (lista de aristas), versión 1.0.0, del proyecto único de
 * Discreta 2, FaMAF, año 2009
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */


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
		edge	!= NULL
*/
INLINE void el_add_edge (edgeList_t * el,  edge_t * edge);

/* Funcion que devuelve el tamaño de la lista, osea delta
 * NOTE: si el == NULL ==> size = 0
*/
INLINE short el_get_size (edgeList_t * el);



/* Funcion que sirve para eliminar el elemento actual (libera el edge)
	REQUIRES:
		el != NULL
		el_get_size (el) >= 1
*/
INLINE void el_del_edge (edgeList_t * el);


/* Funcion que avanza al siguiente elemento, si esta en el ultimo elemento
 * entonces el "visor" vuelve al comienzo. (una especie de lista circular)
	REQUIRES:
		el != NULL
*/
INLINE void el_avance (edgeList_t * el);





#endif
