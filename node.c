#include "node.h"

/* recordemos que tenemos tambien el caso alfabetico, podriamos usar entero
 * para el alfabetico simplemente casteandolo o usando atoi...
 */
struct s_node {
	unsigned int nodeName;	/* caso numerico */
	List fordwardList;	/* lista de aristas fordware */
	List backwardList;	/* lista de aristas backward */
	bool state;		/* despues deveriamos ver si es nescesario */
	unsigned int epsilon;	/* hace falta esto ? */
};
	
struct s_edge {
	unsigned int capacity;
	unsigned int flow;
	node_t * node;		/* puntero al nodo que conecta */
};