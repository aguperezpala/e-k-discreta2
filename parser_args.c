#include "parser_args.h"


struct _parserArgs {
	
	
};


/* Constructor 
RETURNS:
parserArgs != NULL
*/
parserArgs_t * pa_create (void)
{
	parserArgs_t * result = NULL;
	
	/* allocamos */
	result = (parserArgs_t *) calloc (1, sizeof (struct _parserArgs));
	/*! inicializamos */
	
	return result;
}

/* Destructor
REQUIRES:
pa != NULL
*/
void pa_destroy (parserArgs_t * pa)
{
	/* pre */
	ASSERT (pa != NULL)
	
	/* liberamos */
	free (pa);
}

/* Funcion que rellena la estructura con los campos determinados
REQUIRES:
pa != NULL
argc >= 0
args != NULL
*/
void pa_parse (parserArgs_t * pa, int argc, char ** args)
{
	
	/* pres */
	ASSERT (pa != NULL)
	ASSERT (argc >= 0)
	ASSERT (args != NULL)
	
	/*! aca va la papocha :p */
	
}
