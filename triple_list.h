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


/*! La estructura de cada celda es de la siguiente forma (una tripleta):
 *  {nodeIndex	 ,	Parent	,	actual Flow }
 * que es la representacion de la "cola" usada por E-K
 * ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ###
 * 				MODO DE USO
 * ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### 
 * Antes que nada, al empezar se debe reinicializar (o inicializar) la lista.
 * Cuando se agrega un elemento (exepto en la inicializacion), ese elemento
 * tiene como padre el ultimo elemento que fue seleccionado como padre. Para
 * seleccionar un padre se debe avanzar el puntero "padre" con (avanzar padre)
*/

#include <stdlib.h>
#include <stdbool.h>

#include "consts.h"
#include "node.h"	/* edge */

/* definimos el tipo */
typedef struct s_tripleList ;



/* Funcion que crea una lista (en caso de que usemos dinamica) 
 * constructor
 */
tripleList_t * tl_create (void);

/* destructor para la lista allocada dinamicamente
	REQUIRES:
		el != NULL
*/
void tl_dinamic_destroy (tripleList_t * tl);

/* destructor para la lista NO allocada dinamicamente, osea practicamente libera
 * todas las celdas de la lista, menos la estructura misma de la celda
	REQUIRES:
		el != NULL
*/
void tl_normal_destroy (tripleList_t * tl);

/*! ~~~~~~~~~~~~  Funciones para obtener elementos ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que obtiene el nodo actual (NOTE:indice del nodo actual)
	REQUIRES:
		tl != NULL
	RETURNS:
		indice
*/
INLINE u32 tl_get_actual_node (tripleList_t * tl);

/* Funcion que obtiene el el flujo actual 
	REQUIRES:
		tl != NULL
	RETURNS:
		flow
*/
INLINE u32 tl_get_actual_flow (tripleList_t * tl);


/* Funcion que devuelve el tamaño de la lista
 * NOTE: si tl == NULL ==> size = 0
*/
INLINE short tl_get_size (tripleList_t * tl);


/*! ~~~~~~~~~~~~  Funciones de "movimientos" ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que agrega un elemento al edge_list "el" del nodo "n".
 * Vamos a usar estructuras fijas, NO dinamicas (por eficiencia...).
 * Inicializa el flujo en 0
	REQUIRES:
		tl	!= NULL
		edge	!= NULL
*/
INLINE void tl_add_edge (tripleList_t * tl,  edge_t * edge);




/* Funcion que sirve para eliminar el elemento actual (libera el edge)
	REQUIRES:
		tl != NULL
		tl_get_size (tl) >= 1
*/
INLINE void tl_del_edge (tripleList_t * tl);


/* Funcion que avanza al siguiente elemento, si esta en el ultimo elemento
 * entonces el "visor" vuelve al comienzo. (una especie de lista circular)
	REQUIRES:
		el != NULL
*/
INLINE void tl_avance (tripleList_t * tl);





#endif
