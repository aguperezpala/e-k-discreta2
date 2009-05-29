/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD tripleta versión 1.0.0, del proyecto único de Discreta 2, FaMAF, año 2009
 * Una tripleta es un elemento de la cola que genera Edmods-Karp a cada paso
 *   de extensión del grafo. Es decir, un elemento tripleta está compuesto por
 *   tres elementos: 1. Nombre del vértice
 *		     2. Nombre del padre que puso este vértice
 *		     3. Flujo que puede mandarse por el lado
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
