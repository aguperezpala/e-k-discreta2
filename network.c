	#include <stdbool.h>
#include "network.h"



struct s_estado_network{
	node_t nodes[7000];
	u32 flow_value;	/*! TODO <Estudiar si conviene!!!> */
	bool maximal;	/* si tenemos un flujo maximal */
	bool completo;	/* si se ingresaron todos los lados */
	short mayor;	/* vértice de "mayor nombre" ingresado */
	short delta;	/* Considerandolo grafo, el delta */
	short colores;	/* Nº de colores obtenido por el coloreo */
	edgeList_t l_con;	/* Lista de lados conflictivos para el coloreo */
};


/** ~~~~~~~~~~~~~~~~~~~~ FUNCIONES AUXILIARES INTERNAS ~~~~~~~~~~~~~~~~~~~~~~ */

#define max(a, b) ((a>b) ? a : b)
#define min(a, b) ((a<b) ? a : b)

/* Indica si el modo de input es soportado por la API */
#define ModoinputValido(x)	((x == 1) || (x == 2))

/* Indica si el modo de verbosidad es soportado por la API */
#define VerbosidadValida(x)	((x == 0) || (x == 1) || (x == 2) || (x == 3))


/* Añade un lado al EstadoNetwork, actualizando todos los campos necesarios.
 * Esta versión tiene en cuenta el coloreo incremental de los vértices.
 *
 * PRE: estado != NULL
 */
