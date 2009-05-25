#include "network.h"

struct s_estado_network{
	node_t *nodes;
	u32 flow_value; /* Estudiar si conviene!!! */
	int maximal; /* 1 <=> tenemos un flujo maximal */
	int completo; /* 1 <=> se ingresaron todos los lados */
}

INLINE EstadoNetwork *network_create(void){
	EstadoNetwork *ret = NULL;

	ret = (EstadoNetwork*)malloc(sizeof(struct s_estado_network));
	
	if(ret != NULL){
		ret->maximal = 0;
		ret->completo = 0;
	}
	
	/* Poscondición */
	ASSERT(ret->maximal == 0);
	ASSERT(ret->completo == 0);
	
	return ret;
}

INLINE int Inicializar(EstadoNetwork *estado, int modoinput){
	int ret = 0;
	
	/* Precondición */
	ASSERT(estado != NULL);
	/* Quizás sería mejor devolver un mensaje de error */
	ASSERT(modoinput == 1 || modoinput == 2); 

	/* {modoinput == 1 || modoinput == 2} */
	switch(modoinput){
		case 1:
			/* Se espera input alfabético: ASCII(A) = 65, ASCII(a) = 97 */
		estado->nodes = (node_t*)malloc(52*sizeof(node_t));
		break;
			
		case 2:
		/* Se espera input alfabético */
			estado->nodes = (node_t*)malloc(7000*sizeof(node_t));
		break;
	}
	
	if(estado->nodes != NULL) ret = 1;
	
	return ret;
}

