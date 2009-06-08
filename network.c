/* Librerías públicas */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* Librerías personales */
#include "edge.h"
#include "network.h"
#include "greedy.h"
#include "first_coloring.h"
#include "print_stack.h"





/**  ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ###  */
/** ~~~~~~~~~~~~~~~~~~ FUNCIONES STATIC (DE USO INTERNO) ~~~~~~~~~~~~~~~~~~~~ */

/* Permite destruir toda la lista de aristas de un determinado nodo.
 *
 */
static void network_edgelist_destroy (u32 node_i , node_t * nodes);
/* Inicializa el flujo de todas las aristas forward de un determinado nodo.
 *
 */
static void network_init_forward_edges (u32 node_i , node_t * nodes);
	
/* Añade un lado al EstadoNetwork, actualizando todos los campos necesarios.
 * Esta versión no tiene en cuenta el coloreo.
 *
 * PRE: estado != NULL
 */
static void AniadirLado (EstadoNetwork *estado, u32 v1, u32 v2, u32 cap)
{
	edge_t *edge = NULL;
	
	ASSERT (estado != NULL)
	
	/* Generamos las listas forward y/o backward si es necesario */
	
	if (estado->nodes[v1].forwardList == NULL) {
		
		estado->nodes[v1].forwardList = el_create ();
		
		if (estado->nodes[v1].backwardList == NULL) {
			/* v1 es vértice nuevo */
			estado->nodes[v1].corrida = 0;
			ns_add_node (estado->nstack, v1);
			estado->nodes[v1].degree = 0;
		}
	}
	
	if (estado->nodes[v2].backwardList == NULL) {
		
		estado->nodes[v2].backwardList = el_create ();
		
		if (estado->nodes[v2].forwardList == NULL) {
			/* v2 es vértice nuevo */
			estado->nodes[v2].corrida = 0;
			ns_add_node (estado->nstack, v2);
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
	
}

/* Añade un lado al EstadoNetwork, actualizando todos los campos necesarios.
 * Esta versión tiene en cuenta el coloreo incremental de los vértices.
 *
 * PRE: estado != NULL
 */
static void AniadirLadoColor (EstadoNetwork *estado, u32 v1, u32 v2, u32 cap)
{
	u32 m = 0;
	Color max_color = 0;
	
	ASSERT (estado != NULL)
	
	/* LLamamos a AniadirLado */
	AniadirLado(estado, v1, v2, cap);
	ASSERT( estado->nodes[v1].degree > 0 && estado->nodes[v2].degree > 0)
			
	/* Seteamos el delta de todo el network/grafo */
	m = max (estado->nodes[v1].degree, estado->nodes[v2].degree);
	if ((unsigned)estado->delta < m) estado->delta = m;
	
	/* Mediante los grados vemos cuales son los vertices nuevos */
	if (estado->nodes[v1].degree == 1) {
		
		if (estado->nodes[v2].degree == 1) {
			/* Ambos vértices eran nuevos */
			estado->nodes[v1].color = 1;
			estado->nodes[v2].color = 2;
		} else{
			/* v1 es nuevo, lo coloreamos sin conflicto */
			estado->nodes[v1].color = 3 - estado->nodes[v2].color;
		}
	} else if (estado->nodes[v2].degree == 1){
		/* v2 es nuevo, lo coloreamos sin conflicto */
		estado->nodes[v2].color = 3 - estado->nodes[v1].color;
	}else{
		/* Ningún vértice es nuevo => lado conflictivo */
		el_add_edge (estado->l_con, el_get_actual(estado->nodes[v1].forwardList));
	}

	/* Actualizamos el color */
	max_color = max(estado->nodes[v1].color , estado->nodes[v2].color);
	estado->colores = max (estado->colores , max_color);
}


/* Imprime por pantalla todos los lados froward (y sus flujos actuales)
 * del elemendo de "nodes" que está en la posición "node_i"
 * Considera a los vértices como caracteres alfabéticos (ascii)
 *
 * PRE: nodes != NULL
 */
static void ImpresionFlujosAlf (u32 node_i, node_t *nodes)
{
	edgeList_t *fl = NULL; /* Lista de lados forward de modes[node] */
	edge_t *edge = NULL;
	int endList = 0;
	
	/* La idea es imprimir todos los lados forward y con eso cubrir 
	* el network completo. */
	
	ASSERT (nodes != NULL)
			
	if (nodes[node_i].forwardList == NULL)
		return;
// 	ASSERT (nodes[node_i].forwardList != NULL)
// 	se quitó esta precondición para soportar la impresión "en bloques"
	
	fl = nodes[node_i].forwardList;
	el_start (fl);
	
	
	while (endList == 0) {
		edge = el_get_actual (fl);
		printf ("Lado (%c,%c): Flujo %u\n",edge->nodeOrig, edge->nodeDest, edge->flow);
		endList = el_avance (fl);
	}
}


/* Imprime por pantalla todos los lados froward (y sus flujos actuales)
 * del elemendo de "nodes" que está en la posición "node_i"
 * Considera a los vértices como números (u32)
 *
 * PRE: nodes != NULL
 */ 
static void ImpresionFlujosNum (u32 node_i, node_t *nodes)
{
	edgeList_t *fl = NULL; /* Lista de lados forward de modes[node] */
	edge_t *edge = NULL;
	int endList = 0;
	u32 x = 0, y = 0, f = 0;
	
	/* La idea es imprimir todos los lados forward y con eso cubrir 
	 * el network completo. */
	
	ASSERT (nodes != NULL)
	
	if (nodes[node_i].forwardList == NULL)
		return;
// 	ASSERT (nodes[node_i].forwardList != NULL)
// 	se quitó esta precondición para soportar la impresión "en bloques"
	
	fl = nodes[node_i].forwardList;
	el_start (fl);
	
	while (endList == 0) {
		edge = el_get_actual (fl);
		x = edge->nodeOrig;
		y = edge->nodeDest;
		f = edge->flow;
		
		PrintFlowNum (x, y, f);
		/* Por PrintFlowNum ver consts.h */	
		
		endList = el_avance (fl);
	}
}


/* Imprime por pantalla el vértice de "nodes" que está en la
 * posición "node_i" en formato alfabético junto con su color
 *
 * PRE: nodes != NULL  &&  nodes[node].color != 0
 */
static void ImpresionColoresAlf (u32 node_i, node_t *nodes)
{
	ASSERT (nodes != NULL)
	printf ("Vertice %c: Color %d\n", node_i, nodes[node_i].color);
}


/* Imprime por pantalla el vértice de "nodes" que está en la
 * posición "node_i" en formato numérico junto con su color
 *
 * PRE: nodes != NULL  &&  nodes[node_i].color != 0
 */
static void ImpresionColoresNum (u32 node_i, node_t *nodes)
{
	ASSERT (nodes != NULL)
	
	if (node_i != 0 && node_i != 1)
		printf ("Vertice %u: Color %d\n", node_i, nodes[node_i].color);
	else if (node_i == 0)
		printf ("Vertice s: Color %d\n",  nodes[node_i].color);
	else
		printf ("Vertice t: Color %d\n",  nodes[node_i].color);
}


/**  ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ###  */
/** ~~~~~~~~~~~~~~~~~~~~~ FUNCIONES DE LA API (EXTERNAS) ~~~~~~~~~~~~~~~~~~~~ */

/* Construye un objeto EstadoNetwork.
 * ret = network_create();
 * POS : {(ret != NULL => ret es un objeto EstadoNetwork vacío) && 
 *		(ret == NULL => no hay memoria para el objeto EstadoNetwork)}
 */
EstadoNetwork *network_create (bool coloreo)
{
	EstadoNetwork *ret = NULL;
	register int i;

	ret = (EstadoNetwork*) malloc (sizeof (struct s_estado_network));
	
	if(ret != NULL){
		ret->cola = qt_create ();
		ret->flow_value = 0;
		ret->maximal  = false;
		ret->completo = false;
		/*ret->mayor  = 0;*/
		ret->delta  = 0;
		ret->colores = 0;
		ret->coloreo = coloreo;
		ret->l_con  = el_create ();
		ret->nstack = ns_create ();
		
		/* esto es obligatorio aca lamentablemente :D */
		for (i = MAX_N_NODES - 1; i <= 0; i--) {
			ret->nodes[i].forwardList = NULL;
			ret->nodes[i].backwardList = NULL;
		}
	}
	
	
	return ret;
}


static void network_init_forward_edges (u32 node_i , node_t * nodes)
{
	edgeList_t * fordward = NULL;
	edge_t * e = NULL;

	fordward = nodes[node_i].forwardList;

	if (el_get_size(fordward) > 0){
		el_start (fordward);
		do{
			e = el_get_actual (fordward);
			e->flow =0;
			nodes[e->nodeOrig].corrida = 0;
			nodes[e->nodeDest].corrida = 0;
			nodes[e->nodeOrig].color = 0;
			nodes[e->nodeDest].color = 0;
		}while(el_avance(fordward) == 0);
	}
	
}

/* PRE : {estado != NULL && (modmoinput==1 || modoinput==2)}
 * ret = Inicializar(estado,modoinput);
 * POS : {(ret == 1 => estado tiene capacidad, según modoinput para almacenar 
 *		nodos) && (ret == 0 => no hay memoria para alojar los nodos)}
 */
int Inicializar (EstadoNetwork *estado, int modoinput)
{
	/* Precondiciones */
	ASSERT(estado != NULL)
	if ( ModoinputInvalido(modoinput) ) {
		PRINTERR("API: Inicializar: modoinput inválido\n");
		return 1;
	}

	/* Inicializo los nodos y sus aristas */
	ns_cmd (estado->nstack , estado->nodes , network_init_forward_edges);
	
	estado->modoinput = modoinput;
	estado->colores = 0;
	estado->flow_value = 0;
	el_clean(estado->l_con);
	estado->maximal = false;

	return 0;
}

/* PRE : {estado != NULL && (modmoinput==1 || modoinput==2)} 
   ret = LeerUnLado(estado,modoinput);
   POS : {(ret == 1 => estado contiene ahora el lado ingresado) && 
	   	  (ret == 0 => error al leer los datos ingresados)}
*/
int LeerUnLado(EstadoNetwork *estado, int modoinput)
{
	u32 v1 = 0, v2 = 0, cap = 0;
	char *scan = NULL;
	
	ASSERT (estado != NULL)
			
	if ( ModoinputInvalido (modoinput) ) {
		PRINTERR ("API: LeerUnLado: modoinput inválido\n");
		estado->completo = true;
		return 0;
	}
	
#ifdef __DEBUG	
	if (modoinput != estado->modoinput) {
		fprintf (stderr,"API: LeerUnLado: modoinput inválido\n"
				"Ingresó %d y antes había escogido %d\nSe ruega"
				" coherencia\n", modoinput, estado->modoinput);
		estado->completo = true;
		return 0;
	}
#endif
	
	/* {modoinput == 1 || modoinput == 2} */
	if (modoinput == 1) {
		/** Input alfabético */
		char edge[15];
		
		/* Guardamos en "edge" lo leído */
		memset (edge, '\0', 15);
		scanf ("%[^\n]", edge);
		getchar ();
		
		if (edge[2] != ' ') {
			/* No había espacio tras los dos vértices */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}
		if (strlen (edge+3)  > 10) {
			/* Capacidad mayor que u32 */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}
		
		/* Guardamos la capacidad en cap */
		cap = (u32) strtol (edge+3, &scan, 10);
		
		if (*scan != '\0') {
			/* La capacidad no era un entero */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}
		
		/* Obtenemos el ASCII del nombre de los vértices */
		v1 = (u32) edge[0];
		v2 = (u32) edge[1];
		
		if (!IsAscii (v1) || !IsAscii (v2)){
			/* Los vértices no eran letras */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		} 
		
	} else {
		/** Input numérico */
		char edge[30];
		char *ptr1 = NULL, *ptr2 = NULL;
		
		memset (edge, '\0', 30);
		getchar();
		scanf ("%[^\n]", (char *) &edge);
		
		ptr1 = (char *) edge;
		
		/* Extraemos el 1º vértice */
		
		ptr2 = ptr1; /* Recordamos el comienzo de la cadena */
		ptr1 = strchr (ptr2, ' ');
		if (ptr1 == NULL) {
			/* No había espacios en la cadena */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}
		
		ptr1[0] = '\0'; /* Aislamos el 1º vértice */
		ptr1++;
		if (strlen (ptr2) > 10) {
			/* Nombre de vértice mayor que u32 */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}	 
		v1 = (unsigned int) strtol (ptr2, &scan, 10);
		if (*scan != '\0') {
			/* El vértice 1 no era un entero */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}
		
		/* Extraemos el 2º vértice */
		
		ptr2 = ptr1;
		ptr1 = strchr (ptr2, ' ');
		if (ptr1 == NULL) {
			/* No había espacios tras el 1º vértice */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}
		
		ptr1[0] = '\0'; /* Aislamos el 2º vértice */
		ptr1++;
		if (strlen (ptr2) > 10) {
			/* Nombre de vértice mayor que u32 */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}
		
		v2 = (unsigned int) strtol (ptr2, &scan, 10);
		if (*scan != '\0') {
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}
		
		/* Extraemos la capacidad */
		
		ptr2 = ptr1;
		if (strlen (ptr2) > 10) {
			/* Capacidad mayor que u32 */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}
			
		cap = (unsigned int) strtol (ptr2, &scan, 10);
		if (*scan != '\0') {
			/* Capacidad no era un entero */
			PRINTERR ("Finalizó la lectura de lados\n\n");
			estado->completo = true;
			return 0;
		}
		
	}

	estado->maximal = false;

	if (estado->coloreo)
		AniadirLadoColor (estado, v1, v2, cap);
	else
		AniadirLado (estado, v1, v2, cap);
	
	return 1;
}

/* PRE: {estado != NULL && verbosidad € {0, 1, 2, 3} }
 * ret = AumentarFlujo (estado, verbosidad)
 * POS: {(ret == 0 => Se pudo aumentar el flujo)	&&
 *	 (ret == 1 => No se pudo aumentar el flujo)		&&
 *	 (ret == 2 => Se produjo un error)			 }
 */
int AumentarFlujo (EstadoNetwork *estado, int verbosidad)
{
	int result = 0;
	u32 s, t, q, flujo = 0;
	unsigned short corrida;
	node_t *actual, *vecino;
	edge_t *edge;
	bool empty = false;
	int endList = 0;
	print_s * ps;
	
	/* Precondiciones */
	ASSERT (estado != NULL)
	
	if ( VerbosidadInvalidaAumentar (verbosidad) ) {
		/* Verbosidad no valida */
		PRINTERR ("API: AumentarFlujo: verbosidad inválida\n");
		return 2;
	}
	
	if(estado->maximal){
		/*No se puede aumentar el flujo
		PRINTERR ("API: AumentarFlujo: No se pudo aumentar flujo\n");*/
		
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
	
	/* Borramos la cola vieja, inicializamos con el maximo flow posible */
	qt_initialize (estado->cola, s, 0xFFFFFFFF);
	/* Nos paramos en 's' */
	qt_start (estado->cola);
	/* Aumentamos y registramos la versión de corrida E-K */
	
	estado->nodes[s].corrida++;
	corrida = estado->nodes[s].corrida;
	
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
				flujo = qt_get_actual_flow (estado->cola);
				if((edge->capacity - edge->flow) < flujo)
					flujo = (edge->capacity - edge->flow);
				vecino->corrida = corrida;
				qt_add_quad (estado->cola, flujo, edge->nodeDest, edge);
				
				if (edge->nodeDest == t) {
					/* Obtuvimos t , terminamos el ciclo */
					q = t;
					goto endwhile;
				}
			}
			
			endList = el_avance (actual->forwardList);
		}
		
		backwards: /* Ciclo "lados backward" */
		if (actual->backwardList == NULL ) goto nextNode;
		el_start (actual->backwardList);
		endList = 0;
		while (endList == 0) { 
			edge = el_get_actual (actual->backwardList);
			vecino = &estado->nodes[edge->nodeOrig];
			
			if (NotInQueue(vecino,corrida) &&
				(edge->flow > 0)){
				/* Encolo el vertice */
				flujo = qt_get_actual_flow (estado->cola);
				if(edge->flow < flujo)
					flujo = edge->flow;
				vecino->corrida = corrida;
				qt_add_quad (estado->cola, flujo, edge->nodeOrig , edge);
			}
			
			endList = el_avance (actual->backwardList);
		}

		nextNode:/* Nos movemos al siguiente nodo */
			empty = (qt_avance(estado->cola) == 1);
			q = qt_get_actual_node (estado->cola);
		
	}
	endwhile:/* Esta es la salida en caso de que lleguemos a t */
	
	
	
	if (q == t) {
		/* Llegamos a 't' => hay que actualizar flujo */
		/* nos movemos al final de la cola */
		qt_move_last (estado->cola);
		if (verbosidad == 1 || verbosidad == 3)
			/* Debemos imprimir el camino */
			ps = ps_create();
		
		/* Actualizamos el flujo total */
		estado->flow_value += flujo;
		
		/* Actualizamos el flujo del network */
		while (q != s){
			edge = qt_get_actual_edge (estado->cola);
	
			ASSERT (nIsFromEdge(q, edge))
			ASSERT (!NotInQueue((&(estado->nodes[q])), corrida))
			
			if (edge->nodeDest == q) { /* Es lado forward */
				edge->flow += flujo;
				if (verbosidad == 1 || verbosidad == 3)
					ps = ps_add_node (ps, q, ',');
						
			} else {		  /* Es lado backward */
				edge->flow -= flujo;
				if (verbosidad == 1 || verbosidad == 3)
					ps = ps_add_node (ps, q, '<');
			}
			
			qt_go_parent (estado->cola);
			q = qt_get_actual_node (estado->cola);
		}
		
		if (verbosidad == 1 || verbosidad == 3) {
			/* Nos faltó agregar 's' */
			ps = ps_add_node (ps, q, ',');
		
			/* Imprimimos el camino hallado */
			ps_print (ps, estado->modoinput, flujo);
			ps_destroy (ps);
		}
		
	} else {
		estado->maximal = true;
		result = 1;
		
		if (verbosidad == 2 || verbosidad == 3) {
			/* Hay que imprimir el corte */
			u32 cap = 0, vecino;
			edgeList_t *vecinos;
			bool endList = false;
			register unsigned short i;
			short nn = qt_get_size (estado->cola);
			/* nn == nº de vértices del corte */
			
			printf ("Corte Minimal: S={");
			qt_start (estado->cola);
			
			/* Tiene que ser 's', sino está como el chori */
			q = qt_get_actual_node (estado->cola);
			ASSERT (q == s)
			
			/* Actualizamos la capacidad del corte */
			vecinos = estado->nodes[q].forwardList;
			el_start (vecinos);
			while (!endList) {
				vecino = el_get_actual(vecinos)->nodeDest;
				
				if (estado->nodes[vecino].corrida != corrida)
				/* Este vecino no apareció en la última corrida */
					cap += el_get_actual(vecinos)->capacity;
				
				endList = el_avance (vecinos);
			}
			
			/* Vamos a revisar los otros vértices del corte */
			qt_avance (estado->cola);
			q = qt_get_actual_node (estado->cola);
			if (q == s) {
			/* El corte sólo tenía a 's' */
				printf ("s}\n");
				goto capacidad;
			} else
				printf ("s, ");
			
			/* Vamos imprimiendo todos los vértices del corte */
			for (i = 0 ; i < nn-2 ; i++) {
				q = qt_get_actual_node (estado->cola);
				
				ASSERT (q != t)
				
				if (estado->modoinput == 1) /* Alfabético */
					printf ("%c, ",q);
				else {
					printf ("%u, ",q);
				}
				
				/* Actualizamos la capacidad del corte */
				vecinos = estado->nodes[q].forwardList;
				if (vecinos == NULL) {
					qt_avance (estado->cola);
					continue;
				}
				el_start (vecinos);
				endList = 0;
				while (!endList) {
					vecino = el_get_actual(vecinos)->nodeDest;
					
					if (NotInQueue((&estado->nodes[vecino]), corrida))
					/* No estaba en la cola => no está en el corte */
						cap += el_get_actual(vecinos)->capacity;
				
					endList = el_avance (vecinos);
				}
				
				qt_avance (estado->cola);
			}
			/* Nos faltó el último */
			q = qt_get_actual_node (estado->cola);
			
			ASSERT (q != t)
			
			if (estado->modoinput == 1)
				printf ("%c}\n", q);
			else {
				if (q == s)
					printf ("s}\n");
				else
					printf ("%u}\n",q);
			}
			
			/* Actualizamos la capacidad del corte por última vez */
			vecinos = estado->nodes[q].forwardList;
			if (vecinos == NULL) goto capacidad;
			el_start (vecinos);
			endList = 0;
			while (!endList) {
				vecino = el_get_actual(vecinos)->nodeDest;
				
				if (estado->nodes[vecino].corrida != corrida)
					cap += el_get_actual(vecinos)->capacity;
				
				endList = el_avance (vecinos);
			}
			capacidad:
			printf ("Capacidad del corte: %u\n\n", cap);
		}
	}
	
	return result;
}

