/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD edgeList (lista de aristas), versión 1.0.0, del proyecto único de
 * Discreta 2, FaMAF, año 2009
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */
#ifndef TRIPLETA_H
#define TRIPLETA_H

#include <stdlib.h>

#include "node.h"
#include "consts.h"


/*! TAD que representa la cola que usamos en E-K, tiene la estructura
	{nodeIndex	 ,	ParentIndex	,	actual Flow }
*/

typedef struct _tripleta tripleta_t;



/* Constructor e inicializador */
tripleta_t * tripleta_create (void);

/* inicializador
	REQUIRES:
		t != NULL
*/
void tripleta_inicialize (tripleta_t * t);


/* Destructor
	REQUIRES:
		t != NULL
NOTE: tener en cuenta si es allocado dinamicamente
*/
void tripleta_destroy (tripleta_t * t);




#endif
