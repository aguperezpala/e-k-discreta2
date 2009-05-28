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


/* Funcion assert previa. NOTE: el ';' ya esta incluido en la definicion para
 * que no nos queden despues ; dando vueltas (por si las moscas
 */
#ifdef __DEBUG
	#include <assert.h>
	#define ASSERT(x)	assert(x);
#else
	#define ASSERT(x)	
#endif

/* Tipo que es solo para wrapping para el color ( si no sirve lo sacamos ) */
typedef unsigned short Color;

/*! VERBOSIDADES */
#define VAL_F		1	/* Valor del flujo */
#define CAP_C		2	/* Corte y capacidad del mismo */
#define VAL_F_FLUX	4	/* Valor del flujo + flujo */
#define FLUX		8	/* Flujo (lados que lo hacen) */


#ifndef INLINE
# if __GNUC__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif


#endif
