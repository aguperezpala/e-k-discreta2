#ifndef PARSER_ARGS_H
#define PARSER_ARGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
		argc >= 0
		args != NULL
*/
void pa_parse (parserArgs_t * pa, int argc, char ** args);













#endif
