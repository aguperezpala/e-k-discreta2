#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void)
{
	char edge[12];
	char vert1, vert2;
	char *scan;
	unsigned int cap;
	

	while (true) {
		memset (edge, '\0', 12);
		printf ("Enter next edge: ");
		scanf ("%[^\n]", &edge);
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
	
	end:
	{
			printf ("Goodbye, thanks for beeing so gay!\n");
			return 0;
	}
}

