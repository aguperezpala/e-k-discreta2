/* Librerías públicas */
#include <stdlib.h>
#include <stdio.h>
/* Librerías personales */
#include "edge.h"
#include "network.h"





/** ~~~~~~~~~~~~~~~~~~ FUNCIONES INTERNAS DE VERBOSIDAD ~~~~~~~~~~~~~~~~~~~~~ */
static void printAumentarFlujo (EstadoNetwork *estado, int verbosidad)
{
	u32 path_flow = 0;
	
	switch (verbosidad) {
	  case 0:
	  	break;
	  case 1:
		path_flow = printCaminoActual(estado)
	  case 2:

	  case 3:
	  
	}
}


/** ~~~~~~~~~~~~~~~~~~~~ FUNCIONES AUXILIARES INTERNAS ~~~~~~~~~~~~~~~~~~~~~~ */

/* Imprime el ultimo camino s<->t obtenido de EstadoNetwork, devolviendo
 * el incremento de flujo
 *
 * PRE: estado != NULL
 */
static u32 printCaminoActual(EstadoNetwork *estado)
{
	u32 € = 0;
	
	/*! TODO */
	
	return €;
}

/* Añade un lado al EstadoNetwork, actualizando todos los campos necesarios.
 * Esta versión no tiene en cuenta el coloreo.
 *
 * PRE: estado != NULL
 */
static void AñadirLado (EstadoNetwork *estado, u32 v1, u32 v2, u32 cap)
{
	u32  m;
	edge_t *edge;
	
	ASSERT (estado != NULL)
	
	m = max(v1, v2);
	if (m > estado->mayor) estado->mayor = m;
	
	/* Generamos las listas forward y/o backward si es necesario */
	
	if (estado->nodes[v1].forwardList == NULL) {
		
		estado->nodes[v1].forwardList = el_create ();
		
		if (estado->nodes[v1].backwardList == NULL)
			/* v1 es vértice nuevo */
			estado->nodes[v1].corrida = 0;
	}
	
	if (estado->nodes[v2].backwardList == NULL) {
		
		estado->nodes[v2].backwardList = el_create ();
		
		if (estado->nodes[v2].backwardList == NULL)
			/* v2 es vértice nuevo */
			estado->nodes[v2].corrida = 0;
	}
	
	/* creamos la arista */
	edge = edge_create (cap, v1, v2);
	
	/* Agregamos a ambas listas */
	el_add_edge (estado->nodes[v1].forwardList, edge);
	el_add_edge (estado->nodes[v2].backwardList, edge);
	
}



/* Añade un lado al EstadoNetwork, actualizando todos los campos necesarios.
 * Esta versión tiene en cuenta el coloreo incremental de los vértices.
 *
 * PRE: estado != NULL
 */
static void AñadirLadoColor (EstadoNetwork *estado, u32 v1, u32 v2, u32 cap)
{
	u32  m;
	edge_t *edge;
	bool v1new = false, v2new = false;
	
	ASSERT (estado != NULL)
	
	m = max(v1, v2);
	if (m > estado->mayor) estado->mayor = m;
	
	/* Generamos las listas forward y/o backward si es necesario */
	
	if (estado->nodes[v1].forwardList == NULL) {
		
		estado->nodes[v1].forwardList = el_create ();
		
		if (estado->nodes[v1].backwardList == NULL) {
			/* v1 es vértice nuevo */
			estado->nodes[v1].corrida = 0;
			/** Para coloreo */
			v1new = true;
			estado->nodes[v1].degree = 0;
		}
	}
	
	if (estado->nodes[v2].backwardList == NULL) {
		
		estado->nodes[v2].backwardList = el_create ();
		
		if (estado->nodes[v1].forwardList == NULL) {
			/* v2 es vértice nuevo */
			estado->nodes[v2].corrida = 0;
			/** Para coloreo */
			v2new = true;
			estado->nodes[v2].degree = 0;
		}
	}
	
	/* creamos la arista */
	edge = edge_create (cap, v1, v2);
	
	/* Agregamos a ambas listas */
	el_add_edge (estado->nodes[v1].forwardList, edge);
	estado->nodes[v1].degree++;
	el_add_edge (estado->nodes[v2].backwardList, edge);
	estado->nodes[v2].degree++;
	
	/** De acá para abajo, para coloreo */
	/* Seteamos el delta de todo el network/grafo */
	m = max (estado->nodes[v1].degree, estado->nodes[v2].degree);
	if (estado->delta < m) estado->delta = m;
	
	
	if (v1new) {
		if (v2new) {
			/* Ambos vértices eran nuevos */
			estado->nodes[v1].color = 1;
			estado->nodes[v2].color = 2;
		} else
			/* v1 es nuevo, lo coloreamos sin conflicto */
			estado->nodes[v1].color = 3 - estado->nodes[v2].color;
	} else if (v2new)
		/* v2 es nuevo, lo coloreamos sin conflicto */
		estado->nodes[v2].color = 3 - estado->nodes[v1].color;
	else
		/* Ningún vértice es nuevo => lado conflictivo */
		el_add_edge (estado->l_con, edge);
}




