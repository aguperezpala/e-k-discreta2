#ifndef CONSTS_H
#define CONSTS_H


#define u32 unsigned int


/* Funcion assert previa. NOTE: el ';' ya esta incluido en la definicion para
 * que no nos queden despues ; dando vueltas (por si las moscas
 */
#ifdef __DEBUG
	#include <assert.h>
	#define ASSERT(x)	assert(x);
#else
	#define ASSERT(x)	
#endif


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
