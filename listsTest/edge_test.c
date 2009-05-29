#include <stdio.h>
#include <assert.h>
#include "node.h"
#include "edge_list.h"
#include "triple_list.h"


/*
static void e_print (edge_t * e)
{
	assert (e != NULL);
	
	printf ("EDGE: cap:%d\tflow:%d\tnodeOrig:%d\tnodeDest:%d\n",
		 e->capacity, e->flow, e->nodeOrig, e->nodeDest);
}
static void edge_list_test ()
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
	el_del_edge (list);
	printf ("size:%d\n",el_get_size(list));

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
}
*/
int main (void)
{
	tripleList_t * l = NULL;
	u32 index = 0;
	int i = 0;
	
	l = tl_create ();
	tl_initialize (l, 0);
	
	index = 1;
	printf ("size:%d\n",tl_get_size (l));
	for (i = 0; i < 10; i++) {
		tl_add_triple (l, (u32) i, (u32) i);
		if (i%2 == 0)
			tl_avance (l);
	}
	
	tl_move_last (l);
	
	for (i = 0; i < 10; i++) {
		
		printf ("actualNode:%d\n",tl_get_actual_node (l));
		/*printf ("actualflow:%d\n",tl_get_actual_flow (l));*/
		tl_go_parent (l);
		/*printf ("parent:%d\n",tl_get_actual_node (l));*/
	}
	
	printf ("size:%d\n",tl_get_size (l));
	tl_dinamic_destroy (l); l = NULL;
	printf ("size:%d\n",tl_get_size (l));
	
	
	return 0;
}