/** ~~~~~~~~~~~~~~~~~~~~~ FUNCIONES DE LA API (EXTERNAS) ~~~~~~~~~~~~~~~~~~~~ */


/* Construye un objeto EstadoNetwork.
 * ret = network_create();
 * POS : {(ret != NULL => ret es un objeto EstadoNetwork vacío) && 
 *		(ret == NULL => no hay memoria para el objeto EstadoNetwork)}
 */
EstadoNetwork *network_create (void)
{
	EstadoNetwork *ret = NULL;

	ret = (EstadoNetwork*) malloc (sizeof (struct s_estado_network));
	
	if(ret != NULL){
		ret->cola = qt_create ();
		ret->flow_value = 0;
		ret->maximal  = false;
		ret->completo = false;
		ret->mayor  = 0;
		ret->delta  = 0;
		ret->colors = 0;
		ret->l_con  = el_create ();
	}
	
	return ret;
}


/* PRE : {estado != NULL && (modmoinput==1 || modoinput==2)}
 * ret = Inicializar(estado,modoinput);
 * POS : {(ret == 1 => estado tiene capacidad, según modoinput para almacenar 
 *		nodos) && (ret == 0 => no hay memoria para alojar los nodos)}
 */
int Inicializar (EstadoNetwork *estado, int modoinput)
{
	int ret = 0, i, n;
	
	/* Precondiciones */
	ASSERT(estado != NULL)
	if ( ModoinputInvalido (modoinput) ) {
		fprintf (stderr, "Network: Inicializar: modoinput inválido\n");
		return 1;
	}

	/* {modoinput == 1 || modoinput == 2} */
	if (modoinput == 1) {
		/* Se espera input alfabético */
		estado->modoinput = 1;
		n = 123;  /* Esto cubre desde ASCII 32  para ' ' (el 1º)
	 		   * hasta ASCII 122 para 'z' (el último) */
	} else {
		/* Se espera input numérico, y la pu~@#@ç$! */
		estado->modoinput = 2;
		n = MAX_N_NODES;
	}
	
	/* Inicializamos los lados */
	for (i = 0 ; i < n ; i++) {
		estado->nodes[i].forwardList = NULL;
		estado->nodes[i].backwardList = NULL;
	}
	
	return ret;
}


