/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD edgeList_t (lista de aristas), versión 1.0.0, del proyecto único de
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


#ifndef EDGE_LIST_H
#define EDGE_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#include "consts.h"
#include "edge.h"


/* definimos el tipo */
typedef struct s_edgeList edgeList_t;


/* Funcion que crea una lista (en caso de que usemos dinamica) 
 * constructor
 */
edgeList_t * el_create (void);

/* Destruye la lista pero no libera su contenido
	REQUIRES:
		el != NULL
*/
void el_destroy (edgeList_t * el);

/* Destruye unicamente el contenido de la lista.
	REQUIRES:
		el != NULL
*/
void el_clean (edgeList_t * el);


/* Funcion que obtiene el edge acutal al que actualmente apunta la lista 
	REQUIRES:
		el != NULL
	RETURNS:
		NULL 	si no hay elemento
		edge 	cc
*/
edge_t * el_get_actual (edgeList_t * el);

/* Funcion que agrega un elemento al edge_list "el" del nodo "n".
 * Vamos a usar estructuras fijas, NO dinamicas (por eficiencia...).
 * Inicializa el flujo en 0
	REQUIRES:
		el	!= NULL
		edge	!= NULL
*/
void el_add_edge (edgeList_t * el,  edge_t * edge);

/* Funcion que devuelve el tamaño de la lista
 * NOTE: si el == NULL ==> size = 0
*/
short el_get_size (edgeList_t * el);



/* Funcion que sirve para eliminar el elemento actual (libera el edge)
	REQUIRES:
		el != NULL
		el_get_size (el) >= 1
*/
void el_del_edge (edgeList_t * el);


/* Funcion que avanza al siguiente elemento, si esta en el ultimo elemento
 * entonces el "visor" vuelve al comienzo. (una especie de lista circular)
 *	REQUIRES:
 *		el != NULL
 *	RETURNS:
 *		0, si se avanzó normalmente
 *		1, si al avanzar volvimos al comienzo
 */
int el_avance (edgeList_t * el);


/* Mueve el "visor" al primero elemento de la lista
 * 	REQUIRES:
 *		el != NULL
 */
void el_start (edgeList_t * el);


#endif
