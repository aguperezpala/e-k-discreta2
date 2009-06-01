/* MACK-EK versión 1.0
 * Implementación eficiente del algoritmo Edmonds-Karp para hallar un flujo
 * maximal en un network
 *
 * TAD print_s (pila de impresión) Es utilizado para la impresión de los
 * caminos hallados por las corridas de AumentarFlujo
 *
 * Autores:  Budde, Carlos E.
 *	     Kondrasky, Alejandro
 *	     Pérez Paladini, Agustín
 *	     Soldevilla, Mallku R.
 *
 * Revisión: Penazzi, Daniel
 *
 */


#ifnedf PRINT_L_H
#define PRINT_L_H



typedef struct _print_s print_s;



/* Genera una nueva pila de impresión vacía
 *
 *    ps = ps_create()
 * POS: ps != NULL
 */
print_s *ps_create (void);


/* Destruye la pila de impresión
 *
 * PRE: ps != NULL
 *    ps_destroy(ps)
 * POS: los recursos de memoria de ps han sido liberados
 */
void ps_destroy (print_s *ps);


/* Añade un nuevo vértice 'v' al comienzo de la pila de impresión.
 *
 * PRE: ps != NULL  &&  sentido == 1,2
 *    ps = ps_add_node (ps, v, sentido);
 * POS: "ps contiene a 'v' como último elemento" &&
 *	sentido == ','  =>  se considera "forward" la relación entre 'v'
 *			    y el vértice anterior de la pila
 *	sentido == '<'  =>  se considera "backward" la relación entre 'v'
 *			    y el vértice anterior de la pila
 */
print_s *ps_add_node (print_s *ps, u32 v, char sentido);


/* Imprime la pila en orden LIFO, es decir, el último elemento agregado
 * será el primero en ser impreso
 *
 * PRE: ps != NULL  &&  modoinput == 1,2
 *    ps_print (ps, modoinput, flujo)
 * POS: modoinput == 1  =>  se considera el código ascii de 'v'
 *	modoinput == 2  =>  se considera el valor numérico de 'v'
 */
void ps_print (print_s *ps, int modoinput, u32 flujo);


#endif

