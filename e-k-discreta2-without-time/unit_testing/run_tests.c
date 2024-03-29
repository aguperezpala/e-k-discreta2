#include <check.h>
#include <stdlib.h> /* Para tener EXIT_XXX */
#include "test_node_stack.h"
#include "test_edge_list.h"
#include "test_greedy.h"
int main (void)
{
	int number_failed;
	SRunner *sr = srunner_create(NULL);
	srunner_add_suite(sr, node_stack_suite());
	srunner_add_suite(sr, edge_list_suite());
	srunner_add_suite(sr, greedy_suite());
	srunner_set_log(sr, "test.log");
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

