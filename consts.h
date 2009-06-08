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


/* Impresión de errores, para debuggeo */
#include <stdio.h>
#define PRINTERR(x)	fprintf(stderr, x)


/* Tipo que es solo para wrapping para el color.
 * Permito colores negativos para el coloreo greedy.
 */
typedef int Color;


/** Algunos macros de utilidad */

#define max(a, b) ((a>b) ? a : b)
#define min(a, b) ((a<b) ? a : b)


/* Indica si el modo de input es soportado por la API */
#define ModoinputInvalido(x)	((x != 1) && (x != 2))


/* Indica si el modo de verbosidad es soportado por la API */
#define   VerbosidadInvalidaAumentar(x)   ((x != 0) && (x != 1) && (x != 2) && (x != 3))
#define   VerbosidadInvalidaImprimir(x)   ((x != 0) && (x != 1) && (x != 2))
#define   VerbosidadInvalidaColorear(x)   ((x != 0) && (x != 1))


/* Inidica si un código numérico ASCII representa un caracter A-Z ó a-z */
#define IsAscii(x)	( ((x > 64) && (x < 91)) || ((x > 95) && (x < 123)) )

/* Indica si en nodo pertenece a dicho edge.
 * bool nIsFromEdge(u32 n , edge_t * e )
 */
#define nIsFromEdge(n,e) ((e->nodeOrig == n) != (e->nodeDest == n))


/* Indica si el vértice 'x' está en la cola de E-K corrida nº 'c'  */
#define   NotInQueue(x,c)   (x->corrida < c)


/* Imprime la cadena: "Lado (x,y): Flujo f"
 * donde 'f', 'x' e 'y' son valores u32. Si 'x' o 'y' son '0' o '1'
 * son cambiados por los caracteres 's' o 't' respectivamente */
#define   PrintFlowNum(x,y,f)   ((x != 0) && (x != 1) && (y != 0) && (y != 1)) ? \
				 printf ("Lado (%u,%u): Flujo %u\n", x, y, f)  \
					 : ( \
				((x == 0) && (y != 0) && (y != 1)) ? \
				printf ("Lado (s,%u): Flujo %u\n", y, f) \
					 : ( \
				((x != 0) && (x != 1) && (y == 1)) ? \
				printf ("Lado (%u,t): Flujo %u\n", x, f) \
					 : ( \
				((x == 1) && (y != 0) && (y != 1)) ? \
				printf ("Lado (t,%u): Flujo %u\n", y, f) \
					 : ( \
				((x != 0) && (x != 1) && (y == 0)) ? \
				printf ("Lado (%u,s): Flujo %u\n", x, f) \
					 : ( \
				printf ("Lado (s,t): Flujo %u\n", f) \
					) ) ) ) )



/* FUNCIONES PARA DETERMINAR SI UN NODO ES O NO BACKWARD/FORDWARD Y SETEARLOS
 * COMO FORD/BACK WARD
 *
 * Mini explicacion: Lo que hacemos es peligroso, porque? porque estamos trabajando
 * sobre indices en un arreglo, osea, un nodo se identifica por su indice en el
 * arreglo, estas funciones (sobretodo las de setear como backward) modifican
 * ese indice agrgandole bits = 1 en los bits de alto orden, por lo que un nodo
 * seteado como backward va a indicar que esta en la posicion >>>>>>> 7000 en el
 * arreglo (SUPER SIGSEV).
 * NOTE: Por eso siempre antes de usar cualquier nodo se debe setear a modo normal
 *	 SOLO EN LOS BACKWARDS (los fordwards no hace falta
 
#define IsBackward(x)	(x & 0xF0000000)
#define IsFordward(x)	!IsBackward(x)	 * kakaso pero no hay otra forma, asique \
					 * chequeen si es backward nada mas \
					 * es mas rapido :D \
					 *
					 
 * para setear un nodo como fordward 
#define SetBackward(x)	(x | 0xF0000000)
#define SetFordward(x)	(x & 0x0FFFFFFF)

 * adicional al pedo pero bueno, sirve para transformar a una direccion segura
 * ya que usamos solo 2¹³ (osea 13 bits, ahi nos podemos pasar pero no deberia
 * suceder NUNCA 
 
#define SetNormalIndexPos(x) (x & 0x0000FFFF)
*/

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
#define F_COLOUR_CYCLES		"-ccycles"		/* calculamos n veces el tiempo para coloreo*/
#define F_FLOW_TIME		"-ftime"		/* calc n veces flow y medir tiempo */
#define F_FLOW_CYCLES		"-fcycles"		/* calc n veces flow y medir ciclos */



#endif
