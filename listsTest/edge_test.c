#include <stdio.h>
#include <assert.h>
#include "node.h"
#include "edge_list.h"

static void e_print (edge_t * e)
{
	assert (e != NULL);
	
	printf ("EDGE: cap:%d\tflow:%d\tnodeOrig:%d\tnodeDest:%d\n",
		 e->capacity, e->flow, e->nodeOrig, e->nodeDest);
}


int main (void)
{
	edgeList_t * list = NULL;
	edge_t * edge = NULL;
	int i = 0;
	
	printf ("size:%d\n",el_get_size(list));
	
	printf ("size:%d\n",el_get_size(list));
	list = el_create ();
	edge = edge_create (1,2,3);
	el_add_edge (list, edge);
	e_print (edge);
	
	e_print (el_get_actual (list));
	el_avance (list);
	e_print (el_get_actual (list));
	
	
	for (i = 0; i < 900; i++) {
		edge = edge_create ((u32) i, 2, (u32) 900-i);
		el_add_edge (list, edge);
	}
	printf ("size:%d\n",el_get_size(list));
	for (i = 0; i < 950; i++) {
		e_print (el_get_actual (list));
		el_avance (list);
	}
	printf ("size:%d\n",el_get_size(list));
	i = 0;
	el_dinamic_destroy (list);
	
	return 0;
}
