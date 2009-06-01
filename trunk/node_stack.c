#include <stdio.h>

#include "node_stack.h"

struct _node_s {
	struct _node_celd dummy;  /* 1º celda */
	struct _node_celd *last;  /* Celda actual */
}* node_s;

struct _node_celd {
	u32 node;	/* Nombre del vértice */
	node_celd prev;
}* node_celd;

/* Genera un nuevo stack de nodos vacía.
 *    ns = ns_create()
 * POS: ns != NULL
 */
node_s *ns_create (void)
{

	ns = (node_s *) malloc (sizeof (struct _node_s));
	ASSERT (ns != NULL)
	
	ns->last = &ns->dummy;

	return ns;
}

/* Agrega un nuevo vértice 'v' al comienzo del stack.
 *
 * PRE: ns != NULL  
 *    ns = ns_add_node (ns, v);
 * POS: "ns contiene a 'v' como último elemento"
 */
void ns_add_node (node_s *ns, u32 v)
{
	node_celd new;
	
	ASSERT (ns != NULL)
	
	new = (node_celd) malloc (sizeof (struct _node_celd));
	ASSERT (new != NULL)
	
	new->node = v;
	new->prev = ns->last;
	ns->last = new;
}

/* Ejecuta el comando cmd para todos los nodos del stack en orden LIFO
 *
 * PRE: ns != NULL && nodes != NULL && {ns} == {nodes}
 *    ns_print (ns,nodes,cmd)
 */
void ns_cmd (node_s *ns,node_t * nodes , node_cmd cmd )
{
	node_s *aux;
	
	ASSERT (ns != NULL)
	ASSERT (nodes != NULL)
	
	aux = ns->last;
	
	/* Realizamos la ejecucion de cmd para todos los vertices */
	while (aux != &ns->dummy) {
		cmd (aux->node, nodes);
		free (aux);
		aux = aux->prev;
	}
	
	free (ns);
	ns = NULL;
}
