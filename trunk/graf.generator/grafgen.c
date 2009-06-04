#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <assert.h>
#include <stdbool.h>

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
	
	ASSERT ((string != NULL) && (num != NULL))
	
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
	
	
	assert (list != NULL);
	
	aux = g_list_first (list);
	
	while (aux != NULL) {
		if (*((unsigned int) aux->data) == n) {
			del = aux;
			g_list_remove_link (list, del);
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
	int least = 0, x = 0;
	unsigned int *number = NULL;
	
	/*! bien ineficiente como la gran choripan */
	assert (from < to);
	assert (to - from < nCount);
	x = (to - from) / nCount;
	
	for (least = 0; least < nCount; least += x) {
		number = (unsigned int *) malloc (sizeof (unsigned int));
		*number = from;
		if (from != exept)
			result = g_list_append (result, number);
		from += x;
	}
	
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
	unsigned int backSide = 0;
	unsigned int flow = 0;
	char dataOut[100];
	GList * side = NULL;
	
	assert (f != NULL);
	assert (network != NULL);
	assert (network != NULL);
	
	/* bien ineficiente :D */
	for (i = 0; i < g_list_length (network); i++) {
		side = g_list_nth_data (network, i);
		for (j = 0; j < g_list_length (side); j++) {
			backSide = *((unsigned int) g_list_nth_data (side, j));
			/* eliminamos el nodo para evitar que haya duplicados */
			exists_and_delete (network[backSide], i);
			flow = (unsigned int) random () % MAX_FLOW_SIDE;
			sprintf (dataOut, "%u%u %u\n",i,j,flow);
			fprintf (f, dataOut);
		}
	}
}

int main (int argc, char ** args)
{
	long int n = 0, m = 0;
	unsigned int i = 0;
	int from = 0, to = 0, nCount = 0;
	char * fName = NULL;
	bool isNumeric = false;
	FILE * file = NULL;
	GList * network = NULL;
	GList * side = NULL;
	
	help();
	if (argc < 5)
		return -1;
	
	/* cargamos los argumentos */
	
	if (!is_int (args[1], &n) {
		ExitBadArg(1);
	}
	if (!is_int (args[2], &m) {
		ExitBadArg(2);
	}
	if (!is_int (args[3], &disNumeric) {
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
	nCount = (random () % (to - from)) - 1;
	side = generate_neighbour (from, to, 1, nCount);
	
	/*! t es vacio */
	
	side = g_list_alloc ();
	g_list_append (network, side);
	for (i = 2; i < n; i++) {
		from = (random () % n) - 1;
		to = n;
		nCount = (random () % (to - from)) - 1;
		side = generate_neighbour (from, to, 0, nCount);
		g_list_append (network, side);
	}	
	
	print_and_check_network (file, network);
	
	return 0;
}