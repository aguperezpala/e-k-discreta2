/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * Módulo Coloreo Greedy, versión 1.0.0, del proyecto único de
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
#include "consts.h"
#include "node_stack.h"

Color greedy_max_color = 0;

/* Comandos para impresion de colores */
#define color_printf_alfa(n,c) printf ("Vertice:%c Color:%i\n", n, -c);
#define color_printf_num (n,c) printf ("Vertice:%u Color:%i\n", n, -c);

/* Funcion que le aplica un coloreo propio a nodes y 
 * retorna la cantidad de colores usados.
   REQUIRES:
 		nodes != NULL
   RETURNS:
 		cantidad de colores utilizados.
   NOTE: Recordar que los colores van a ser negativos. Ademas 
 	     suponemos que puede contener un coloreo "positivo" previo.	
 */
Color color_greedy (node_s node_stack , node_t * nodes);



/* Dado un el nodo busca el menor color aún libre entre sus vecinos
*
* PRE: nodes != NULL && max_color < 0
* POS: color_propio(node, nodes) && retorna el mayor color usado.
*/
void coloring_node(u32 node_i, node_t * nodes);




#endif
