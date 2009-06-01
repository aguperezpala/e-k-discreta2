#include <stdio.h>
#include <stdlib.h>
#include "parser_args.h"
#include "consts.h"
#include "network.h"




static void main_help (void)
{
	printf ("\n\n\n\nModo de uso:\n"
	"Para setear modo numerico: -numeric (por defecto es modo alfanumerico)\n"
	"verbosidad: -v <grado>\n"
	"si vamos a calcular el flujo maximo: -max-flow\n"
	"si vamos a calcular coloreo: -colour\n"
	"si vamos a agregar bloques incrementalmente: -inc <n>\n"
	"si vamos a calcular parcialmente: -partial <m>\n"
	"para ejecutar n veces para medir el tiempo: -ctime <n>\n"
	"para ejecutar n veces para medir el flujo: -ftime <n>\n"
	"\n\nNOTA: son obligatorios los campos <>\n");
}
	





int main (int argc, char ** args)
{
	parserArgs_t * pa = NULL;
	int result = 0;
	
	/* creamos el parserArgs */
	pa = pa_create ();


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
