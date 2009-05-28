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

#ifndef TRIPLE_LIST_H
#define TRIPLE_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#include "consts.h"
#include "node.h"	/* edge */

/* definimos el tipo */
typedef struct s_tripleList ;



/* Funcion que crea una lista (en caso de que usemos dinamica) 
 * constructor
 */
tripleList_t * el_create (void);

/* destructor para la lista allocada dinamicamente
	REQUIRES:
		el != NULL
*/
void el_dinamic_destroy (tripleList_t * el);

/* destructor para la lista NO allocada dinamicamente, osea practicamente libera
 * todas las celdas de la lista, menos la estructura misma de la celda
	REQUIRES:
		el != NULL
*/
void el_normal_destroy (tripleList_t * el);


/* Funcion que obtiene el edge acutal al que actualmente apunta la lista 
	REQUIRES:
		el != NULL
	RETURNS:
		NULL 	si no hay elemento
		edge 	cc
*/
INLINE edge_t * el_get_actual (tripleList_t * el);

/* Funcion que agrega un elemento al edge_list "el" del nodo "n".
 * Vamos a usar estructuras fijas, NO dinamicas (por eficiencia...).
 * Inicializa el flujo en 0
	REQUIRES:
		el	!= NULL
		edge	!= NULL
*/
INLINE void el_add_edge (tripleList_t * el,  edge_t * edge);

/* Funcion que devuelve el tamaño de la lista
 * NOTE: si el == NULL ==> size = 0
*/
INLINE short el_get_size (tripleList_t * el);



/* Funcion que sirve para eliminar el elemento actual (libera el edge)
	REQUIRES:
		el != NULL
		el_get_size (el) >= 1
*/
INLINE void el_del_edge (tripleList_t * el);


/* Funcion que avanza al siguiente elemento, si esta en el ultimo elemento
 * entonces el "visor" vuelve al comienzo. (una especie de lista circular)
	REQUIRES:
		el != NULL
*/
INLINE void el_avance (tripleList_t * el);





#endif
