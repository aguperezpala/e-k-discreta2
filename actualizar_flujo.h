/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * Módulo actualizar_flujo. Es el mecanismo de "rastreo" del camino hallado
 * por una corrida de E-K (al finalizar una ejecución de AumentarFlujo)
 * Permite 4 modos de verbosidad
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */

#include "consts.h"
#include "network.h"

#ifndef ACTUALIZAR_FLUJO_H
#define ACTUALIZAR_FLUJO_H


/* Se limita a actualizar el estado del network sin imprimir nada por pantalla
 * 
 * PRE: estado != NULL && 0 <= q,s,t <= MAX_N_NODES
 */
void ActualizarSilencioso (EstadoNetwork *estado, u32 q, u32 s, u32 t, u32 flujo);


/* Además de actualizar el estado del network imprime el camino hallado que
 * está actualmente en la cola del network y el flujo que por él transita.
 * De no haber camino s--t no se imprime nada
 *
 * PRE: estado != NULL && 0 <= q,s,t <= MAX_N_NODES
 */
void ActualizarConCamino (EstadoNetwork *estado, u32 q, u32 s, u32 t, u32 flujo);


/* Actualiza el estado del network y, en caso de no existir camino s--t,
 * imprime el corte minimal actualmente en la cola y su capacidad
 * Si el camino s--t existe nada es impreso
 *
 * PRE: estado != NULL && 0 <= q,s,t <= MAX_N_NODES
 */
void ActualizarConCorte (EstadoNetwork *estado, u32 q, u32 s, u32 t, u32 flujo);


/* La combinación esperada entre ActualizarConCamino y ActualizarConCorte
 *
 * PRE: estado != NULL && 0 <= q,s,t <= MAX_N_NODES
 */
void ActualizarConCaminoYCorte (EstadoNetwork *estado, u32 q, u32 s, u32 t, u32 flujo);


#endif

