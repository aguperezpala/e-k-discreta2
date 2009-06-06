#include "test_edge_list.h"
#include "../edge_list.h"
#include "../edge.h"
#include "../consts.h"
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Configuracion del testing*/
#define CANT_EDGES 20

/* Variables locales */
static edge_t * e = NULL;
static edgeList_t * el_din = NULL;
static u32 i = 0;

/* Funciones para seteo de entorno */

START_TEST ( test_create_destroy_empty_el )
{
	el_din = el_create ();
	assert (el_din != NULL);
	el_destroy(el_din);
	el_din= NULL;
}
END_TEST


START_TEST (test_add_edge_el)
{
	el_din = el_create ();
	assert (el_din != NULL);

	for(i=0; i < CANT_EDGES ; i++){
		e = edge_create(i , i , i+1);
		el_add_edge(el_din, e);
	}
}
END_TEST


START_TEST (test_create_clean_destroy_el)
{
	el_din = el_create ();
	assert (el_din != NULL);

	for(i=0; i < CANT_EDGES ; i++){
		e = edge_create(i , i , i+1);
		el_add_edge(el_din, e);
	}
	
	el_clean(el_din);
	el_destroy(el_din);
	el_din= NULL;
}
END_TEST

START_TEST ( test_check_size_el )
{
	el_din = el_create ();
	assert (el_din != NULL);

	for(i=0; i < CANT_EDGES ; i++){
		e = edge_create(i , i , i+1);
		el_add_edge(el_din, e);
	}

	assert(el_get_size(el_din) == CANT_EDGES);
	
	el_clean(el_din);
	el_destroy(el_din);
	el_din= NULL;
	assert(el_get_size(el_din) == 0);
	
}
END_TEST

START_TEST ( test_start_avance_el )
{
	el_din = el_create ();
	assert (el_din != NULL);

	for(i=0; i < CANT_EDGES ; i++){
		e = edge_create(i , i , i+1);
		el_add_edge(el_din, e);
		e = el_get_actual(el_din);
		assert (i== e->capacity);
		assert (i== e->nodeOrig);
		assert (i+1== e->nodeDest);
	}

	assert(el_get_size(el_din) == CANT_EDGES);
	el_start(el_din);
	do{
		assert (i<= CANT_EDGES);
		e = el_get_actual(el_din);
		printf ("capacity = %u\n", e->capacity);
		printf ("nodeOrig = %u\n", e->nodeOrig);
		printf ("nodeDest = %u\n", e->nodeDest);
	}while(el_avance(el_din)== 0);
	
	el_clean(el_din);
	el_destroy(el_din);
	el_din= NULL;
	assert(el_get_size(el_din) == 0);
}
END_TEST


START_TEST ( test_start_avance_del_el )
{
	el_din = el_create ();
	assert (el_din != NULL);

	for(i=0; i < CANT_EDGES ; i++){
		e = edge_create(i , i , i+1);
		el_add_edge(el_din, e);
		e = el_get_actual(el_din);
		assert (i== e->capacity);
		assert (i== e->nodeOrig);
		assert (i+1== e->nodeDest);
	}

	assert(el_get_size(el_din) == CANT_EDGES);
	el_start(el_din);
	do{
		assert (i<= CANT_EDGES);
		e = el_get_actual(el_din);
		printf ("capacity = %u\n", e->capacity);
		printf ("nodeOrig = %u\n", e->nodeOrig);
		printf ("nodeDest = %u\n", e->nodeDest);
	}while(el_avance(el_din)== 0);

	for(i=0; i < CANT_EDGES -10 ; i++){
		el_del_edge(el_din);
	}

	assert(el_get_size(el_din) == 10);
	el_clean(el_din);
	el_destroy(el_din);
	el_din= NULL;
	assert(el_get_size(el_din) == 0);
	
}
END_TEST

Suite *edge_list_suite (void)
{
	Suite *s = suite_create ("edge_list");
	TCase *tc_commands = tcase_create ("Operationes");

	/* Comandos */
	tcase_add_test (tc_commands, test_create_destroy_empty_el);
	tcase_add_test (tc_commands, test_add_edge_el);
	tcase_add_test (tc_commands, test_create_clean_destroy_el);
	tcase_add_test (tc_commands, test_check_size_el);
	tcase_add_test (tc_commands, test_start_avance_el);
	tcase_add_test (tc_commands, test_start_avance_del_el);
	suite_add_tcase (s,tc_commands);

	return s;
}
