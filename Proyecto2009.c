#include <stdio.h>
#include <stdlib.h>
#include "parser_args.h"
#include "consts.h"
#include "network.h"

static void main_help (void)
{
	printf ("Modo de uso:\n"
	"



int main (int argc, char ** args)
{
	parserArgs_t * pa = NULL;
	int result = 0;
	
	pa = pa_create ();
	
	 		/*-2 si no es un parametro valido
 		-3 si se esperaba otro tipo de valor (numerico por ejemplo)
		-4 otro error
*/

	
	if (argc <= 1) {
		printf ("ingresaste < 1\n");
		return -1;
	}
	
	result = pa_parse (pa, argc, args);
	if (result < 0) {
		printf ("Ingreso mal algun parametro\n");
	}
	pa_print (pa);
	
	
	return 0;
}