/* PRE : {estado != NULL && (modmoinput==1 || modoinput==2)} 
   ret = LeerUnLado(estado,modoinput);
   POS : {(ret == 1 => estado contiene ahora el lado ingresado) && 
	   	  (ret == 0 => error al leer los datos ingresados)}
*/
int LeerUnLado(EstadoNetwork *estado, int modoinput)
{
	u32 v1, v2, cap;
	char *scan = NULL;
	
	ASSERT (estado != NULL)
			
	if ( ModoinputInvalido (modoinput) ) {
		fprintf (stderr, "Network: LeerUnLado: modoinput inválido\n");
		estado->completo = true;
		return 0;
		
	} else if (modoinput != estado->modoinput) {
		fprintf (stderr, "Network: LeerUnLado: modoinput inválido\n"
				"Ingresó %d y antes había escogido %d\nSe ruega"
				" coherencia\n", modoinput, estado->modoinput);
		estado->completo = true;
		return 0;
	}
	
	/* {modoinput == 1 || modoinput == 2} */
	if (modoinput == 1) {
		/** Input alfabético */
		char edge[15];
		
		/* Guardamos en "edge" lo leído */
		scanf ("%[^\n]", &edge);
		getchar ();
		
		if (edge[2] != ' ') {
			/* No había espacio tras los dos vértices */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}
		
		
		if (strlen (edge+3) > 10) {
			/* Capacidad mayor que u32 */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}
		
		/* Guardamos la capacidad en cap */
		cap = (u32) strtol (edge+3, &scan, 10);
		
		if (*scan != '\0') {
			/* La capacidad no era un entero */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}
		
		/* Obtenemos el ASCII del nombre de los vértices */
		v1 = (u32) edge[0];
		v2 = (u32) edge[1];
		
		if (!IsAscii (v1) || !IsAscii (v2)){
			/* Los vértices no eran letras */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		} else {
			if (estado->coloreo)
				AñadirLadoColor (estado, v1, v2, cap);
			else
				AñadirLado (estado, v1, v2, cap);
		}
		
		if (estado->maximal) estado->maximal = false;
		
	} else {
		/** Input numérico */
		char edge[30];
		char *ptr1 = NULL, *ptr2 = NULL;
		
		getchar();
		scanf ("%[^\n]", (char *) &edge);
		
		ptr1 = (char *) edge;
		
		/* Extraemos el 1º vértice */
		
		ptr2 = ptr1; /* Recordamos el comienzo de la cadena */
		ptr1 = strchr (ptr2, ' ');
		if (ptr1 == NULL) {
			/* No había espacios en la cadena */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}
		
		ptr1[0] = '\0'; /* Aislamos el 1º vértice */
		ptr1++;
		if (strlen (ptr2) > 10) {
			/* Nombre de vértice mayor que u32 */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}	 
		v1 = (unsigned int) strtol (ptr2, &scan, 10);
		if (*scan != '\0') {
			/* El vértice 1 no era un entero */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}
		
		/* Extraemos el 2º vértice */
		
		ptr2 = ptr1;
		ptr1 = strchr (ptr2, ' ');
		if (ptr1 == NULL) {
			/* No había espacios tras el 1º vértice */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}
		
		ptr1[0] = '\0'; /* Aislamos el 2º vértice */
		ptr1++;
		if (strlen (ptr2) > 10) {
			/* Nombre de vértice mayor que u32 */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}
		
		v2 = (unsigned int) strtol (ptr2, &scan, 10);
		if (*scan != '\0') {
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}
		
		/* Extraemos la capacidad */
		
		ptr2 = ptr1;
		if (strlen (ptr2) > 10) {
			/* Capacidad mayor que u32 */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}
			
		cap = (unsigned int) strtol (ptr2, &scan, 10);
		if (*scan != '\0') {
			/* Capacidad no era un entero */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			estado->completo = true;
			return 0;
		}
		
		if (estado->coloreo)
			AñadirLadoColor (estado, v1, v2, cap);
		else
			AñadirLado (estado, v1, v2, cap);
		
		if (estado->maximal) estado->maximal = false;
	}
	
	return 1;
}


/* PRE: {estado != NULL && verbosidad € {0, 1, 2, 3} }
 * ret = AumentarFlujo (estado, verbosidad)
 * POS: {(ret == 0 => Se pudo aumentar el flujo)	&&
 *	 (ret == 1 => No se pudo aumentar el flujo)	&&
 *	 (ret == 2 => Se produjo un error)			 }
 */
