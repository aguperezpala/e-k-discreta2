#ifndef NETWORK_H
#define NETWORK_H

typedef struct s_estado_network EstadoNetwork;
/* Construye un objeto EstadoNetwork.
   ret = network_create();
   POS : {(ret != NULL => ret es un objeto EstadoNetwork vacío) && 
	      (ret == NULL => no hay memoria para el objeto EstadoNetwork)}
 */
INLINE EstadoNetwork *network_create(void);

/* PRE : {estado != NULL && (modmoinput==1 || modoinput==2)}
   ret = Inicializar(estado,modoinput);
   POS : {(ret == 1 => estado tiene capacidad, según modoinput para almacenar 
		   nodos) && (ret == 0 => no hay memoria para alojar los nodos)}
 */
INLINE int Inicializar(EstadoNetwork *estado, int modoinput);

/* PRE : {estado != NULL && (modmoinput==1 || modoinput==2)} 
   ret = LeerUnLado(estado,modoinput);
   POS : {(ret == 1 => estado contiene ahora el lado ingresado) && 
	   	  (ret == 0 => error al leer los datos ingresados)}
*/
INLINE int LeerUnLado(EstadoNetwork *estado, int modoinput);