/* PRE: {estado != NULL && verbosidad € {0, 1, 2} }
 * flujo = ImprimirFlujo (estado, verbosidad)
 * POS: { flujo >= 0 => (flujo == "flujo actual de (estado)"  &&
 *	  	         "se imprimió según (verbosidad)")
 *	  flujo < 0 => (error de ejecución)
 *	}
 */
long int ImprimirFlujo (EstadoNetwork *estado, int verbosidad)
{
	/* Precondiciones */
	ASSERT (estado != NULL)
	if ( VerbosidadInvalidaImprimir (verbosidad) ) {
		/* Verbosidad no valida */
		PRINTERR ("API: ImprimirFlujo: verbosidad inválida\n");
		return -1;
	}
	
 	qt_start (estado->cola);
			
	if (verbosidad == 2) {
		printf ("Flujo:\n");
		/* Llamamos a una función de node_stack (ns_cmd) que toma
		 * un conjunto de nodos (estado->nodes) y un conjunto de 
		 * índices (estado->nstack) que a cada nodo que esté
		 * contemplado en los índices le aplica la directiva
		 * pasada como 3º argumento (ImpresionFlujosAlf/Num) */
		if (estado->modoinput == 1)
			ns_cmd (estado->nstack, estado->nodes, &ImpresionFlujosAlf);
		else
			ns_cmd (estado->nstack, estado->nodes, &ImpresionFlujosNum);
	}
	
	if (verbosidad != 0) {
		if (estado->maximal)
			printf ("Valor del flujo maximal: %u\n\n", estado->flow_value);
		else
			printf ("Valor del flujo parcial: %u\n\n", estado->flow_value);
	}
	
	return estado->flow_value;
}

