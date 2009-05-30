/* Librerías públicas */
#include <stdbool.h>
/* Librerías personales */
#include "consts.h"
#include "node.h"
#include "edge.h"
#include "edge_list.h"
#include "network.h"



struct s_estado_network{
	node_t nodes[7000];
	tripleList_t *cola;	/* Cola de las corridas E-K */
	u32 flow_value;	/*! TODO <Estudiar si conviene!!!> */
	bool maximal;	/* si tenemos un flujo maximal */
	bool completo;	/* si se ingresaron todos los lados */
	bool coloreo;	/* si nos llamaron con la opción de coloreo */
	short modoinput;
	short mayor;	/* vértice de "mayor nombre" ingresado */
	short delta;	/* Considerandolo grafo, el delta */
	short colores;	/* Nº de colores obtenido por el coloreo */
	edgeList_t l_con;	/* Lista de lados conflictivos para el coloreo */
};



/** ~~~~~~~~~~~~~~~~~~~~ FUNCIONES AUXILIARES INTERNAS ~~~~~~~~~~~~~~~~~~~~~~ */


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
		ret->cola = tl_create ();
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
	if ( ! ModoinputValido(modoinput) ) {
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
		n = 7000;
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
	if (! ModoinputValido(modoinput) ) {
		fprintf (stderr, "Network: LeerUnLado: modoinput inválido\n");
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
			goto end0;
		}
		
		
		if (strlen (edge+3) > 10) {
			/* Capacidad mayor que u32 */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			goto end0;
		}
		
		/* Guardamos la capacidad en cap */
		cap = (u32) strtol (edge+3, &scan, 10);
		
		if (*scan != '\0') {
			/* La capacidad no era un entero */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			goto end0;
		}
		
		/* Obtenemos el ASCII del nombre de los vértices */
		v1 = (u32) edge[0];
		v2 = (u32) edge[1];
		
		if (!IsAscii (v1) || !IsAscii (v2)){
			/* Los vértices no eran letras */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			goto end0;
		} else {
			if (estado->coloreo)
				AñadirLadoColor (estado, v1, v2, cap);
			else
				AñadirLado (estado, v1, v2, cap);
		
		/* Se agregó bien el lado */
		goto end1;
		
	} else {
		/** Input numérico */
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
			goto end0;
		}
		
		ptr1[0] = '\0'; /* Aislamos el 1º vértice */
		ptr1++;
		if (strlen (ptr2) > 10) {
			/* Nombre de vértice mayor que u32 */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			goto end0;
		}	 
		v1 = (unsigned int) strtol (ptr2, &scan, 10);
		if (*scan != '\0') {
			/* El vértice 1 no era un entero */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			goto end0;
		}
		
		/* Extraemos el 2º vértice */
		
		ptr2 = ptr1;
		ptr1 = strchr (ptr2, ' ');
		if (ptr1 == NULL) {
			/* No había espacios tras el 1º vértice */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			goto end0;
		}
		
		ptr1[0] = '\0'; /* Aislamos el 2º vértice */
		ptr1++;
		if (strlen (ptr2) > 10) {
			/* Nombre de vértice mayor que u32 */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			goto end0;
		}	 
		v2 = (unsigned int) strtol (ptr2, &scan, 10);
		if (*scan != '\0') {
			
			fprintf (stderr, "Finalizó la lectura de lados\n");
			goto end0;
		}
		
		/* Extraemos la capacidad */
		
		ptr2 = ptr1;
		if (strlen (ptr2) > 10) {
			/* Capacidad mayor que u32 */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			goto end0;
		}
			
		cap = (unsigned int) strtol (ptr2, &scan, 10);
		if (*scan != '\0') {
			/* Capacidad no era un entero */
			fprintf (stderr, "Finalizó la lectura de lados\n");
			goto end0;
		}
		
		if (estado->coloreo)
			AñadirLadoColor (estado, v1, v2, cap);
		else
			AñadirLado (estado, v1, v2, cap);
		
		/* Se agregó bien el lado */
		goto end1;
	}
	
	end1:
			return 1;
	end0:
			return 0;
}


/* PRE: {estado != NULL && verbosidad € {0, 1, 2, 3} }
ret = AumentarFlujo (estado, verbosidad)
POS: {ret == 0 => *//*! TODO <COMPLETAR COMPLETAR> */
int AumentarFlujo (EstadoNetwork *estado, int verbosidad)
{
	int result = 0;
	u32 s, t, indiceActual;
	unsigned short corrida;
	node_t  actual;
	edge_t *edge;
	bool empty = false; /* "¿Se vació la cola?" */
	int endList = 0;
	
	/* Precondiciones */
	ASSERT (estado != NULL)
	if ( ! VerbosidadValida(verbosidad) ) {
		fprintf (stderr, "Network: AumentarFlujo: verbosidad inválida\n");
		return /*###*/;
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
	tl_initialize (estado->cola, s);
	/* Nos paramos en 's' */
	tl_start (estado->cola);
	/* Aumentamos y registramos la versión de corrida E-K */
	corrida = estado->nodes[s].corrida++;
	
	indiceActual = tl_get_actual_node (estado->cola);
	
	while (!empty && indiceActual != t) { /* Ciclo principal */
		
		actual = estado->nodes[indiceActual];
		el_start (actual.forwardList);
		
		while (endList == 0) { /* Ciclo "lados forward" */
			
			edge = el_get_actual (actual.forwardList);
			
			if (edge->flow < edge->capacity) {
				
				
			
			endList = el_avance (actual.forwardList);
			
	
	/*! TODO <EN CONSTRUCCIÓN> */
	
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

