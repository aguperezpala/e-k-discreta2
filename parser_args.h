#ifndef PARSER_ARGS_H
#define PARSER_ARGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "consts.h"
/* definimos la estructura que a su vez va a tener almacenado los flags (args)
 * y las opciones de las mismas (seria una especie de "flagsFields struct")
 */
typedef struct _parserArgs parserArgs_t;


/* Constructor 
	RETURNS:
		parserArgs != NULL
*/
parserArgs_t * pa_create (void);

/* Destructor
	REQUIRES:
		pa != NULL
*/
void pa_destroy (parserArgs_t * pa);

/* Funcion que rellena la estructura con los campos determinados
	REQUIRES:
		pa != NULL
		argc >= 1
		args != NULL
	RETURNS:
 	!error:
 		= 0
 	error:
 		-2 si no es un parametro valido
 		-3 si se esperaba otro tipo de valor (numerico por ejemplo)
		-4 otro error
*/
int pa_parse (parserArgs_t * pa, int argc, char ** args);


/*! ~~~~~~~~	Funciones para obtener los flags ~~~~~~~*/
/* isNumeric 
	REQUIRES:
		pa != NULL
*/
bool pa_is_numeric (parserArgs_t * pa);


/* calculamos el flujo?
	REQUIRES:
		pa != NULL
*/
bool pa_work_flow (parserArgs_t * pa);

/* calculamos el coloreo?
	REQUIRES:
		pa != NULL
*/
bool pa_work_colour (parserArgs_t * pa);

/* verbose
	REQUIRES:
		pa != NULL
*/
bool pa_verbose (parserArgs_t * pa);

/* tenemos que leer incrementalmente?
	REQUIRES:
		pa != NULL
	RETURNS:
		0 en caso de que no
		> 0 caso de que si (indicando cada cuantas lineas tenemos que leer)
*/
int pa_incremental (parserArgs_t * pa);


/* tenemos que correr parcialmente el algoritmo??
	REQUIRES:
		pa != NULL
	RETURNS:
		0 en caso de que no
		> 0 caso de que si (indicando cuantas corridas tenemos que hacer)
*/
int pa_partial (parserArgs_t * pa);


/* tenemos que repetir el algoritmo de flujo para medir el tiempo
	REQUIRES:
		pa != NULL
	RETURNS:
		0 en caso de que no
		> 0 caso de que si (indicando cuantas veces)
*/
int pa_max_flow_repeat (parserArgs_t * pa);

/* tenemos que repetir el algoritmo de coloreo para medir el tiempo
	REQUIRES:
		pa != NULL
	RETURNS:
		0 en caso de que no
		> 0 caso de que si (indicando cuantas corridas tenemos que hacer)
*/
int pa_colour_repeat (parserArgs_t * pa);



#ifdef __DEBUG

/* Imprime la estructura
	REQUIRES:
		pa != NULL
*/
void pa_print (parserArgs_t * pa);

#endif






#endif
