#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main (void)
{
	char edge[12], vertice1[5], vertice2[5], capacity[10];
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
			memset (edge, '\0', 12);
			printf ("Enter next edge: ");
			scanf ("%[^\n]", (char *) &edge);
			getchar ();
			
			if (edge[2] != ' ') {
				fprintf (stderr, "Finalizó la lectura de lados\n");
				goto end;
			}
				
			vert1 = edge[0];
			vert2 = edge[1];
			cap = (unsigned int) strtol (edge+3, &scan, 10);
			
			if (*scan != '\0') {
				fprintf (stderr, "Finalizó la lectura de lados\n");
				goto end;
			}
				
			printf ("\nvert1: %c\nvert2: %c\ncapacity: %u\n",
				vert1, vert2, cap);
		}
		
	} else if (inputmode == 2) {
		while (true) {
			printf ("Enter next edge: ");
			
			/* Obtenemos el 1º vértice */
			scanf ("%[^ ]", (char *) &vertice1);
			v1 = (unsigned int) strtol (vertice1, &scan, 10);
			getchar();
			
			/** "%[^!-/:-~]" */
			/* ¿Mal formato? */
			if (*scan != '\0') {
				printf ("Finalizó la lectura de lados\n");
				goto end;
			}
			
			/* Obtenemos el 2º vértice */
			scanf ("%[^ ]", (char *) &vertice2);
			v1 = (unsigned int) strtol (vertice2, &scan, 10);
			getchar ();
			
			/* ¿Mal formato? */
			if (*scan != '\0') {
				printf ("Finalizó la lectura de lados\n");
				goto end;
			}
			
			/* Obtenemos la capacidad */
			scanf ("%[^\n]", (char *) &capacity);
			cap = (unsigned int) strtol (capacity, &scan, 10);
			getchar();
			
			/* ¿Mal formato? */
			if (*scan != '\0') {
				printf ("Finalizó la lectura de lados\n");
				goto end;
			}
			
			printf ("\nv1: %u\nv2: %u\ncap: %u\n", v1, v2, cap);
		}
	} else
		goto end;
	
	end:
	{
			printf ("Goodbye, thanks for beeing so gay!\n");
			return 0;
	}
}

