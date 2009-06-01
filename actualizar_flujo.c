
#include <stdio.h>

#include "actualizar_flujo.h"


/* Se limita a actualizar el estado del network sin imprimir nada por pantalla
 * 
 * PRE: estado != NULL && 0 <= q,s,t <= MAX_N_NODES
 */
void ActualizarSilencioso (EstadoNetwork *estado, u32 q, u32 s, u32 t, u32 flujo)
{
	edge_t *edge;
	
	ASSERT (estado != NULL)
	ASSERT (0 <= q <= MAX_N_NODES)
	ASSERT (0 <= s <= MAX_N_NODES)
	ASSERT (0 <= t <= MAX_N_NODES)
	
	if (q == t) {
		/* Actualizamos el valor del flujo */
		estado->flow_value += flujo;
		
		/* Actualizamos el flujo */
		while (q != s){
			edge = qt_get_actual_edge (estado->cola);
		
			ASSERT (nIsFromEdge(q, edge))
			ASSERT (!NotInQueue(&estado->nodes[q], estado->corrida))
			
			if (q == edge->nodeDest)
				edge->flow += flujo;  /* Es lado forward */
			else
				edge->flow -= flujo;  /* Es lado backward */
			
			qt_go_parent (estado->cola);
			q = qt_get_actual_node (estado->cola);
		}
		
	} else
		estado->maximal = true;
}




/* Además de actualizar el estado del network imprime el camino hallado que
 * está actualmente en la cola del network y el flujo que por él transita.
 * De no haber camino s--t no se imprime nada
 *
 * PRE: estado != NULL && 0 <= q,s,t <= MAX_N_NODES
 */
void ActualizarConCamino (EstadoNetwork *estado, u32 q, u32 s, u32 t, u32 flujo)
{
	edge_t *edge;
	print_s *ps;  /* Pila de impresión (ver print_stack.h) */
	
	ASSERT (estado != NULL)
	ASSERT (0 <= q <= MAX_N_NODES)
	ASSERT (0 <= s <= MAX_N_NODES)
	ASSERT (0 <= t <= MAX_N_NODES)
	
	if (q == t) {
		ps = ps_create();
		
		/* Actualizamos el flujo total */
		estado->flow_value += flujo;
		
		/* Actualizamos el flujo del network */
		while (q != s){
			edge = qt_get_actual_edge (estado->cola);
	
			ASSERT (nIsFromEdge(q, edge))
			ASSERT (!NotInQueue(&estado->nodes[q], estado->corrida))
			
			if (edge->nodeDest == q) { /* Es lado forward */
				edge->flow += e;
				ps = ps_add_node (ps, q, 1);
						
			} else {		  /* Es lado backward */
				edge->flow -= e;
				ps = ps_add_node (ps, q, 2);
			}
			
			qt_go_parent (estado->cola);
			q = qt_get_actual_node (estado->cola);
		}
		/* Nos faltó agregar 's' */
		ps = ps_add_node (ps, q, estado->modoinput, 1);
		
		/* Imprimimos el camino hallado */
		ps_print (ps, estado->modoinput);
		ps_destroy (ps);
		
	} else
		estado->maximal = true;
}



/* Actualiza el estado del network y, en caso de no existir camino s--t,
 * imprime el corte minimal actualmente en la cola y su capacidad
 * Si el camino s--t existe nada es impreso
 *
 * PRE: estado != NULL && 0 <= q,s,t <= MAX_N_NODES
 */
void ActualizarConCorte (EstadoNetwork *estado, u32 q, u32 s, u32 t, u32 flujo)
{
	ASSERT (estado != NULL)
	ASSERT (0 <= q <= MAX_N_NODES)
	ASSERT (0 <= s <= MAX_N_NODES)
	ASSERT (0 <= t <= MAX_N_NODES)
}




/* La combinación esperada entre ActualizarConCamino y ActualizarConCorte
 *
 * PRE: estado != NULL && 0 <= q,s,t <= MAX_N_NODES
 */
void ActualizarConCaminoYCorte (EstadoNetwork *estado, u32 q, u32 s, u32 t, u32 flujo)
{
	ASSERT (estado != NULL)
	ASSERT (0 <= q <= MAX_N_NODES)_NODES)
	ASSERT (0 <= s <= MAX_N_NODES)
	ASSERT (0 <= t <= MAX_N_NODES)
}




