#include "test_greedy.h"
#include "../edge_list.h"
#include "../edge.h"
#include "../consts.h"
#include "../node_stack.h"
#include "../node.h"
#include "../greedy.h"
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Configuracion del testing*/
#define GREEDY_CANT_EDGES 5 
#define GREEDY_CANT_NODES 20


static void printcolores (u32 node_i, node_t *nodes)
{
	ASSERT (nodes != NULL)
	
	if (node_i != 0 && node_i != 1)
		printf ("Vertice %u: Color %d\n", node_i, nodes[node_i].color);
	else if (node_i == 0)
		printf ("Vertice s: Color %d\n",  nodes[node_i].color);
	else
		printf ("Vertice t: Color %d\n",  nodes[node_i].color);
}

START_TEST ( test_greedy )
{
	edge_t * e = NULL;
	node_t nodes[GREEDY_CANT_NODES];
	node_s ns = ns_create();
	u32 i=0 , j=0;
	Color  c = 0;

	for(i=0; i < GREEDY_CANT_NODES ; i++){
		nodes[i].color = 0;
		nodes[i].corrida = 0;
		ns_add_node(ns , i);
	}
	
	for(i=0; i < GREEDY_CANT_NODES ; i++){
		nodes[i].forwardList = el_create();
		for(j=(i+1); j <= GREEDY_CANT_EDGES ; j++){
			e = edge_create(0 , i , j);
			el_add_edge(nodes[i].forwardList, e);
			e = el_get_actual(nodes[i].forwardList);
			assert (i== e->nodeOrig);
			assert (j== e->nodeDest);
		}
		nodes[i].backwardList = el_create();
		for(j=(i+1); j <= GREEDY_CANT_EDGES ; j++){
			e = edge_create(0 , j , i );
			el_add_edge(nodes[i].backwardList, e);
			e = el_get_actual(nodes[i].backwardList);
			assert (j== e->nodeOrig);
			assert (i== e->nodeDest);
		}
		printf("node:%u , propio?: %u\n" , i , color_propio(i , nodes));
	}

	printf("Cantidad de colores usados: %u\n", c);
	/*c = color_greedy(ns,nodes);
	printf("Cantidad de colores usados: %u", c);*/
	ns_cmd(ns , nodes , printcolores);
}
END_TEST

Suite *greedy_suite (void)
{
	Suite *s = suite_create ("greedy");
	TCase *tc_commands = tcase_create ("Operationes");

	/* Comandos */
	suite_add_tcase (s,tc_commands);
	tcase_add_test (tc_commands, test_greedy);
	return s;
}
