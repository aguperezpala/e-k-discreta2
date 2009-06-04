#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#define ExitBadArg(i)	printf ("Error en el argumento %d\n",i);return 1;
#define MAX_FLOW_SIDE	0x000FFFFF
static void help (void)
{
	printf ("\n\nModo de uso:\n"
	"grafget <n> <m> <numeric> <nombre_archivo>\n"
	"n: cantidad de vectices\n"
	"m: cantidad de lados\n"
	"<numeric>: 1 si es numerico 0 caso contrario\n"
	"nombre_archivo: donde se almacenta el grafo\n"
	"TODOS LOS ARGUMENTOS SON OBLIGATORIOS\n"
	);
}


static bool is_int (const char *string, long int *num)
{
	bool result = false;
	char *endptr = '\0';
	size_t size = 0;
	
	assert ((string != NULL) && (num != NULL));
	
	*num = strtol (string, &endptr, 10);
	size = strlen (string);
	
	if ((size > 0) && (*endptr == '\0'))
		result = true;
	
	return result;
}

/* funcion que devuelve true si existe ese nodo en esa lista, falso cc
	REQUIRES:
		list != NULL
	RETURNS:
		true si existe n en la lista
		false caso contrario
*/
static void exists_and_delete (GList * list, unsigned int n)
{
	GList * aux = NULL;
	GList * del = NULL;
	unsigned int * num = NULL;
	
	
	assert (list != NULL);
	
	aux = g_list_first (list);
	
	while (aux != NULL) {
		num = (unsigned int *) aux->data;
		if (num != NULL && *num == n) {
			del = aux;
			list = g_list_remove_link (list, del);
			g_list_free (del);
			break;
		}
			
		aux = aux->next;
	}
	
	
}
	
/* funcion que genera una lista de nCount vecinos desde from hasta to exepto exept
	REQUIRES:
		from < to
		nCount > to - from
	RETURNS:
		list of neighbour
*/
static GList * generate_neighbour (unsigned int from, unsigned int to, 
				   unsigned int exept, unsigned int nCount /*cantidad de vecinos*/)
{
	GList * result = NULL;
	unsigned int least = 0, x = 0;
	unsigned int *number = NULL;
	
	/*! bien ineficiente como la gran choripan */
	assert (from < to);
	assert (to - from > nCount);
	x = (to - from) / nCount;
	
	for (least = 0; least < nCount; least++) {
		
		if (from != exept){
			number = (unsigned int *) malloc (sizeof (unsigned int));
			*number = from;
			result = g_list_append (result, number);
		}
		from += x;
	}
	result = g_list_first (result);
	assert (result != NULL);
	return result;
}

/* Funcion que imprime y chequea que no haya 2 lados iguales
	REQUIRES:
		f != NULL
		network != NULL
*/
static void print_and_check_network (FILE * f, GList * network)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int * backSide = 0;
	unsigned int flow = 0;
	char dataOut[100];
	GList * side = NULL;
	GList * backList = NULL;
	
	assert (f != NULL);
	assert (network != NULL);
	assert (network != NULL);
	
	/* bien ineficiente :D */
	for (i = 0; i < g_list_length (network); i++) {
		side = g_list_nth_data (network, i);
		for (j = 0; j < g_list_length (side) && i != 1; j++) {
			backSide = ((unsigned int *) g_list_nth_data (side, j));
			if (backSide != NULL) {
				/* eliminamos el nodo para evitar que haya duplicados */
				backList = g_list_nth_data (network, *backSide);
				if (backList != NULL)
					exists_and_delete ( backList, i);
				flow = (unsigned int) random () % MAX_FLOW_SIDE;
				sprintf (dataOut, "%u.%u %u",i,j,flow);
				fprintf (f, "%s\n", dataOut);
			}
		}
	}
}

int main (int argc, char ** args)
{
	long int n = 0, m = 0;
	unsigned int i = 0;
	int from = 0, to = 0, nCount = 0;
	char * fName = NULL;
	long int isNumeric = false;
	FILE * file = NULL;
	GList * network = NULL;
	GList * side = NULL;
	
	help();
	if (argc < 5)
		return -1;
	
	/* cargamos los argumentos */
	
	if (!is_int (args[1], &n)) {
		ExitBadArg(1);
	}
	if (!is_int (args[2], &m)) {
		ExitBadArg(2);
	}
	if (!is_int (args[3], &isNumeric)) {
		ExitBadArg(3);
	}
	
	fName = args[4];
	
	file = fopen (fName, "w");
	if (file == NULL) {
		printf ("Erro creando el archivo\n");
		return 1;
	}
	
	/* creamos el network */
	/* cargamos a s y nunca a t */
	from = (random () % n) - 1;
	to = n;
	nCount = (m % (to - from)) - 1;
	side = generate_neighbour (from, to, 1, nCount);
	network = g_list_append (network, side);
	/*! t es vacio */
	
	side = generate_neighbour (0, 3, 0, 2);
	network = g_list_append (network, side);
	for (i = 2; i < n; i++) {
		from = abs ((random () % n) - 1);
		to = n;
		nCount = (m % (to - from - 1)) + 1;
		side = generate_neighbour (from, to, 0, nCount);
		network = g_list_append (network, side);
	}	
	
	fclose (file);
	
	print_and_check_network (file, network);
	for (i = 0; i < n; i++) {
		g_list_free (g_list_nth_data (network, i));
	}
	return 0;
}