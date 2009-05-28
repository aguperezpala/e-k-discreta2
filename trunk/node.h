/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD node (vértices), versión 1.0.0, del proyecto único de
 * Discreta 2, FaMAF, año 2009
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */


#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>
#include "consts.h"

/*! #include "listType.h": deberiamos nosotros (lo vamos a hacer) implementar este
 * TAD. Eficientemente y usando esos truquitos para poder diferenciar los 2 sub
 * conjuntos (los habilitados y deshabilitados).
 */


/* definimos los tipos (NO es TAN mala practica definir los 2 tipos aca mismo) */




 /* recordemos que tenemos tambien el caso alfabetico, podriamos usar entero
 * para el alfabetico simplemente casteandolo o usando atoi...
 */
typedef struct s_node {
	
	/*!u32 nodeName;		No hace falta, el nombre es el indice mismo */
	u32 flux; 			/* flujo */
	edgeList_t *forwardList;	/* lista de aristas forward  */
	edgeList_t *backwardList;	/* lista de aristas backward */
	bool state;			/*! <HACE FALTA???> */
	int colour;
	/* int satur;	Agregarlo en caso de que usemos DSATUR */
} node_t;


typedef struct s_edge {
	u32 capacity;
	u32 flow;
	u32 nodeOrig;
	u32 nodeDest;
	/*! Podriamos probar con short */
} edge_t;

/* Creamos una arista
	REQUIRES:
		0 <= nodeOrig, nodeDest < 7000
*/
INLINE edge_t * edge_create (u32 capacity, u32 nodeOrig, u32 nodeDest);


/*! los que le decia de las funciones inline, aca les paso un link
 * http://www.greenend.org.uk/rjk/2003/03/inline.html 
 */

#endif
