#include <stdio.h>

#include "node_stack.h"

struct _node_s {
	struct _node_celd dummy;  /* 1º celda */
	struct _node_celd *last;  /* Celda actual */
};

struct _node_celd {
	u32 node;	/* Nombre del vértice */
	_node_celd *prev;
}* node_celd;

#define 

/* Genera una nueva pila de impresión vacía
 *
 *    ns = ns_create()
 * POS: ns != NULL
 */
node_s *ns_create (int modoinput)
{
	node_s ns;
	ASSERT ((modoinput == 1) || (modoinput == 2))

	ns = (node_s *) malloc (sizeof (struct _node_s));
	ASERT (ns != NULL)
	
	ns->last = &ns->dummy;
	
	return ns;
}

/* Añade un nuevo vértice 'v' al comienzo de la pila de impresión.
 *
 * PRE: ns != NULL  &&  sentido == 1,2
 *    ns = ns_add_node (ns, v, sentido);
 * POS: "ns contiene a 'v' como último elemento" &&
 *	sentido == ','  =>  se considera "forward" la relación entre 'v'
 *			    y el vértice anterior de la pila
 *	sentido == '<'  =>  se considera "backward" la relación entre 'v'
 *			    y el vértice anterior de la pila
 */
node_s *ns_add_node (node_s *ns, u32 v)
{
	node_celd new;
	
	ASSERT (ns != NULL)
	
	new = (node_celd) malloc (sizeof (struct _node_celd));
	ASSERT (new != NULL)
	
	new->node = v;
	new->prev = ns->last;
	ns->last = new;
	
	return ns;
}


/* Imprime la pila en orden LIFO, es decir, el último elemento agregado
 * será el primero en ser impreso
 *
 * PRE: ns != NULL  &&  modoinput == 1,2
 *    ns_print (ns, modoinput, flujo)
 * POS: modoinput == 1  =>  se considera el código ascii de 'v'
 *	modoinput == 2  =>  se considera el valor numérico de 'v'
 */
void ns_print (node_s *ns, int modoinput,node_t * nodes)
{
	node_s *aux;
	
	ASSERT (ns != NULL)
	ASSERT (nodes != NULL)
	
	aux = ns->last;
	if (modoinput == 1)
		while (aux != &ns->dummy) {
			/* Vamos imprimiendo todos los vértices */
			printf ("Vertice:%c Color:%d\n", aux->node, nodes[aux->node].color);
			
			free (aux);
			aux = aux->prev;
		}
	else
		while (aux != &ns->dummy) {
			/* Vamos imprimiendo todos los vértices */
			printf ("Vertice:%u Color:%d\n", aux->node, nodes[aux->node].color);
				
			free (aux);
			aux = aux->prev;
		}
		
	free (aux);
	aux = NULL;
	free (ns);
	ns = NULL;
}
