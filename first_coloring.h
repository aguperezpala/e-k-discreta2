/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * Módulo de resolución de aristas conflictivas de un network.
 * Dada una instancia de EstadoNetwork obtiene un coloreo propio para la misma
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */
 
#include "network.h"


#ifndef C_INICIAL_H
#define C_INICIAL_H


/* Estudia la lista de aristas conflictivas de (estado) para ir resolviendo
 * los conflictos de color uno por uno
 *
 * PRE: estado != NULL
 *
 *	K = ResolverConflictos (estado)
 *
 * POS: "estado posee coloreo propio" && "el coloreo emplea K colores"
 */
short ResolverConflictos (EstadoNetwork *estado);


#endif
