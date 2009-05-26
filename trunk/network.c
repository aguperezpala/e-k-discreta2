#include <stdbool.h>
#include "network.h"



struct s_estado_network{
	node_t nodes[7000];
	u32 flow_value;	/* Estudiar si conviene!!! */
	bool maximal;	/* si tenemos un flujo maximal */
	bool completo;	/* si se ingresaron todos los lados */
	short delta;	/* Considerandolo grafo, el delta */
	short colors;	/* Nº de colores obtenido por el coloreo */
}



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

INLINE int Inicializar(EstadoNetwork *estado, int modoinput){
	int ret = 0, i = 0, n = 0;
	
	/* Precondición */
	ASSERT(estado != NULL);
	/* Quizás sería mejor devolver un mensaje de error */
	ASSERT(modoinput == 1 || modoinput == 2); 

	/* {modoinput == 1 || modoinput == 2} */
	switch(modoinput){
		case 1:
			/* Se espera input alfabético: ASCII(A) = 65, ASCII(a) = 97 */
			n = 52;
		break;
			
		case 2:
			n = 7000;
		/* Se espera input numérico, y la pu~@#@ç$! */
		break;
		
			
	}
	
	for (i = 0 ; i < n ; i++) {
		estado.nodes[i].fordwardList = NULL;
		estado.nodes[i].backwardList = NULL;
	}
		
	
	if(estado->nodes != NULL) ret = 1;
	
	return ret;
}

/* PRE: {estado != NULL && verbosidad € {0, 1, 2, 3} }
ret = AumentarFlujo (estado, verbosidad)
POS: {ret == 0 => *//*! ### NOTE TODO TEST <COMPLETAR COMPLETAR> ###
*/
INLINE int AumentarFlujo (EstadoNetwork *estado, int verbosidad)
{
	
}

/*! ### NOTE TODO TEST <COMPLETAR COMPLETAR> ### */
INLINE u32 ImprimirFlujo (EstadoNetwork *estado, int verbosidad)
{

}

/*! ### NOTE TODO TEST <COMPLETAR COMPLETAR> ### */
INLINE u32 ColorearNetwork (EstadoNetwork *estado, int verbosidad)
{

}

