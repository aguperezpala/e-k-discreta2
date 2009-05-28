/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD Coloreo Greedy, versión 1.0.0, del proyecto único de
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

#ifndef GREEDY_H
#define GREEDY_H

#include "node.h"
#include "const.h"

/* Funcion que le aplica un coloreo propio a nodes y 
   retorna la cantidad de colores usados.
	REQUIRES:
		nodes != NULL
	RETURNS:
		cantidad de colores
*/
Color color_greedy ( node_t * nodes );

#endif