/* MACK-EK versiÃƒÂ³n 1.0
 * ImplementaciÃƒÂ³n eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     PÃƒÂ©rez Paladini, AgustÃƒÂ­n
 *	     Soldevilla, Mallku R.
 *
 * RevisiÃƒÂ³n: Penazzi, Daniel
 *
 */




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser_args.h"
#include "consts.h"
#include "network.h"




static void main_help (void)
{
	printf (
	
	"\n\n\t\t    Bienvenido a MACK-EK version 1.0\n\nModo de uso:\n\n"
	"  Para setear:  ·modo numerico: -numeric (por defecto es modo alfanumerico)\n"
	"		·verbosidad: -v <grado>\n\n"
	"  Si vamos a calcular:  ·el flujo maximo: -max-flow\n"
	"			·coloreo: -colour\n"
	"			·parcialmente: -partial <m>\n\n"
	"  Si vamos a agregar bloques de forma incremental: -inc <n>\n\n"
	"  Para ejecutar n veces:  ·para medir el tiempo: -ctime <n>\n"
	"			  ·para medir el flujo: -ftime <n>\n\n"
	"NOTA: son obligatorios los campos <>\n"
	       );
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
	while (!finish) {
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
		err = 0;
		if (flowsRun > 0) {
			/* entonces debemos aumentar m veces el flujo */
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
	int err, verbose, flowsRun;
	
	
	
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
	
	err = 0;
	/* chequeamos si debemos aumentar parcialmente */
	if (flowsRun > 0) {
		/* entonces debemos aumentar m veces el flujo */
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
		printf ("\nError de ejecuciÃƒÂ³n: Ã‚Â¡se requieren argumentos!\n\n");
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
	estado = network_create (pa_work_colour(pa));
	if (estado == NULL) {
		printf ("No se pudo crear el network, memoria insuficiente\n");
		return 1;
	}
	/* vemos si es modo numerico o alfabetico */
	if (pa_is_numeric (pa))
		inputMode = 2;
	else
		inputMode = 1;
	
	
	/** NOTE <EMPIEZA LA JODA> */
	/* inicializamos el network */
	err = Inicializar(estado, inputMode);
	
	
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
	
	
	/** ### ### Para calcular el tiempo hay que setear verbose a 0 ### ### */
	/*verbose = 0;*/
	/*! HACERLO EFICIENTE A ESTO!, falta calcular el tiempo */
	/* ahora vamos a ver cuantas veces tenemos que repetir esto */
	for (i = pa_max_flow_repeat (pa); i > 0 && err != 2; i--) {
		/* ahora lo que hacemos es aumentar el flow */
		/*! debemos inicializar esto! */
		err = Inicializar(estado, inputMode);
		while (err == 0)
			err = AumentarFlujo (estado, verbose);
		
	}
	
	/* ahora vamos a verificar si debemos buscar color o no */
	if (pa_work_colour (pa)) {
		/* ahora vamos a chequear cuantas veces deberiamos correr el
		 * coloreo */
		for (i = 0 ; i <= pa_colour_repeat (pa); i++) {
			/*!###	### <<<Inicializamos?????> ### ###*/
			colours = ColorearNetwork (estado, verbose);
		}
	}
	/* imprimimos el flujo solo si verbose <= 1*/
	if (verbose <= 2)
		ImprimirFlujo (estado, verbose);
	
	
	return 0;
}
