#include <stdio.h>

#include "print_stack.h"


struct _print_s {
	struct _print_celd dummy;  /* 1º celda */
	struct _print_celd *last;  /* Celda actual */
};

struct _print_celd {
	u32 node;	/* Nombre del vértice */
	char sentido;	/* ',' => forward ; '<' => backward */
	_print_celd *prev;
};


/* Genera una nueva pila de impresión vacía
 *
 *    ps = ps_create()
 * POS: ps != NULL
 */
print_s *ps_create (void)
{
	print_s ps;
	
	ps = (print_s *) malloc (sizeof (struct _print_s));
	ASERT (ps != NULL)
	
	ps->last = &ps->dummy;
	ps->size = 0;
	
	return ps;
}


/* Destruye la pila de impresión
 *
 * PRE: ps != NULL
 *    ps_destroy(ps)
 * POS: los recursos de memoria de ps han sido liberados
 */
void ps_destroy (print_s *ps)
{
	print_s *aux;
	
	ASSERT (ps != NULL)
	
	aux = ps->last;
	
	while (aux != &ps->first) {
		/* Destruimos hacia atrás hasta llegar al comienzo */
		ps->last = ps->last->prev;
		free (aux);
		aux = ps->last;
	}
	
	free (ps);
}


/* Añade un nuevo vértice 'v' al comienzo de la pila de impresión.
 *
 * PRE: ps != NULL  &&  sentido == 1,2
 *    ps = ps_add_node (ps, v, sentido);
 * POS: "ps contiene a 'v' como último elemento" &&
 *	sentido == ','  =>  se considera "forward" la relación entre 'v'
 *			    y el vértice anterior de la pila
 *	sentido == '<'  =>  se considera "backward" la relación entre 'v'
 *			    y el vértice anterior de la pila
 */
print_s *ps_add_node (print_s *ps, u32 v, char sentido)
{
	_print_celd *new;
	
	ASSERT (ps != NULL)
	ASSERT ((sentido == ',') || (sentido == '<'))
	
	new = (_print_celd *) malloc (sizeof (struct _print_celd));
	ASSERT (new != NULL);
	
	new->node = v;
	new->sentido = sentido;
	new->prev = ps->last;
	
	ps->last = new;
	
	return ps;
}


/* Imprime la pila en orden LIFO, es decir, el último elemento agregado
 * será el primero en ser impreso
 *
 * PRE: ps != NULL  &&  modoinput == 1,2
 *    ps_print (ps, modoinput, flujo)
 * POS: modoinput == 1  =>  se considera el código ascii de 'v'
 *	modoinput == 2  =>  se considera el valor numérico de 'v'
 */
void ps_print (print_s *ps, int modoinput, u32 flujo)
{
	print_s *aux;
	
	ASSERT (ps != NULL)
	ASSERT ((modoinput == 1) || (modoinput == 2))
	
	aux = ps->last;
	
	while (aux->prev != &ps->dummy) {
		/* Vamos imprimiendo todos los vértices */
		if (modoinput == 1)
			printf ("%c%c", aux->node, aux->sentido);
		else
			printf ("%u%c", aux->node, aux->sentido);
		
		aux = aux->prev;
	}
	
	/* Imprimimos 't' (o el último vértice, que DEBERIA ser lo mismo) */
	if (modoinput == 1)
			printf ("%c: %u\n\n", aux->node, flujo);
	else
			printf ("%u: %u\n\n", aux->node, flujo);
}