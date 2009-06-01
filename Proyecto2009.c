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
	EstadoNetwork * estado = NULL;
	int result = 0, err = 0, inputMode = 0;
	int i = 0, blockReadSize = 0, flowsRun = 0;
	bool finish = false;
	
	
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
	
	/* creamos el network */
	estado = network_create ();
	if (estado == NULL) {
		printf ("No se pudo crear el network, memoria insuficiente\n");
		return 1;
	}
	/* vemos si es modo numerico o alfabetico */
	if (pa_is_numeric (pa))
		inputMode = 2;
	else
		inputMode = 1;
	/* inicializamos */
	err = Inicializar(estado, inputMode);
	
	if (err == 0){
		printf ("No se pudo inicializar el network\n");
		return 1;
	}
	
	/* Ahora vamos a verificar si debemos ingresar en forma de bloques o en forma
	 * normal los lados */
	blockReadSize = pa_incremental (pa);
	flowsRun = pa_partial (pa)
	
	if (blockReadSize > 0){
		/* tenemos que leer en forma de bloque */
		while (!finish) {
			for (i = 0; i < blockReadSize && !finish; i++) {
				/* leemos un lado y nos fijamos si debemos salir */
				finish = LeerUnLado(estado, inputMode) == 0;
			}
			/* ahora vemos si tenemos que aumentar el flujo m veces
			 * o si lo tenemos que aumentar hasta el final */
			
			if (flowsRun > 0) {
				/* entonces debemos aumentar m veces el flujo */
				err = 0;
				for (i = 0; i < flowsRun && err == 0; i++) {
					err = AumentarFlujo (estado, pa_verbose (pa));
				}
			} else 
				/* simplemente aumentamos el flujo */
				while (err == 0)
					err = AumentarFlujo (estado, pa_verbose (pa));
		}
	} else {
		/* tomamos primero todos los lados */
		while (!finish)
			finish = LeerUnLado(estado, inputMode) == 0;
		
		err = 0;
		/* simplemente aumentamos el flujo */
		while (err == 0)
			err = AumentarFlujo (estado, pa_verbose (pa));
	
	
	
	return 0;
}