int AumentarFlujo (EstadoNetwork *estado, int verbosidad)
{
	int result = 0;
	u32 s, t, q , p , e;
	unsigned short corrida;
	node_t *actual, *vecino;
	edge_t *edge;
	bool empty = false;
	int endList = 0;
	
	/* Precondiciones */
	ASSERT (estado != NULL)

	if ( VerbosidadInvalidaAumentar (verbosidad) ) {
		/* Verbosidad no valida */
		fprintf (stderr, "Network: AumentarFlujo: verbosidad inválida\n");
		return 2;
	}

	if(estado->maximal){
		/* No se puede aumentar el flujo */
		fprintf (stderr, "Network: AumentarFlujo: No se pudo aumentar flujo\n");
		return 1;
	}
		
	if (estado->modoinput == 1) {
		/** Modo alfabético */
		s = 115; /* 115 == ASCII('s') */
		t = 116;
	} else {
		/** Modo numérico */
		s = 0;
		t = 1;
	}
	
	/* Borramos la cola vieja */
	qt_initialize (estado->cola, s);
	/* Nos paramos en 's' */
	qt_start (estado->cola);
	/* Aumentamos y registramos la versión de corrida E-K */
	corrida = estado->nodes[s].corrida++;
	
	q = qt_get_actual_node (estado->cola);
	
	while (!empty && q != t) { /* Ciclo principal */
		
		actual = &estado->nodes[q];
		ASSERT (actual->degree > 0)

		/* forwards: Ciclo "lados forward" */
		if (actual->forwardList == NULL ) goto backwards;
		el_start (actual->forwardList);
		endList = 0;
		while (endList == 0) { 
			edge = el_get_actual (actual->forwardList);
			vecino = &estado->nodes[edge->nodeDest];
			
			if (NotInQueue(vecino,corrida) &&
				(edge->flow < edge->capacity)){
				/* Encolo el vertice */
				e = qt_get_actual_flow (estado->cola);
				if((edge->capacity - edge->flow) < e)
					e = (edge->capacity - edge->flow);
				qt_add_quad (estado->cola, e, edge->nodeDest, edge, false);
				
				if (edge->nodeDest == t) {
					/* Obtuvimos t , terminamos el ciclo */
					q = t;
					goto endwhile;
				}
			}
			
			endList = el_avance (actual->forwardList);
		}
		
		backwards: /* Ciclo "lados backward" */
		if (actual->forwardList == NULL ) goto nextNode;
		el_start (actual->backwardList);
		endList = 0;
		while (endList == 0) { 
			edge = el_get_actual (actual->backwardList);
			vecino = &estado->nodes[edge->nodeOrig];
			
			if (NotInQueue(vecino,corrida) &&
				(edge->flow > 0)){
				/* Encolo el vertice */
				e = qt_get_actual_flow (estado->cola);
				if(edge->flow < e)
					e = edge->flow;
				qt_add_quad (estado->cola, e, edge->nodeOrig , edge, true);
			}
			
			endList = el_avance (actual->backwardList);
		}

		nextNode:/* Nos movemos al siguiente nodo */
			empty = (qt_avance(estado->cola) != 1);
			q = qt_get_actual_node (estado->cola);
		
		endwhile:/* Esta es la salida en caso de que lleguemos a t */
	}

	/* Actualizamos el estado según la verbosidad escogida
	 * Ver la librería actualizar_flujo.h */
	switch (verbosidad) {
		
		case 0:
			ActualizarSilencioso (estado, q, s, t, e);
			break;
			
		case 1:
			ActualizarConCamino (estado, q, s, t, e);
			break;
			
		case 2:
			ActualizarConCorte (estado, q, s, t, e);
			break;
			
		case 3:
			ActualizarConCaminoYCorte (estado, q, s, t, e);
			break;
		default:
			fprintf (stderr, "Network: AumentarFlujo: falló la "
					"detección de verbosidad errónea\n");
			return 2;
			break;
	}
	
	return result;
}


/*! TODO <COMPLETAR COMPLETAR> */
u32 ImprimirFlujo (EstadoNetwork *estado, int verbosidad)
{

}

/*! TODO <COMPLETAR COMPLETAR> */
u32 ColorearNetwork (EstadoNetwork *estado, int verbosidad)
{

}

