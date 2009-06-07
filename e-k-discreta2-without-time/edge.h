/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD edge_t (lado), versión 1.0.0, del proyecto único de
 * Discreta 2, FaMAF, año 2009
 * La estructura es transparente para permitir el acceso directo
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */

#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>

#include "consts.h"

typedef struct s_edge {
	u32 capacity;	/* Capacidad del lado */
	u32 flow;	/* Flujo actual que atraviesa el lado */
	u32 preFlow;	/* Flujo que querríamos mandar en una corrida E-K */
	u32 nodeOrig;	/* Vértice de origen */
	u32 nodeDest;	/* Vértice de destino */
} edge_t;


/* Creamos una arista
	REQUIRES:
		0 <= nodeOrig, nodeDest < 7000
*/
edge_t * edge_create (u32 capacity, u32 nodeOrig, u32 nodeDest);


/* destructor
 	REQUIRES:
		e != NULL
*/
void edge_destroy (edge_t * e);



#endif
