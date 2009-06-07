#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main (void)
{
	char edge[30];
	char vert1, vert2;
	char *scan;
	unsigned int v1, v2, cap;
	int inputmode;
	

	printf ("Please choose the input mode:\n");
	printf (" 1- Alphabetical (\"v1v2 capacity\")\n");
	printf (" 2- Numerical (\"v1 v2 capacity\")\n");
	scanf ("%d", &inputmode);
	
	if (inputmode == 1) {
		while (true) {
			printf ("Enter next edge: ");
			getchar ();
			scanf ("%[^\n]", (char *) &edge);
			
			if (edge[2] != ' ') {
				printf ("Faltó el espacio entre vértices y cap\n");
				fprintf (stderr, "Finalizó la lectura de lados\n");
				break;
			}
				
			vert1 = edge[0];
			vert2 = edge[1];
			cap = (unsigned int) strtol (edge+3, &scan, 10);
			
			if (*scan != '\0') {
				printf ("La capacidad no era un nº\n");
				fprintf (stderr, "Finalizó la lectura de lados\n");
				break;
			}
				
			printf ("\nvert1: %c\nvert2: %c\ncapacity: %u\n",
				vert1, vert2, cap);
		}
		
	} else if (inputmode == 2) {
		char *ptr1 = NULL, *ptr2 = NULL;
		
		while (true) {
			getchar();
			printf ("Enter next edge: ");
			scanf ("%[^\n]", (char *) &edge);
			
			ptr1 = (char *) edge;
			
			/* Extraemos el 1º vértice */
			
			ptr2 = ptr1; /* Recordamos el comienzo de la cadena */
			ptr1 = strchr (ptr2, ' ');
			/* ¿Mal formato? */
			if (ptr1 == NULL) {
				printf ("v1(1): %s\n", ptr2);
				printf ("Finalizó la lectura de lados\n");
				break;
			}
			
			ptr1[0] = '\0'; /* Aislamos el 1º vértice */
			ptr1++;
			if (strlen (ptr2) > 10) {
				printf ("Nombre de vértice no soportad\n");
				printf ("Nombre de vértice: %s\n", ptr2);
				printf ("Finalizó la lectura de lados\n");
				break;
			}	 
			v1 = (unsigned int) strtol (ptr2, &scan, 10);
			/* ¿Mal formato? */
			if (*scan != '\0') {
				printf ("v1(2): %s\n", ptr2);
				printf ("Finalizó la lectura de lados\n");
				break;
			}
			
			/* Extraemos el 2º vértice */
			
			ptr2 = ptr1; /* Recordamos el comienzo de la cadena */
			ptr1 = strchr (ptr2, ' ');
			/* ¿Mal formato? */
			if (ptr1 == NULL) {
				printf ("v2(1): %s\n", ptr2);
				printf ("Finalizó la lectura de lados\n");
				break;
			}
			
			ptr1[0] = '\0'; /* Aislamos el 2º vértice */
			ptr1++;
			if (strlen (ptr2) > 10) {
				printf ("Nombre de vértice no soportad\n");
				printf ("Nombre de vértice: %s\n", ptr2);
				printf ("Finalizó la lectura de lados\n");
				break;
			}	 
			v2 = (unsigned int) strtol (ptr2, &scan, 10);
			/* ¿Mal formato? */
			if (*scan != '\0') {
				printf ("v2(2): %s\n", ptr2);
				printf ("Finalizó la lectura de lados\n");
				break;
			}
			
			/* Extraemos la capacidad */
			
			ptr2 = ptr1;
			if (strlen (ptr2) > 10) {
				printf ("Capacidad no soportada\n");
				printf ("Capacidad: %s\n", ptr2);
				printf ("Finalizó la lectura de lados\n");
				break;
			}
				
			cap = (unsigned int) strtol (ptr2, &scan, 10);
			/* ¿Mal formato? */
			if (*scan != '\0') {
				printf ("cap: %s\n", ptr2);
				printf ("Finalizó la lectura de lados\n");
				break;
			}
			
			printf ("\nv1: %u\nv2: %u\ncap: %u\n", v1, v2, cap);
		}
	}
	
	printf ("Goodbye, thanks for beeing so gay!\n");
	return 0;
}

