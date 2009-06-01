#include <stdio.h>
#include <stdlib.h>
#include "parser_args.h"
#include "consts.h"
#include "network.h"

#define F_NUMERIC		"-numeric"		/* si es modo numerico */
#define F_VERBOSE		"-v"			/* si vamos a insertar verbosidad */
#define	F_MAX_FLOW		"-max-flow"		/* si queremos calcular max flow */
#define F_COLOUR		"-colour"		/* si vamos a calcular coloreo */
#define F_INCREMENTAL		"-inc"			/* calculamos incrementalmente */
#define F_PARTIAL		"-partial"		/* si vamos a calcular parcialmente */
#define F_COLOUR_TIME		"-ctime"		/* calculamos n veces el tiempo para coloreo*/
#define F_FLOW_TIME		"-ftime"		/* calc n veces flow */



static void main_help (void)
{
	printf ("Modo de uso:\n"
	"NOTA: Las flags que requieren de un parametro adicional son las marcadas"
	"con un *.\n"
	"Para setear modo numerico: -numeric (por defecto es modo alfanumerico)\n"
	"* verbosidad: -v <grado>\n"
	"si vamos a calcular el flujo maximo: -max-flow\n"
	"si vamos a calcular coloreo: -colour\n"
	"*si vamos a agregar bloques incrementalmente: -inc <n>\n"
	"*si vamos a calcular parcialmente: -partial <m>\n"
	"*para ejecutar n veces para medir el tiempo: -ctime <n>\n"
	"*para ejecutar n veces para medir el flujo: -ftime <n>\n");
}
	



int main (int argc, char ** args)
{
	parserArgs_t * pa = NULL;
	int result = 0;
	
	pa = pa_create ();
	
	 		/*-2 si no es un parametro valido
 		-3 si se esperaba otro tipo de valor (numerico por ejemplo)
		-4 otro error
*/

	main_help ();
	if (argc <= 1) {
		printf ("Se requieren argumentos\n");
		return -1;
	}
	
	result = pa_parse (pa, argc, args);
	if (result < 0) {
		if (result == -2)
			printf ("Hay un parametro invalido\n");
		else if (result == -3)
			printf ("Se esperaba un valor numerico\n");
		return 1;
	}
	
#ifdef __DEBUG
	pa_print (pa);
#endif
	
	
	return 0;
}
