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


#ifndef INLINE
# if __GNUC__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif


#endif
