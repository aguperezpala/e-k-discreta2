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
 * que es la representacion de la "cola" usada por E-K.
 * ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ###
 * 				MODO DE USO
 * ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### 
 * Antes que nada, al empezar se debe reinicializar (initialize) la lista.
 * Cuando se agrega un elemento (exepto en la inicializacion), ese elemento
 * tiene como padre el elemento actual (osea a donde apunta el visor).
*/

#include <stdlib.h>
#include <stdbool.h>

#include "consts.h"
#include "node.h"	/* edge */

/* definimos el tipo */
typedef struct s_tripleList tripleList_t ;


/*! ~~~~~~~~~~~~  Constructores / destructores ~~~~~~~~~~~~~~~~~~~ */

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

/* Funcion para inicializar la lista
	REQUIRES:
		tl != NULL
NOTE: antes de cada corrida debemos inicializar la estructura, tomamos el nodo
* principal de todos (s).
*/
void tl_initialize (tripleList_t * tl, u32 indexNode);

/*! ~~~~~~~~~~~~  Funciones para obtener elementos ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que obtiene el nodo actual (NOTE:indice del nodo actual)
	REQUIRES:
		tl != NULL
	RETURNS:
		indice
*/
 u32 tl_get_actual_node (tripleList_t * tl);

/* Funcion que obtiene el el flujo actual 
	REQUIRES:
		tl != NULL
	RETURNS:
		flow
*/
 u32 tl_get_actual_flow (tripleList_t * tl);
 
/* Funcion que obtiene la arista que agrego al nodo actual
	REQUIRES:
		tl != NULL
	RETURNS:
		edge
*/
edge_t tl_get_actual_edge (tripleList_t * tl);

/* Funcion que obtiene la arista que agrego al nodo actual
	REQUIRES:
		tl != NULL
	RETURNS:
		si es backward
*/
bool tl_get_actual_is_backward (tripleList_t * tl);


/* Funcion que devuelve el tamaño de la lista
 * NOTE: si tl == NULL ==> size = 0
*/
 short tl_get_size (tripleList_t * tl);


/*! ~~~~~~~~~~~~~~~~  Funciones de "movimientos" ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que avanza el visor al siguiente elemento, si esta en el ultimo elemento
 * entonces el "visor" vuelve al comienzo. (una especie de lista circular)
 *	REQUIRES:
 *		tl != NULL
 *	RETURNS:
 *		0, si avanzamos normalmente
 *		1, si estamos al final de la cola
 */
int tl_avance (tripleList_t * tl);

/* Funcion que mueve el visor al padre del elemento actual
	REQUIRES:
		el != NULL
*/
 void tl_go_parent (tripleList_t * tl);

 
/* Funcion que avanza el visor al siguiente elemento
 * Si esta en el ultimo elemento no avanzamos.
 *	REQUIRES:
 *		tl != NULL
 *	RETURNS:
 *		0, si avanzamos normalmente
 *		1, si estamos al final de la cola
 */
 void tl_start (tripleList_t * tl);


 /* Funcion que mueve el actual al final de la lista
	REQUIRES:
		el != NULL
NOTE: cuando terminamos t se encuentra en el ultimo lugar, primero debemos
      avanzar el "visor" (actual) al final.
*/
 void tl_move_last (tripleList_t * tl);
 
 
/*! ~~~~~~~~~~~~~~~~  Funciones de agregado/quitado ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que agrega una quintupleta (nodo, padre, flow, edge , is_backward).
 NOTE: tener en cuenta que el padre va a ser el elemento actual
	REQUIRES:
		tl		!= NULL
		edge	!= NULL
		indexNode	<= MAX_N_NODES
*/
void tl_add_triple (tripleList_t * tl,  u32 flow, u32 indexNode , edge_t * edge , bool is_backward );



#endif
