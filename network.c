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
};


/** ~~~~~~~~~~~~~~~~~~~~~~ FUNCIONES AUXILIARES INTERNAS ~~~~~~~~~~~~~~~~~~~~ */

#define max(a, b) ((a>b) ? a : b)
#define min(a, b) ((a<b) ? a : b)

/* Indica si el modo de input es soportado por la API */
#define ModoinputValido(x)	((x == 1) || (x == 2))

/* Indica si el modo de verbosidad es soportado por la API */
#define VerbosidadValida(x)	((x == 0) || (x == 1) || (x == 2) || (x == 3))

static inline void AñadirLadoAlf (EstadoNetwork *estado,
				   char vert1, char vert2, u32 cap)
{
	u32 v1, v2, m;
	
	ASSERT (estado != NULL)
	
	v1 = (u32) vert1;
	v2 = (u32) vert2;
	
	m = max(v1, v2);
	if (m > estado->mayor) estado->mayor = m;
	
	/*! TODO: <ACTUALIZAR ARISTAS>
		  <AGREGAR NODOS SI ES NECESARIO>
	 	  <SETEAR COLORES DE LOS NODOS>
	 	  <ACTUALIZAR DELTA DEL ESTADONETWORK>
	 */
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
	}
	
	/* Poscondición 
	ASSERT(ret->maximal == false)
	ASSERT(ret->completo == false)
*/	
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
		estado->nodes[i].fordwardList = NULL;
		estado->nodes[i].backwardList = NULL;
	}
		
	
	if (estado->nodes != NULL) ret = 1;
	
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
		char vert1, vert2;
		char *scan;
		u32 cap;
		
		/* Guardamos en "edge" lo leído */
		memset (edge, '\0', 13);
		scanf ("%[^\n]", &edge);
		getchar ();
		
		/* ¿Mal formato? */
		if (edge[2] != ' ') {
			printf ("Finalizó la lectura de lados\n");
			goto end0;
		}
		
	/*! TODO <CAMBIAR STRTOL POR UNA FUNC. PROPIA QUE DEVUELVA U32> */
		cap = (u32) strtol (edge+3, &scan, 10);
		
		/* ¿Mal formato? */
		if (*scan != '\0') {
			printf ("Finalizó la lectura de lados\n");
			goto end0;
		}
		
		vert1 = edge[0];
		vert2 = edge[1];
		
		AñadirLadoAlf (estado, vert1, vert2, cap);
		
		goto end1;
		
	} else {
		/* Input numérico */
		
		/*! TODO <EN CONSTRUCCIÓN> */
		
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
		assert (false);
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

