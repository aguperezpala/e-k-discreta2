#ifndef CONSTS_H
#define CONSTS_H

/* Funcion assert previa. NOTE: el ';' ya esta incluido en la definicion para
 * que no nos queden despues ; dando vueltas (por si las moscas
 */
#ifdef __DEBUG
	#include <assert.h>
	#define ASSERT(x)	assert(x);
#else
	#define ASSERT(x)	
#endif






#endif
