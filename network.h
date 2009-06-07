/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * API verión 1.0.0 del proyecto único de Discreta 2, FaMAF, año 2009
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */
 
/* Librerías públicas */
#include <stdbool.h>
/* Librerías personales */
#include "consts.h"
#include "node.h"
#include "edge_list.h"
#include "quad_list.h"
#include "node_stack.h"


#ifndef NETWORK_H
#define NETWORK_H



typedef struct s_estado_network {
	node_t nodes[MAX_N_NODES];
	quadList_t *cola;	/* Cola de las corridas E-K */
	u32 flow_value;	/* valor de flujo actual */
	bool maximal;	/* si tenemos un flujo maximal */
	bool completo;	/* si se ingresaron todos los lados */
	bool coloreo;	/* si nos llamaron con la opción de coloreo */
	short modoinput;
	short delta;	/* Considerandolo grafo, el delta */
	short colores;	/* Nº de colores obtenido por el coloreo */
	edgeList_t * l_con;	/* Lista de lados conflictivos para el coloreo */
	node_s nstack;	/* Stack que guarda los nodos que fueron agregados */
} EstadoNetwork;



/* Construye un objeto EstadoNetwork.
 * ret = network_create();
 * POS : {(ret != NULL => ret es un objeto EstadoNetwork vacío) && 
 *		(ret == NULL => no hay memoria para el objeto EstadoNetwork)}
 */
EstadoNetwork *network_create(bool coloreo);


/* PRE : {estado != NULL && (modmoinput==1 || modoinput==2)}
 * ret = Inicializar(estado,modoinput);
 * POS : {(ret == 1 => estado tiene capacidad, según modoinput para almacenar 
 *		nodos) && (ret == 0 => no hay memoria para alojar los nodos)}
 */
int Inicializar(EstadoNetwork *estado, int modoinput);


/* PRE : {estado != NULL && (modmoinput==1 || modoinput==2)} 
 * ret = LeerUnLado(estado,modoinput);
 * POS : {(ret == 1 => estado contiene ahora el lado ingresado) && 
 *		(ret == 0 => error al leer los datos ingresados)}
*/
int LeerUnLado(EstadoNetwork *estado, int modoinput);



/* PRE: {estado != NULL && verbosidad € {0, 1, 2, 3} }
 * ret = AumentarFlujo (estado, verbosidad)
 * POS: {(ret == 0 => Se pudo aumentar el flujo)	&&
 *	 (ret == 1 => No se pudo aumentar el flujo)	&&
 *	 (ret == 2 => Se produjo un error)			 }
 */
int AumentarFlujo (EstadoNetwork *estado, int verbosidad);


/* PRE: {estado != NULL && verbosidad € {0, 1, 2} }
 * flujo = ImprimirFlujo (estado, verbosidad)
 * POS: { flujo >= 0 => (flujo == "flujo actual de (estado)"  &&
 *	  	         "se imprimió según (verbosidad)")
 *	  flujo < 0 => (error de ejecución)
 *	}
 */
long int ImprimirFlujo (EstadoNetwork *estado, int verbosidad);


/* PRE: {estado != NULL && verbosidad € {0, 1} }
 * colores = ColorearNetwork  (estado, verbosidad)
 * POS: { colores >= 0 => ( colores  == "cantidad de colores utilizados"  
 *	  	  && "se imprimió según (verbosidad)")}
 */
u32 ColorearNetwork (EstadoNetwork *estado, int verbosidad);



#endif
