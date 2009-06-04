/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * Estructura node_t (vértices), versión 1.0.0, del proyecto único de
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


typedef struct s_node {
	edgeList_t *forwardList;	/* lista de aristas forward  */
	edgeList_t *backwardList;	/* lista de aristas backward */
	unsigned short corrida; 	/* Versión de corrida E-K para aumentar flujo */
	short degree;				/* Nº total de vecinos */
	Color color;				/* Color del vertice */
} node_t;


#endif
