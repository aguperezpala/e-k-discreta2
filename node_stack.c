#include <stdio.h>

#include "node_stack.h"

typedef struct _node_celd_s * node_celd;

struct _node_celd_s {
	u32 node;	/* Nombre del vértice */
	node_celd prev;
};

struct _node_s {
	node_celd dummy;  /* 1º celda */
	node_celd last;  /* Celda ultima */
};

node_s ns_create (void)
{
	node_s ns = (node_s) malloc (sizeof (struct _node_s));
	ASSERT (ns != NULL)

	ns->dummy = (node_celd) malloc (sizeof (struct _node_celd_s));
	ASSERT (ns->dummy != NULL)
	
	ns->last = ns->dummy;

	return ns;
}

void ns_destroy (node_s ns)
{
	node_celd aux;
	node_celd target;
	
	ASSERT (ns != NULL)
	
	aux = ns->last;
	
	/* Destruye todos los nodos */
	while (aux != ns->dummy) {
		target = aux;
		aux = aux->prev;
		free(target);
		target = NULL;
	}
	
	/* Destruye el stack */
	free (ns->dummy);
	ns->dummy = NULL;
	aux = NULL;
	free (ns);
	ns = NULL;
}

void ns_add_node (node_s ns, u32 v)
{
	node_celd new;
	
	ASSERT (ns != NULL)
	
	new = (node_celd) malloc (sizeof(struct _node_celd_s));
	ASSERT (new != NULL)
	
	new->node = v;
	new->prev = ns->last;
	ns->last = new;
}

void ns_cmd (node_s ns,node_t * nodes , node_cmd cmd )
{
	node_celd aux;
	
	ASSERT (ns != NULL)
	ASSERT (nodes != NULL)
	
	aux = ns->last;
	
	/* Realizamos la ejecucion de cmd para todos los vertices */
	while (aux != ns->dummy) {
		cmd (aux->node, nodes);
		aux = aux->prev;
	}
	aux = NULL;
}
