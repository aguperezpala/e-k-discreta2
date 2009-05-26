#include <stdbool.h>
#include "network.h"



struct s_estado_network{
	node_t nodes[7000];
	u32 flow_value;	/*! <Estudiar si conviene!!!> */
	bool maximal;	/* si tenemos un flujo maximal */
	bool completo;	/* si se ingresaron todos los lados */
	short delta;	/* Considerandolo grafo, el delta */
	short colors;	/* Nº de colores obtenido por el coloreo */
};


/** ~~~~~~~~~~~~~~~~~~~~~~ FUNCIONES AUXILIARES INTERNAS ~~~~~~~~~~~~~~~~~~~~ */


/* Indica si el modo de input es soportado por la API */
#define ModoinputValido(x)	((x == 1) || (x == 2))
/*! BORRAR LO DE ABAJO */
/*static inline bool ModoinputValido (int modoinput)
{
	if ((modoinput == 1) ||
	    (modoinput == 2) )
		return true;
	else
		return false;
}*/


/* Indica si el modo de verbosidad es soportado por la API */
#define VerbosidadValida(x)	((x == 0) || (x == 1) || (x == 2) || (x == 3))
/*! BORRAR LO DE ABAJO */
/*static inline bool VerbosidadValida (int verbosidad)
{
	if ((verbosidad == 0) ||
	    (verbosidad == 1) ||
	    (verbosidad == 2) ||
	    (verbosidad == 3) )
		return true;
	else
		return false;
}*/



/** ~~~~~~~~~~~~~~~~~~~~~ FUNCIONES DE LA API (EXTERNAS) ~~~~~~~~~~~~~~~~~~~~ */


INLINE EstadoNetwork *network_create(void)
{
	EstadoNetwork *ret = NULL;

	ret = (EstadoNetwork*)malloc(sizeof(struct s_estado_network));
	
	if(ret != NULL){
		ret->flow_value = 0;
		ret->maximal  = false;
		ret->completo = false;
		ret->delta  = 0;
		ret->colors = 0;
	}
	
	/* Poscondición 
	ASSERT(ret->maximal == false)
	ASSERT(ret->completo == false)
*/	
	return ret;
}


INLINE int Inicializar(EstadoNetwork *estado, int modoinput)
{
	int ret = 0, i, n;
	
	/* Precondiciones */
	ASSERT(estado != NULL)
	if ( ! ModoinputValido(modoinput) ) {
		fprintf (stderr, "Network: Inicializar: modoinput inválido\n");
		assert  (false);
	}

	/* {modoinput == 1 || modoinput == 2} */
	if (modoinput == 1)
		/* Se espera input alfabético: ASCII(A) = 65, ASCII(a) = 97 */
		n = 52;
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
		assert  (false);
	}
	
	if (modoinput == 1) {
		/* Input alfabético */
		char vert1;
		char vert2;
		char cap[10];
		
		scanf ("%c%c %s", &vert1, &vert2, &cap);
		
	switch (modoinput) {
		char edge[10];
		char capacity[10];
		
		case 1:
			scanf ("%s %[^\n]s", &edge, %capacity);
	}
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

