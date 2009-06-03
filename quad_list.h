/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD TAD quadList (lista de quatripletas), versión 1.0.0, del proyecto único de
 * Discreta 2, FaMAF, año 2009
 * Este TAD representa la cola de una corrida E-K (o sea una ejecución de
 * AumentarFlujo)
 * Su nombre deriva de los elementos que componen cada una de sus celdas:
 * 	·Nombre del vértice
 *	·Nombre del padre (y que satanas te guarde)
 *	·Flujo soportado por el lado padre--vértice
 *	·Lado que une al vertice con su padre ( si , es un embarazo paterno :P )
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */


#ifndef QUAD_LIST_H
#define QUAD_LIST_H


/*! La estructura de cada celda es de la siguiente forma (una cuatripĺeta):
 *  {nodeIndex	 ,	Parent	,	actual Flow ,  edge }
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
#include "node.h"
#include "edge.h"

/* definimos el tipo */
typedef struct s_quadList quadList_t ;


/*! ~~~~~~~~~~~~  Constructores / destructores ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que crea una lista (en caso de que usemos dinamica) 
 * constructor
 */
quadList_t * qt_create (void);

/* destructor para la lista allocada dinamicamente
	REQUIRES:
		el != NULL
*/
void qt_dinamic_destroy (quadList_t * qt);

/* destructor para la lista NO allocada dinamicamente, osea practicamente libera
 * todas las celdas de la lista, menos la estructura misma de la celda
	REQUIRES:
		el != NULL
*/
void qt_normal_destroy (quadList_t * qt);

/* Funcion para inicializar la lista
	REQUIRES:
		qt != NULL
NOTE: antes de cada corrida debemos inicializar la estructura, tomamos el nodo
* principal de todos (s).
*/
void qt_initialize (quadList_t * qt, u32 indexNode, u32 flow);

/*! ~~~~~~~~~~~~  Funciones para obtener elementos ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que obtiene el nodo actual (NOTE:indice del nodo actual)
	REQUIRES:
		qt != NULL
	RETURNS:
		indice
*/
u32 qt_get_actual_node (quadList_t * qt);

/* Funcion que obtiene el el flujo actual 
	REQUIRES:
		qt != NULL
	RETURNS:
		flow
*/
u32 qt_get_actual_flow (quadList_t * qt);
 
/* Funcion que obtiene la arista que agrego al nodo actual
	REQUIRES:
		qt != NULL
	RETURNS:
		edge
*/
edge_t * qt_get_actual_edge (quadList_t * qt);

/* Funcion que devuelve el tamaño de la lista
 * NOTE: si qt == NULL ==> size = 0
*/
short qt_get_size (quadList_t * qt);


/*! ~~~~~~~~~~~~~~~~  Funciones de "movimientos" ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que avanza el visor al siguiente elemento
 * Si esta en el ultimo elemento no avanzamos.
 *	REQUIRES:
 *		qt != NULL
 *	RETURNS:
 *		0, si avanzamos normalmente
 *		1, si estamos al final de la cola
 */
int qt_avance (quadList_t * qt);

/* Funcion que mueve el visor al padre del elemento actual
	REQUIRES:
		el != NULL
*/
 void qt_go_parent (quadList_t * qt);

 
/* Funcion que mueve el visor al comienzo de la lista
 *	REQUIRES:
 *		qt != NULL
 *	RETURNS:
 *		0, si avanzamos normalmente
 *		1, si estamos al final de la cola
 */
 void qt_start (quadList_t * qt);


 /* Funcion que mueve el actual al final de la lista
	REQUIRES:
		el != NULL
NOTE: cuando terminamos t se encuentra en el ultimo lugar, primero debemos
      avanzar el "visor" (actual) al final.
*/
 void qt_move_last (quadList_t * qt);
 
 
/*! ~~~~~~~~~~~~~~~~  Funciones de agregado/quitado ~~~~~~~~~~~~~~~~~~~ */

/* Funcion que agrega una quintupleta (nodo, padre, flow, edge , is_backward).
 NOTE: tener en cuenta que el padre va a ser el elemento actual
	REQUIRES:
		qt		!= NULL
		edge	!= NULL
		indexNode	<= MAX_N_NODES
		nIsFromEdge(indexNode, edge)
*/
void qt_add_quad (quadList_t * qt,  u32 flow, u32 indexNode , edge_t * edge);



#endif
