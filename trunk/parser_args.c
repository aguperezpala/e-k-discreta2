#include "parser_args.h"

/*! algunos defines internos */
/* Para flowAndColour vamos a dividir los 2 primeros bytes para flujo y los
 * 2 otros bytes para coloreo */
#define getFlowPrint(x)		((x & 0xFFFF0000) >> 16)
#define getColourPrint(x)	(x & 0x0000FFFF)
#define setFlowPrint(x)		(x << 16)
#define setColourPrint(x)	(x)

struct _parserArgs {
	bool isNumeric;		/* para saber si es numerico */
	int flowAndColour;	/* si queremos imprimir flow y coloreo */
	int verbose;		/* grado de verbosidad */
	int incremental;	/* si tenemos que leer incrementalmente y cuantas lineas */
	int partialRun;		/* corrimiento parcial, m */
	bool timeMeasurement; /* pidieron medición del tiempo? */
	bool cyclesMeasurement; /* pidieron medición de los ciclos de CPU? */
	int colourRepeat;	/* cantidad de repeticiones para el colore */
	int maxFlowRepeat;	/* cantidad de repeticiones para el flujo */	
};



/*! Funciones internas */
/* Revisa si la cadena string está compuesta sólo por caracteres numéricos.
 * En ese caso devuelve en num la conversión del string hacia decimales
 * 
 * PRE: string != NULL && num != NULL
 *
 *  res = is_int (string, num)
 *
 * POS: (res == true && num == int_format (string) &&
 *	  < V i : 0 <= i < strlen(string) : string[i] € {0, ..., 9} > )  ||
 * 	(res == false &&
 *	  < E i : 0 <= i < strlen(string) : string[i] ¬€ {0, ..., 9} > )
 */
static bool is_int (const char *string, long int *num)
{
	bool result = false;
	char *endptr = '\0';
	size_t size = 0;
	
	ASSERT ((string != NULL) && (num != NULL))
	
	*num = strtol (string, &endptr, 10);
	size = strlen (string);
	
	if ((size > 0) && (*endptr == '\0'))
		result = true;
	
	return result;
}



/* funcion que mapea el argumento a un entero como sigue
REQUIRES:
	arg != NULL
RETURNS:
	0	"-numeric"
	1	"-v"
	2	"-max-flow"
	3	"-colour"
	4	"-inc"
	5	"-partial"
	6	"-ctime"
	7	"-ftime"
	
	-1 caso de error
*/
static int pa_map_arg (char * arg)
{
	int result = -1;
	
	ASSERT(arg != NULL)
	
	if (strcmp (arg, F_NUMERIC) == 0)
		result = 0;
	else if (strcmp (arg, F_VERBOSE) == 0)
		result = 1;
	else if (strcmp (arg, F_MAX_FLOW) == 0)
		result = 2;
	else if (strcmp (arg, F_COLOUR) == 0)
		result = 3;
	else if (strcmp (arg, F_INCREMENTAL) == 0)
		result = 4;
	else if (strcmp (arg, F_PARTIAL) == 0)
		result = 5;
	else if (strcmp (arg, F_COLOUR_TIME) == 0)
		result = 6;
	else if (strcmp (arg, F_FLOW_TIME) == 0)
		result = 7;
	else 
		result = -1;
	
	return result;
}


