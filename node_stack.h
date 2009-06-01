/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD node_s (stack de nodos) Es utilizado para cualquier cosa que requiera
 * recorrer todos los nodos del network.
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */

#ifndef NODE_STK_H
#define NODE_STK_H

#include "node.h"


typedef void (*node_cmd) (u32 node , node_t * nodes);
typedef struct _node_s * node_s;

/* Genera un nuevo stack de nodos vacía.
 *    ns = ns_create()
 * POS: ns != NULL
 */
node_s ns_create (void);

/* Destruye el stack de nodos
 *
 * PRE: ns != NULL
 *    ns_destroy(ns)
 */
void ns_destroy (node_s ns);

/* Agrega un nuevo vértice 'v' al comienzo del stack.
 *
 * PRE: ns != NULL  
 *    ns = ns_add_node (ns, v);
 * POS: "ns contiene a 'v' como último elemento"
 */
void ns_add_node (node_s ns, u32 v);

/* Ejecuta el comando cmd para todos los nodos del stack en orden LIFO
 *
 * PRE: ns != NULL && nodes != NULL && {ns} == {nodes}
 *    ns_print (ns,nodes,cmd)
 */
void ns_cmd (node_s ns, node_t * nodes , node_cmd cmd);

#endif
