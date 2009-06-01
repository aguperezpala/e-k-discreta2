/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * Constantes y macros varios
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */

#ifndef CONSTS_H
#define CONSTS_H


#define u32 unsigned int

/*! maxima cantidad de nodos */
#define MAX_N_NODES	7000


/* Funcion assert previa. NOTE: el ';' ya esta incluido en la definicion */
#ifdef __DEBUG
	#include <assert.h>
	#define ASSERT(x)	assert(x);
#else
	#define ASSERT(x)	
#endif

/* Tipo que es solo para wrapping para el color.
 * Permito colores negativos para el coloreo greedy.
 */
typedef signed short Color;


/** Algunos defines de utilidad */

#define max(a, b) ((a>b) ? a : b)
#define min(a, b) ((a<b) ? a : b)


/* Indica si el modo de input es soportado por la API */
#define ModoinputInvalido(x)	((x != 1) && (x != 2))


/* Indica si el modo de verbosidad es soportado por la API */
#define   VerbosidadInvalidaAumentar(x)   ((x != 0) && (x != 1) && (x != 2) && (x != 3))
#define   VerbosidadInvalidaImprimir(x)   ((x != 0) && (x != 1) && (x != 2))
#define   VerbosidadInvalidaColorear(x)   ((x != 0) && (x != 1))


/* Inidica si un código numérico ASCII representa un caracter A-Z ó a-z */
#define IsAscii(x)	( ((x > 64) && (x < 91)) || ((x > 97) && (x < 123)) )

/* Indica si en nodo pertenece a dicho edge.
 * bool nIsFromEdge(u32 n , edge_t * e )
 */
#define nIsFromEdge(n,e) ((e->nodeOrig == n) != (e->nodeDest == q))

/* Indica si el vértice 'x' está en la cola de E-K corrida nº 'c'  */
#define   NotInQueue(x,c)   (x->corrida < c)

#define   Transform(x)   ((x == 0) ? 's'

/* Imprime la cadena: "Lado (x,y): Flujo f" donde 'x', 'y' y 'f'
 * son valores u32. Si 'x' o 'y' son '0' o '1' son cambiados por
 * los caracteres 's' o 't' respectivamente */
#define   PrintFlowNum(x,y,f)  (((x != 0) && (x != 1) && (y != 0) && (y != 1)) ? \
				(printf ("Lado (%u,%u): Flujo %u\n", x, y, f);)  \
					 : ( \
				((x == 0) && (y != 0) && (y != 1)) ? \
				(printf ("Lado (s,%u): Flujo %u\n", y, f);) \
					 : ( \
				((x == 1) && (y != 0) && (y != 1)) ? \
				(printf ("Lado (t,%u): Flujo %u\n", y, f);) \
					 : ( \
				((x != 0) && (x != 1) && (y == 0)) ? \
				(printf ("Lado (%u,s): Flujo %u\n", x, f);) \
					 : ( \
				((x != 0) && (x != 1) && (y == 1)) ? \
				(printf ("Lado (%u,t): Flujo %u\n", x, f);) \
					 : ( \
				(printf ("Lado (s,t): Flujo %u\n");) \
					) ) ) ) ) \
				)
				
					 
/*					 
				(y == 0) ? \
				printf ("Lado (%u,s): Flujo %u\n", x, f); \
					 : ( \
				(x == 1) ? \
				printf ("Lado (t,%u): Flujo %u\n", y, f); \
					 : ( \
				(y == 1) ? \
				printf ("Lado (%u,t): Flujo %u\n", x, f); \
					 : ( \
				printf ("Lado (%u,%u): Flujo %u\n", x, y, f) \
					) ) ) )  )
*/					
					
#define   PrintFlowNum(x,y,f)  ((x != 0) && (y != 0(( ? \
					
					
				

#ifndef INLINE
# if __GNUC__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif

/*! STDIN flags (parametros) */
#define F_NUMERIC		"-numeric"		/* si es modo numerico */
#define F_VERBOSE		"-v"			/* si vamos a insertar verbosidad */
#define	F_MAX_FLOW		"-max-flow"		/* si queremos calcular max flow */
#define F_COLOUR		"-colour"		/* si vamos a calcular coloreo */
#define F_INCREMENTAL		"-inc"			/* calculamos incrementalmente */
#define F_PARTIAL		"-partial"		/* si vamos a calcular parcialmente */
#define F_COLOUR_TIME		"-ctime"		/* calculamos n veces el tiempo para coloreo*/
#define F_FLOW_TIME		"-ftime"		/* calc n veces flow */




#endif
