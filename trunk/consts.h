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
#define ModoinputValido(x)	((x == 1) || (x == 2))


/*! Indica si el modo de verbosidad es soportado por la API.
 * NOTE: Esto no es util ya que las 3 operaciones de verbosidad
 * no aceptan estos cuatro valores.
 */
#define VerbosidadValida(x)	((x == 0) || (x == 1) || (x == 2) || (x == 3))


/* Inidica si un código numérico ASCII representa un caracter A-Z ó a-z */
#define IsAscii(x)	( ((x > 64) && (x < 91)) || ((x > 97) && (x < 123)) )


/* Indica si el vértice 'x' está en la cola de E-K corrida nº 'c'  */
#define   NotInQueue(x,c)   (x->corrida < c)


/* Indica si el vértice 'x' (de tipo u32) tiene la etiqueta "backward"
 * ie: si fue agregado hacia atrás en AumentarFlujo
#define   IsBackward(x)   (x & 0x80000000)
*/
/* Declara "backward" al vértice 'x'
 * NOTE Antes de volver a usar el vértice 'x' debe quitarse esta etiqueta
#define   SetBackward(x)   (x |= 0x80000000)
*/
/* Quita la etiqueta "backward" del vértice 'x'
#define   UnsetBackward(x)   (x &= 0x7FFFFFFF)
*/


#ifndef INLINE
# if __GNUC__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif


#endif