/* Funcion que matchea cada flag devolviendo si se requiere un parametro adicional
 * Por ejemplo -v requiere un parametro adicional que es el grado de verbosidad
 * si este parametro no corresponde entonces se devuelve -1
 	REQUIRES:
 		args ** != NULL
 		argc	>= 2
 		1 =< i < argc	(posicion del parametro a calcular)
 	RETURNS:
 	!error:
 		>= 0	si el flag tomaba otro parametro
 		-1	si es correcto pero no tomaba otro parametro
 	
 	error:
 		-2 si no es un parametro valido
 		-3 si se esperaba otro tipo de valor (numerico por ejemplo)
		-4 otro error
*/
static int pa_real_parse (char ** args, int argc, int i)
{
	int result = -3;
	long int param = 0;
	
	ASSERT (args != NULL)
	ASSERT (argc >= 2)
	ASSERT (i < argc && i >= 1)
	
	/* buscamos el commando */
	switch (pa_map_arg (args[i])) {
		case 0:
			result = -1;
			break;
		case 1:
			/* es verbose, por lo que i+1 deberia tener el entero */
			if (i + 1 < argc && is_int (args[i+1], &param))
				result = (int) param;
			else
				result = -3;
			break;
		case 2:
			result = -1;
			break;
		case 3:
			result = -1;
			break;
		case 4:
			if (i + 1 < argc && is_int (args[i+1], &param))
				result = (int) param;
			else
				result = -3;
			break;
		case 5:
			if (i + 1 < argc && is_int (args[i+1], &param))
				result = (int) param;
			else
				result = -3;
			break;
		case 6:
			if (i + 1 < argc && is_int (args[i+1], &param))
				result = (int) param;
			else
				result = -3;
			break;
		case 7:
			if (i + 1 < argc && is_int (args[i+1], &param))
				result = (int) param;
			else
				result = -3;
			break;
			
		default:
			result = -3;
			break;
			
	}
	
	return result;
}



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
	/* por defecto como tenemos calloc = 0 todo */
	
	
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
int pa_parse (parserArgs_t * pa, int argc, char ** args)
{
	int i = 1;
	int result = 0;
	
	/* pres */
	ASSERT (pa != NULL)
	ASSERT (argc >= 1)
	ASSERT (args != NULL)
	
	/*! aca va la papocha :p */


	while (i < argc && result > -2) {
		
		result = pa_real_parse(args, argc, i);
		
		switch (pa_map_arg (args[i])) {
			case 0:
				if (result == -1) {
					pa->isNumeric = true;
					result = 0;
				}
				break;
			case 1:
				if (result >= 0) {
					pa->verbose = result;
					/* aumentamos en uno i ya que debemos
					 * saltear el proximo argumento */
					i++;
					result = 0;
				}	
				break;
			case 2:
				if (result == -1) {
					pa->flowAndColour |= setFlowPrint(1);
					result = 0;
				}
				break;
			case 3:
				if (result == -1) {
					pa->flowAndColour |= setColourPrint(1);
					result = 0;
				}
				break;
			case 4:
				if (result >= 0) {
					pa->incremental = result;
					i++;
				}
				break;
			case 5:
				if (result >= 0) {
					pa->partialRun = result;
					i++;
				}
				break;
			case 6:
				if (result >= 0) {
					pa->colourRepeat = result;
					i++;
				}
				break;
			case 7:
				if (result >= 0) {
					pa->maxFlowRepeat = result;
					i++;
				}
				break;
				
			default:
				result = -3;
				break;
			
		}
		i++;
	}
	
	return result;
	
}


/*! ~~~~~~~~	Funciones para obtener los flags ~~~~~~~*/

bool pa_is_numeric (parserArgs_t * pa)
{
	ASSERT (pa != NULL)
	
	return pa->isNumeric;
}


bool pa_work_flow (parserArgs_t * pa)
{
	ASSERT (pa != NULL)
	
	return (getFlowPrint(pa->flowAndColour) != 0);
}


bool pa_work_colour (parserArgs_t * pa)
{
	ASSERT (pa != NULL)
	
	return (getColourPrint(pa->flowAndColour) != 0);
}

int pa_verbose (parserArgs_t * pa)
{
	ASSERT (pa != NULL)
	
	return pa->verbose;
}



int pa_incremental (parserArgs_t * pa)
{
	ASSERT (pa != NULL)
	
	return pa->incremental;
}



int pa_partial (parserArgs_t * pa)
{
	ASSERT (pa != NULL)
	
	return pa->partialRun;
}

int pa_max_flow_repeat (parserArgs_t * pa)
{
	ASSERT (pa != NULL)
	
	return pa->maxFlowRepeat;
}


int pa_colour_repeat (parserArgs_t * pa)
{
	ASSERT (pa != NULL)
	
	return pa->colourRepeat;
}


#ifdef __DEBUG

/* Imprime la estructura
	REQUIRES:
		pa != NULL
*/
void pa_print (parserArgs_t * pa)
{
	ASSERT (pa != NULL)
	
	
	printf ("Es modo numerico?\t");
	
	if (pa->isNumeric)
		printf ("true\n");
	else
		printf ("false\n");
	
	printf ("Hay que imprimir flujo\t");
	if (pa_work_flow (pa))
		printf ("true\n");
	else
		printf ("false\n");
	
	printf ("Hay que imprimir color\t");
	if (pa_work_colour (pa))
		printf ("true\n");
	else
		printf ("false\n");

	printf ("verbose: %d\n", pa->verbose);
	printf ("incremental: %d\n", pa->incremental);
	printf ("partialRun: %d\n", pa->partialRun);
	printf ("ColourRepeat: %d\n", pa->colourRepeat);
	printf ("FlowRepeat: %d\n", pa->maxFlowRepeat);
}
	
	
#endif