/* PRE: {estado != NULL && verbosidad € {0, 1} }
 * colores = ColorearNetwork  (estado, verbosidad)
 * POS: { colores >= 0 => ( colores  == "cantidad de colores utilizados"  
 *	  	  && "se imprimió según (verbosidad)")}
 */
u32 ColorearNetwork (EstadoNetwork *estado, int verbosidad)
{
	unsigned short K = 0;
	node_cmd printNC; /* Comando para imprimir el nodo y su color */

	/* Precondiciones */
	if ( VerbosidadInvalidaColorear (verbosidad)  ) {
		/* Verbosidad no valida */
		PRINTERR ("API: ColorearNetwork: verbosidad inválida\n");
		return 0;
	}
	if ( !estado->coloreo ) {
		/* Verbosidad no valida */
		PRINTERR ("API: ColorearNetwork: Error interno\n");
		return 0;
	}
	
	/* Imprimo el coloreo obtenido por first_coloring */
	printNC = ( estado->modoinput == 1 ) ? &ImpresionColoresAlf : &ImpresionColoresNum;
	
	if (estado->colores > 0){
		/*Se realizo un coloreo previo */
		K = ResolverConflictos(estado);
		ASSERT (K>0)

		if ( verbosidad == 1 ) {
			printf("Coloreo con First Coloring : %d\n" , K );  
			ns_cmd (estado->nstack , estado->nodes, printNC );
			printf("Cantidad de Colores utilizados: %d\n" , K ); 
		}
		estado->colores = K;
		if ( K <= estado->delta )return K;
	}
	
	K = color_greedy( estado->nstack , estado->nodes);
	ASSERT (K > 0)
	/* Imprimo el coloreo obtenido por greedy.
	   NOTA!: Los colores se imprimen en negativo , luego lo arreglare con una
		  funcion aparte. */
	if ( verbosidad == 1 ) {
		printf("Coloreo con Greedy : %d\n" , K );  
		ns_cmd (estado->nstack , estado->nodes, printNC );
		printf("Cantidad de Colores utilizados: %d\n" , K ); 
	}

	estado->colores = K;
	
	return K;
}


