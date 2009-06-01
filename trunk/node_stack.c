#include <stdio.h>

#include "node_stack.h"

struct _node_s {
	struct _node_celd dummy;  /* 1º celda */
	struct _node_celd *last;  /* Celda actual */
	void print_cmd;		  /* Comando para imprimir */ 
}* node_s;

struct _node_celd {
	u32 node;	/* Nombre del vértice */
	node_celd prev;
}* node_celd;

/* Macros internas */
#define printf_alfa(n,c) printf ("Vertice:%c Color:%d\n", n, c);
#define printf_num (n,c) printf ("Vertice:%u Color:%d\n", n, c);

/* Genera una nueva pila de nodos vacía.
 *      modoinput == 1  =>  se considera el código ascii de 'v'
 *	modoinput == 2  =>  se considera el valor numérico de 'v'
 *    ns = ns_create()
 * POS: ns != NULL
 */
node_s *ns_create (int modoinput)
{
	node_s ns;
	ASSERT ((modoinput == 1) || (modoinput == 2))

	ns = (node_s *) malloc (sizeof (struct _node_s));
	ASSERT (ns != NULL)
	
	ns->last = &ns->dummy;

	if ( modoinput == 1 )
		ns->print_cmd = printf_alfa;
	else
		ns->print_cmd = printf_num;
	
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
 * PRE: ns != NULL
 *    ns_print (ns, modoinput, flujo)
 * POS: modoinput == 1  =>  se considera el código ascii de 'v'
 *	modoinput == 2  =>  se considera el valor numérico de 'v'
 */
void ns_print (node_s *ns,node_t * nodes)
{
	register node_s *aux;
	
	ASSERT (ns != NULL)
	ASSERT (nodes != NULL)
	
	aux = ns->last;

	while (aux != &ns->dummy) {
		/* Vamos imprimiendo todos los vértices */
		ns->print_cmd (aux->node, nodes[aux->node].color);
		free (aux);
		aux = aux->prev;
	}
	
	free (aux);
	aux = NULL;
	free (ns);
	ns = NULL;
}