/*! NOTE <ESTO ESTÁ HECHO PARA COLOREO> puede hacerse más eficiente sino */
static inline void AñadirLado (EstadoNetwork *estado, u32 v1, u32 v2, u32 cap)
{
	u32  m;
	edge_t *edge;
	bool v1new = false, v2new = false;
	
	ASSERT (estado != NULL)
	
	m = max(v1, v2);
	if (m > estado->mayor) estado->mayor = m;
	
	/* ahora debemos verificar si tenemos que generar la fordwareList o backward */
	if (estado->nodes[v1].forwardList == NULL) {
		estado->nodes[v1].forwardList = el_create ();
		
		/** NOTE Lo que sigue es para coloreo */
		if (estado->nodes[v1].backwardList == NULL) {
			/* v1 es vértice nuevo */
			v1new = true;
			estado->nodes[v1].delta = 0;
		}
	}
	
	if (estado->nodes[v2].backwardList == NULL) {
		estado->nodes[v2].backwardList = el_create ();
		
		/** NOTE Lo que sigue es para coloreo */
		if (estado->nodes[v1].forwardList == NULL) {
			/* v2 es vértice nuevo */
			v2new = true;
			estado->nodes[v2].delta = 0;
		}
	}
	
	/* creamos la arista */
	edge = edge_create (cap, v1, v2);
	
	/* Agregamos a ambas listas */
	el_add_edge (estado->nodes[v1].forwardList, edge);
	estado->nodes[v1].delta++;
	el_add_edge (estado->nodes[v2].backwardList, edge);
	estado->nodes[v2].delta++;
	
	/* Seteamos el delta de todo el network/grafo */
	m = max (estado->nodes[v1].delta, estado->nodes[v2].delta);
	if (estado->delta < m) estado->delta = m;
	
	
	/** NOTE Lo que sigue es para coloreo */
	if (v1new) {
		if (v2new) {
			/* Ambos vértices eran nuevos */
			estado->nodes[v1].colour = 1;
			estado->nodes[v2].colour = 2;
		} else
			/* v1 es nuevo, lo coloreamos sin conflicto */
			estado->nodes[v1].colour = 3 - estado->nodes[v2].colour;
	} else if (v2new)
		/* v2 es nuevo, lo coloreamos sin conflicto */
		estado->nodes[v2].colour = 3 - estado->nodes[v1].colour;
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
INLINE EstadoNetwork *network_create (void)
{
	EstadoNetwork *ret = NULL;

	ret = (EstadoNetwork*)malloc(sizeof(struct s_estado_network));
	
	if(ret != NULL){
		ret->flow_value = 0;
		ret->maximal  = false;
		ret->completo = false;
		ret->delta  = -1;
		ret->colors = -1;
		ret->l_con = el_create ();
	}
	
	return ret;
}


/* PRE : {estado != NULL && (modmoinput==1 || modoinput==2)}
 * ret = Inicializar(estado,modoinput);
 * POS : {(ret == 1 => estado tiene capacidad, según modoinput para almacenar 
 *		nodos) && (ret == 0 => no hay memoria para alojar los nodos)}
 */
INLINE int Inicializar (EstadoNetwork *estado, int modoinput)
{
	int ret = 0, i, n;
	
	/* Precondiciones */
	ASSERT(estado != NULL)
	if ( ! ModoinputValido(modoinput) ) {
		fprintf (stderr, "Network: Inicializar: modoinput inválido\n");
		return 1;
	}

	/* {modoinput == 1 || modoinput == 2} */
	if (modoinput == 1)
		/* Se espera input alfabético */
		n = 123;
		/* Esto cubre desde ASCII 32  para ' ' (el 1º)
	 	 *	      hasta ASCII 122 para 'z' (el último) */
	else
		/* Se espera input numérico, y la pu~@#@ç$! */
		n = 7000;
	
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
INLINE int LeerUnLado(EstadoNetwork *estado, int modoinput)
{
	ASSERT (estado != NULL);
	if (! ModoinputValido(modoinput) ) {
		fprintf (stderr, "Network: LeerUnLado: modoinput inválido\n");
		return 0;
	}
	
	/* {modoinput == 1 || modoinput == 2} */
	if (modoinput == 1) {
		/* Input alfabético */
		char edge[13];
		char *scan = NULL;
		u32 v1, v2, cap;
		
		/* Guardamos en "edge" lo leído */
		/*memset (edge, '\0', 13); NOTE: no hace falta*/
		/** NOTE ¿Como es inicializada "char edge[13]"? */
		scanf ("%[^\n]", &edge);
		getchar ();
		
		/* ¿Mal formato? */
		if (edge[2] != ' ') {
			printf ("Finalizó la lectura de lados\n");
			goto end0;
		}
		
		/* Guardamos la capacidad en cap */
		cap = (u32) strtol (edge+3, &scan, 10);
		
		/* ¿Mal formato? */
		if (*scan != '\0') {
			printf ("Finalizó la lectura de lados\n");
			goto end0;
		}
		
		/* Obtenemos el ASCII del nombre de los vértices */
		v1 = (u32) edge[0];
		v2 = (u32) edge[1];
		
		AñadirLado (estado, v1, v2, cap);
		
		goto end1;
		
	} else {
		/* Input numérico */
		char vert1[5], vert2[5], capacity[10];
		char *scan = NULL;
		u32 v1, v2, cap;
		
		/* Obtenemos el 1º vértice */
		scanf ("%s", &vert1);
		v1 = (u32) strtol (vert1, &scan, 10);
		
		/* ¿Mal formato? */
		if (*scan != '\0') {
			printf ("Finalizó la lectura de lados\n");
			goto end0;
		}
		
		/* Obtenemos el 2º vértice */
		scanf ("%s", &vert2);
		v1 = (u32) strtol (vert2, &scan, 10);
		
		/* ¿Mal formato? */
		if (*scan != '\0') {
			printf ("Finalizó la lectura de lados\n");
			goto end0;
		}
		
		/* Obtenemos la capacidad */
		scanf ("%s", &capacity);
		cap = (u32) strtol (vert1, &scan, 10);
		
		/* ¿Mal formato? */
		if (*scan != '\0') {
			printf ("Finalizó la lectura de lados\n");
			goto end0;
		}
		
		/* Guardamos la capacidad en cap */
		cap = (u32) strtol (edge+3, &scan, 10);
		
		AñadirLado (estado, v1, v2, cap);
		
		goto end1;
		
		/** ¿¿¿ Deberíamos hacer el mismo parseo sintáctico ??? */
		
	}
	
	end1:
			return 1;
	end0:
			return 0;
}


/* PRE: {estado != NULL && verbosidad € {0, 1, 2, 3} }
ret = AumentarFlujo (estado, verbosidad)
POS: {ret == 0 => *//*! ### NOTE TODO TEST <COMPLETAR COMPLETAR> ###
*/
INLINE int AumentarFlujo (EstadoNetwork *estado, int verbosidad)
{
	/* Precondiciones */
	ASSERT (estado != NULL);
	if ( ! VerbosidadValida(verbosidad) ) {
		fprintf (stderr, "Network: AumentarFlujo: verbosidad inválida\n");
		return /*###*/;
	}
	
	
}


/*! ### NOTE TODO TEST <COMPLETAR COMPLETAR> ### */
INLINE u32 ImprimirFlujo (EstadoNetwork *estado, int verbosidad)
{

}

/*! ### NOTE TODO TEST <COMPLETAR COMPLETAR> ### */
INLINE u32 ColorearNetwork (EstadoNetwork *estado, int verbosidad)
{

}

