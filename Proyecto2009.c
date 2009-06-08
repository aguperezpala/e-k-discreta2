/* MACK-EK versiÃ³n 1.0
 * ImplementaciÃ³n eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     PÃ©rez Paladini, AgustÃ­n
 *	     Soldevilla, Mallku R.
 *
 * RevisiÃ³n: Penazzi, Daniel
 *
 */




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "parser_args.h"
#include "consts.h"
#include "network.h"
#include "cycle_ms.h"



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
	"  Para ejecutar n veces:  ·colorear y medir el tiempo: -ctime <n>\n"
	"			  .colorear y medir ciclos de cpu empleados: -ccycles <n>\n"
	"			  ·buscar flujo maximal y medir el tiempo: -ftime <n>\n\n"
	"			  ·buscar flujo maximal y medir ciclos de cpu empleados: -fcycles <n>\n\n"
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
			
		if (finish)
			estado->maximal = true;
		else
			estado->maximal = false;
		/* imprimimos el flujo */
		ImprimirFlujo (estado, verbose);
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
	/* Para medir ciclos de CPU consumidos */
	ticks residuo = 0,t1 = 0, t2 = 0;
	ticks *mediciones = NULL;
	ticks moda = 0;
	/* Para medir tiempo de procesador empleado */
	clock_t start=0,end=0;
	/* Resultado final de las mediciones */
	long double measure = 0;
	
	
	/* creamos el parserArgs */
	pa = pa_create ();


	main_help ();
	if (argc <= 1) {
		printf ("\nError de ejecucion: ¡se requieren argumentos!\n\n");
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
	
	if(pa_work_flow (pa)){
		if (pa_timeMeasurement(pa)){
			/* primero vamos a hacer una corrida normal y cargar 
					el grafo */
			start = clock(); 
			err = normal_read (estado, pa, inputMode);
			end = clock();
			measure +=((long double)(end-start))/CLOCKS_PER_SEC;
			
			/* Las siguientes iteraciones consistirán en Inicializar el network
				y buscar el flujo maximal
			 */
			
			for (i = pa_max_flow_repeat (pa)-1; i > 0 && err != 2; i--){
				/* ia! */
				start = clock();
				
				err = Inicializar(estado, inputMode);
			
				/* ahora lo que hacemos es aumentar el fucking flow */
				while (err == 0)
					err = AumentarFlujo (estado, 0);
				/* Listo. Paramos el reloj */
				end = clock();
				measure +=((long double)(end-start))/((long double)CLOCKS_PER_SEC);
			}
			/* Calculamos un promedio */
			measure = measure/pa_max_flow_repeat(pa);
			printf("\nTiempo estimado: %Lf\n",measure);
		
		}
		if(pa_cycleMeasurement(pa)){
			mediciones = (ticks*)calloc(pa_max_flow_repeat (pa),sizeof(ticks));
			/* Los ciclos que debemos restar son los necesarios para ejecutar 2 
			   veces CPUID, 2 veces RDTSC y 2 veces el "left-shifting" más el 
			   "or" bit a bit. 
			*/
			residuo = getResiduo ();
			
			/* primero vamos a hacer una corrida normal y cargar 
				el grafo */
			t1=getticks();
			err = normal_read (estado, pa, inputMode);
			t2=getticks();
			mediciones[pa_max_flow_repeat (pa)-1] = (t2-t1)-residuo;
			
			/* Las siguientes iteraciones consistirán en Inicializar el network
				y buscar el flujo maximal
			 */
			verbose = pa_verbose (pa);
			for (i = pa_max_flow_repeat (pa)-1; i > 0 && err != 2; i--){
				residuo = getResiduo ();
				t1=getticks();
				err = Inicializar(estado, inputMode);
			
				/* ahora lo que hacemos es aumentar el flujo */
				while (err == 0)
				
					err = AumentarFlujo (estado, 0);
				
				
				t2=getticks();
				mediciones[i-1] = (t2-t1)-residuo;
			}
			moda = calcularModa(mediciones,pa_max_flow_repeat (pa));
			
			printf("\nCiclos de CPU empleados: %llu\n",moda);
			/* Liberamos recursos */
			/*free(mediciones);
			mediciones=NULL;*/
		}
		if(!pa_max_flow_repeat (pa)){
			/* {No han pedido realizar medición alguna} */
			blockReadSize = pa_incremental (pa);
			verbose = pa_verbose (pa);
			/* primero vamos a hacer una corrida normal y cargar el grafo */
			if (blockReadSize > 0){
				err = block_read (estado, pa, inputMode);
			} else {
				err = normal_read (estado, pa, inputMode);
			}
			/* ahora lo que hacemos es aumentar el fucking flow */
			while (err == 0)
				err = AumentarFlujo (estado, verbose);
			
			if (blockReadSize <= 0)
				/* imprimimos el flujo */
				ImprimirFlujo (estado, verbose);
		}
	}
	
	/* ahora vamos a verificar si debemos buscar color o no */
	if (pa_work_colour (pa)){
		if(pa_timeMeasurement(pa)){
			/* primero vamos a hacer una corrida normal y cargar 
				el grafo */
			start = clock(); 
			err = normal_read (estado, pa, inputMode);
			colours = ColorearNetwork (estado, 0);
			end = clock();
			printf("\nFirst Coloring - Tiempo estimado: %Lf\n",((long double)(end-start))/((long double)CLOCKS_PER_SEC));
			
			/* Las siguientes iteraciones consistirán en Inicializar el grafo
				y colorear
			 */
			
			for (i = pa_colour_repeat (pa); i > 0; i--) {
				/* ia! */
				start = clock(); 
				
				err = Inicializar(estado, inputMode);
				colours = ColorearNetwork (estado, 0);
								
				/* Listo. Paramos el reloj */
				end = clock();
				measure +=((long double)(end-start))/((long double)CLOCKS_PER_SEC);
			}
			/* Calculamos un promedio */
			measure = measure/pa_colour_repeat(pa);
			printf("\nTiempo estimado: %Lf\n",measure);
		}
		if(pa_cycleMeasurement(pa)){
			mediciones = (ticks*)calloc(pa_colour_repeat (pa),sizeof(ticks));
			/* Los ciclos que debemos restar son los necesarios para ejecutar 2 
			   veces CPUID, 2 veces RDTSC y 2 veces el "left-shifting" más el 
			   "or" bit a bit. 
			*/
			residuo = getResiduo();
			
			/* primero vamos a hacer una corrida normal y cargar 
				el grafo */
			t1=getticks();
			err = normal_read (estado, pa, inputMode);
			colours = ColorearNetwork (estado, 0);			
			t2=getticks();
			printf("\nFirst Coloring - Ciclos de CPU consumidos: %llu",(t2-t1)-residuo);
		
			for (i = pa_colour_repeat (pa); i > 0 && err != 2; i--){
				t1=getticks();

				err = Inicializar(estado, inputMode);
				colours = ColorearNetwork (estado, 0);
																					
				t2=getticks();
				mediciones[i-1] = (t2-t1)-residuo;
			}
			moda = calcularModa(mediciones,pa_colour_repeat (pa));
			printf("\nCiclos de CPU consumidos: %llu\n",moda);
			/* Liberamos recursos */
			/*free(mediciones);
			mediciones=NULL;*/
		}
		if(!pa_colour_repeat (pa)){
			/* {No han pedido realizar medición alguna} */
			/* Ahora vamos a verificar si debemos ingresar en forma de 
			 bloques o en forma normal los lados */
			blockReadSize = pa_incremental (pa);
			verbose = pa_verbose (pa);
			/* primero vamos a hacer una corrida normal y cargar el grafo */
			if (blockReadSize > 0){
				err = block_read (estado, pa, inputMode);
			} else {
				err = normal_read (estado, pa, inputMode);
			}
			/* ahora lo que hacemos es aumentar el fucking flow */
			colours = ColorearNetwork (estado, verbose);
		}
	}
	/* Liberamos recursos */
	/*pa_destroy(pa); pa = NULL;
	network_destroy (estado); estado = NULL;*/
	
	return 0;
}
