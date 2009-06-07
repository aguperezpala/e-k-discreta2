#include "../../edge_list.h"
#include "../../edge.h"
#include "../../consts.h"
#include "../../node_stack.h"
#include "../../node.h"
#include "../../first_coloring.h"
#include "../../network.h"
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Configuracion del testing*/
#define FIRST_COLORING_CANT_NODES 444

static void frt_printcolores (u32 node_i, node_t *nodes)
{
	ASSERT (nodes != NULL)
	
	if (node_i != 0 && node_i != 1)
		printf ("Vertice %u: Color %d\n", node_i, nodes[node_i].color);
	else if (node_i == 0)
		printf ("Vertice s: Color %d\n",  nodes[node_i].color);
	else
		printf ("Vertice t: Color %d\n",  nodes[node_i].color);
}

static void frt_AniadirLado (EstadoNetwork *estado, u32 v1, u32 v2, u32 cap)
{
	edge_t *edge = NULL;
	
	ASSERT (estado != NULL)
	
	/* Generamos las listas forward y/o backward si es necesario */
	
	if (estado->nodes[v1].forwardList == NULL) {
		
		estado->nodes[v1].forwardList = el_create ();
		
		if (estado->nodes[v1].backwardList == NULL) {
			/* v1 es vértice nuevo */
			estado->nodes[v1].corrida = 0;
			ns_add_node (estado->nstack, v1);
			estado->nodes[v1].degree = 0;

		}
	}
	
	if (estado->nodes[v2].backwardList == NULL) {
		
		estado->nodes[v2].backwardList = el_create ();
		
		if (estado->nodes[v2].forwardList == NULL) {
			/* v2 es vértice nuevo */
			estado->nodes[v2].corrida = 0;
			ns_add_node (estado->nstack, v2);
			estado->nodes[v2].degree = 0;
		}
	}
	
	/* creamos la arista */
	edge = edge_create (cap, v1, v2);
	
	/* Agregamos a ambas listas */
	el_add_edge (estado->nodes[v1].forwardList, edge);
	estado->nodes[v1].degree++;
	el_add_edge (estado->nodes[v2].backwardList, edge);
	estado->nodes[v2].degree++;
	
}

static void frt_AniadirLadoColor (EstadoNetwork *estado, u32 v1, u32 v2, u32 cap)
{
	u32 m = 0;
	Color max_color = 0;
	
	ASSERT (estado != NULL)
	
	/* LLamamos a AniadirLado */
	frt_AniadirLado(estado, v1, v2, cap);
	ASSERT( estado->nodes[v1].degree > 0 && estado->nodes[v2].degree > 0)
			
	/* Seteamos el delta de todo el network/grafo */
	m = max (estado->nodes[v1].degree, estado->nodes[v2].degree);
	if ((unsigned)estado->delta < m) estado->delta = m;
	
	/* Mediante los grados vemos cuales son los vertices nuevos */
	if (estado->nodes[v1].degree == 1) {
		
		if (estado->nodes[v2].degree == 1) {
			/* Ambos vértices eran nuevos */
			estado->nodes[v1].color = 1;
			estado->nodes[v2].color = 2;

		} else{
			/* v1 es nuevo, lo coloreamos sin conflicto */
			estado->nodes[v1].color = 3 - estado->nodes[v2].color;
		}
	} else if (estado->nodes[v2].degree == 1){
		/* v2 es nuevo, lo coloreamos sin conflicto */
		estado->nodes[v2].color = 3 - estado->nodes[v1].color;
	}else{
		/* Ningún vértice es nuevo => lado conflictivo */
		el_add_edge (estado->l_con, el_get_actual(estado->nodes[v1].forwardList));
	}

	/* Actualizamos el color */
	max_color = max(estado->nodes[v1].color , estado->nodes[v2].color);
	estado->colores = max (estado->colores , max_color);
}

int main(void)
{
	EstadoNetwork * estado = NULL; 
	u32 i=0, j=0;

	estado = network_create();
	ASSERT (estado != NULL)

	/* Añado los lados del grafo completo */
	for(i=0; i < FIRST_COLORING_CANT_NODES ; i++){
		for(j=i+1; j < FIRST_COLORING_CANT_NODES ; j++)
			frt_AniadirLadoColor(estado, i, j, i+j);
	}
	
	/* Realizo el coloreo */
	ns_cmd(estado->nstack , estado->nodes , frt_printcolores);
	printf("Cantidad de colores usados: %u\n", ResolverConflictos(estado));
	ns_cmd(estado->nstack , estado->nodes , frt_printcolores);

	/* Destruyo todos los lados */
	for (i = 0; i < FIRST_COLORING_CANT_NODES; i++) {
		if(el_get_size(estado->nodes[i].forwardList) > 0) el_clean(estado->nodes[i].forwardList);
		if((estado->nodes[i].forwardList) != NULL) el_destroy(estado->nodes[i].forwardList);
		estado->nodes[i].forwardList = NULL;
		if(estado->nodes[i].backwardList != NULL) el_destroy(estado->nodes[i].backwardList);
		estado->nodes[i].backwardList = NULL;
	}

	return 0;
}

