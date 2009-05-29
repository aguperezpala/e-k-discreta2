/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * Estructura node (vértices), versión 1.0.0, del proyecto único de
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


#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include "consts.h"
#include "edge.h"
#include "edge_list.h"


 /* recordemos que tenemos tambien el caso alfabetico, podriamos usar entero
 * para el alfabetico simplemente casteandolo o usando atoi...
 */
typedef struct s_node {
	
	/*!u32 nodeName;		No hace falta, el nombre es el indice mismo */
	u32 flux; 			/* flujo */
	edgeList_t *forwardList;	/* lista de aristas forward  */
	edgeList_t *backwardList;	/* lista de aristas backward */
	Color color;
	short degree;			/* Nº total de vecinos */
	/* int satur;	Agregarlo en caso de que usemos DSATUR */
} node_t;


#endif
