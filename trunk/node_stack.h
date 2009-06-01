/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD node_s (pila de nodos) Es utilizado para la impresión de los
 * nodos coloreados.
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */

#ifnedf NODE_STK_H
#define NODE_STK_H

#include "node.h"

typedef struct _node_s node_s;

/* Genera una nueva pila de nodos vacía
 *
 *    ns = ns_create()
 * POS: ns != NULL
 */
node_s *ns_create (int modoinput);

/* Añade un nuevo vértice 'v' al comienzo de la pila de nodos.
 *
 * PRE: ps != NULL
 *    ps = ps_add_node (ps, v);
 * POS: "ps contiene a 'v' como último elemento" 
 */
node_s *ns_add_node (node_s *ns, u32 v);

/* Imprime la pila en orden LIFO, es decir, el último elemento agregado
 * será el primero en ser impreso
 *
 * PRE: ns != NULL  &&  modoinput == 1,2 && nodes != NULL && {ns} == {nodes}
 *    ns_print (ns)
 * POS: modoinput == 1  =>  se considera el código ascii de 'v'
 *	modoinput == 2  =>  se considera el valor numérico de 'v'
 */
void ns_print (node_s *ns, int modoinput , node_t * nodes);

#endif