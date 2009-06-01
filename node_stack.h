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

typedef void (*node_cmd) (u32 node , node_t * nodes);
typedef struct _node_s node_s;

/* Algunos comandos aceptados */
#define printf_alfa(n,c) printf ("Vertice:%c Color:%d\n", n, c);
#define printf_num (n,c) printf ("Vertice:%u Color:%d\n", n, c);

/* Genera una nueva pila de nodos vacía.
 *      modoinput == 1  =>  se considera el código ascii de 'v'
 *	modoinput == 2  =>  se considera el valor numérico de 'v'
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

/* Ejecuta el comando cmd en la pila en orden LIFO.
 *
 * PRE: ns != NULL  &&  modoinput == 1,2 && nodes != NULL && {ns} == {nodes}
 *    ns_print (ns)
 * POS: modoinput == 1  =>  se considera el código ascii de 'v'
 *	modoinput == 2  =>  se considera el valor numérico de 'v'
 */
void ns_cmd (node_s *ns, node_t * nodes , node_cmd cmd);

#endif