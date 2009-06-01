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
	

/* funcion que toma los lados en bloque
	REQUIRES:
		estado != NULL
		pa != NULL
	RETURNS:
		0 si no trabajamos el max flow (solo ingreso de lados)
		1 si no se puede seguir aumentando el flujo
		2 caso de error (AumentarFlujo)
*/
static int block_read (EstadoNetwork * estado, parserArgs_t * pa, int inputMode)
{
	bool finish = false;
	register int i = 0;
	int err = 0, verbose, flowsRun, blockReadSize;
	
	
	ASSERT (estado != NULL)
	ASSERT (pa != NULL)
	
	blockReadSize = pa_incremental (pa);
	flowsRun = pa_partial (pa);
	verbose = pa_verbose (pa);
	
	/* tenemos que leer en forma de bloque */
	while (!finish && err != 2) {
		for (i = 0; i < blockReadSize && !finish; i++) {
			/* leemos un lado y nos fijamos si debemos salir */
			finish = LeerUnLado(estado, inputMode) == 0;
		}
		
		/*! ahora vemos si debemos actualizar o no el flujo
		 * <<<Podriamos hacerlo mas eficiente separando toda esta
		 * cochinada en 2 ciclos, y chequear antes si tenemos que buscar
		 * o no el flujo>>>
		 */
		if (!pa_work_flow (pa))
			/* no vamos a buscar el flujo maximal */
			continue;
		/* ahora vemos si tenemos que aumentar el flujo m veces
		* o si lo tenemos que aumentar hasta el final */
		if (flowsRun > 0) {
			/* entonces debemos aumentar m veces el flujo */
			err = 0;
			for (i = 0; i < flowsRun && err == 0; i++) {
				err = AumentarFlujo (estado, verbose);
			}
		} else 
			/* simplemente aumentamos el flujo */
			while (err == 0)
				err = AumentarFlujo (estado, verbose);
	}
	return err;
}

/* funcion que actualiza el flujo pero tomando primero todos los datos
	REQUIRES:
		estado != NULL
		pa 	!= NULL
	RETURNS:
		0 si no trabajamos el max flow (solo ingreso de lados)
		1 si no se puede seguir aumentando el flujo
		2 caso de error (AumentarFlujo)
*/
static int normal_read (EstadoNetwork * estado, parserArgs_t * pa, int inputMode)
{
	bool finish = false;
	register int i = 0;
	int err = 0, verbose, flowsRun;
	
	
	
	ASSERT (estado != NULL)
	ASSERT (pa != NULL)
	
	
	flowsRun = pa_partial (pa);
	verbose = pa_verbose (pa);
	
	/* tomamos primero todos los lados */
	while (!finish)
		finish = LeerUnLado(estado, inputMode) == 0;
	
	/*! vamos a verificar si debemos calcular el flujo, o solo es para coloreo */
	if (!pa_work_flow (pa))
		/* no vamos a buscar el flujo maximal */
		return err;
	
	/* chequeamos si debemos aumentar parcialmente */
	if (flowsRun > 0) {
		/* entonces debemos aumentar m veces el flujo */
		err = 0;
		for (i = 0; i < flowsRun && err == 0; i++) {
			err = AumentarFlujo (estado, verbose);
		}
	} else 
		/* simplemente aumentamos el flujo */
		while (err == 0)
			err = AumentarFlujo (estado, verbose);
		
	return err;
}

int main (int argc, char ** args)
{
	parserArgs_t * pa = NULL;
	EstadoNetwork * estado = NULL;
	int result = 0, err = 0, inputMode, verbose, blockReadSize;
	register int i = 0;
	u32 colours = 0;
	
	
	
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
	
	if (err == 0){
		printf ("No se pudo inicializar el network\n");
		return 1;
	}
	
	
	/* Ahora vamos a verificar si debemos ingresar en forma de bloques o en forma
	 * normal los lados */
	blockReadSize = pa_incremental (pa);
	verbose = pa_verbose (pa);
	
	/* primero vamos a hacer una corrida normal y cargar el grafo */
	if (blockReadSize > 0){
		err = block_read (estado, pa, inputMode);
	} else {
		err = normal_read (estado, pa, inputMode);
	}
	
	/*! HACERLO EFICIENTE A ESTO!, falta calcular el tiempo */
	/* ahora vamos a ver cuantas veces tenemos que repetir esto */
	for (i = pa_max_flow_repeat (pa); i > 0 && err != 2; i--) {
		/* inicializamos el network */
		Inicializar(estado, inputMode);
		/* ahora lo que hacemos es aumentar el fucking flow */
		while (err == 0)
			err = AumentarFlujo (estado, verbose);
		
	}
	/* ahora vamos a verificar si debemos buscar color o no */
	if (pa_work_colour (pa)) {
		/* ahora vamos a chequear cuantas veces deberiamos correr el
		 * coloreo */
		for (i = pa_colour_repeat (pa); i > 0; i--) {
			/*! inicializamos aca siempre o no? */
			colours = ColorearNetwork (estado, verbose);
		}
	}
	/* imprimimos el flujo */
	ImprimirFlujo (estado, verbose);
	
	
	return 0;
}
