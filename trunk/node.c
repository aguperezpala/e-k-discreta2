#include "consts.h"
#include "node.h"

/* recordemos que tenemos tambien el caso alfabetico, podriamos usar entero
 * para el alfabetico simplemente casteandolo o usando atoi...
 */
struct s_node {
	u32 nodeName;	/* numérico => el nº ; alfabético => atoi (ASCII) */
	u32 €; 		/* flujo */
	edgeList_t fordwardList;	/* lista de aristas fordware */
	edgeList_t backwardList;	/* lista de aristas backward */
	bool state;		/* despues deberiamos ver si es nescesario */
};
	
struct s_edge {
	u32 capacity;
	u32 flow;
	node_t * node;	/* puntero al nodo que conecta (for ó back) */
};