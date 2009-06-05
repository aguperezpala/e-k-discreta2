#include "test_node_stack.h"
#include "../node_stack.h"
#include "../node.h"
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Configuracion del testing*/
#define CANT_NODES 20

/* Variables locales */
static node_s ns = NULL;
static int i = 0;
static node_t nodes[CANT_NODES];

/* Funciones para seteo de entorno */
static void ImpresionColoresAlf (u32 node_i, node_t *nodes)
{
	ASSERT (nodes != NULL)
	printf ("Vertice %d: Color %d\n", node_i, nodes[node_i].color);
}

START_TEST ( test_create_ns )
{
	ns = ns_create ();
	assert (ns != NULL);
	ns_destroy(ns);
	ns= NULL;
}
END_TEST


START_TEST ( test_add_node_ns )
{
	ns = ns_create ();
	assert (ns != NULL);

	for(i=0; i < 20 ; i++)ns_add_node(ns ,(u32) i);

	ns_destroy(ns);
	ns= NULL;
}
END_TEST

START_TEST ( test_cmd_ns )
{
	ns = ns_create ();
	assert (ns != NULL);

	for(i=0; i < CANT_NODES ; i++){
		nodes[i].color = i;
		ns_add_node(ns , i);
	}
	ns_cmd(ns , nodes , ImpresionColoresAlf );

	ns_destroy(ns);
	ns= NULL;
}
END_TEST

Suite *node_stack_suite (void)
{
	Suite *s = suite_create ("node_stack");
	TCase *tc_commands = tcase_create ("Operations");

	/* Comandos */
	/*tcase_add_checked_fixture (tc_commands, create_tables , destroy_tables);*/
	tcase_add_test (tc_commands, test_create_ns);
	tcase_add_test (tc_commands, test_add_node_ns);
	tcase_add_test (tc_commands, test_cmd_ns);
	suite_add_tcase (s,tc_commands);

	return s;
}