static void network_edgelist_destroy (u32 node_i , node_t * nodes)
{
	edgeList_t * fordward = NULL, * backward = NULL;

	fordward = nodes[node_i].forwardList;
	backward = nodes[node_i].backwardList;

	if (fordward != NULL) {
		el_clean (fordward);
		el_destroy (fordward);
		fordward = NULL;
	}
	if (backward != NULL) {
		el_destroy (backward);
		backward = NULL;
	}
}

/* PRE:	{estado != NULL}
* POS: {estado == NULL && "memoria libre :D"}
*/
void network_destroy  (EstadoNetwork * estado)
{
	/* pre */
	ASSERT (estado != NULL)
	
	/* Destruimos las aristas de la lista de nodos */
	ns_cmd(estado->nstack , estado->nodes ,network_edgelist_destroy);
	/* eliminamos el stack */
	if (estado->nstack != NULL) ns_destroy (estado->nstack);
	estado->nstack = NULL;
	/* eliminamos la lista de conflictivos */
	if (estado->l_con != NULL) el_destroy (estado->l_con);
	estado->l_con = NULL;
	/* eliminamos ahora la cola */
	if (estado->cola != NULL) qt_dinamic_destroy (estado->cola);
	estado->cola = NULL;
	/* eliminamos el network */
	free (estado); estado = NULL;
}
	
		

