#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/types.h>
#include <time.h>


#define is_ascii_int(x)  ((x > 47) && (x < 58))

/* Devuelve el resultado de x elevado a la n-ésima potencia 
   PRE: n > 0
*/
static unsigned int pot (unsigned int x, unsigned int n)
{
	unsigned int i=n, y=x;
	
	for (i=1 ; i<n ; i++)
		y *= x;
	
	return y;
}

/* Si cadena representa un entero, es convertido a unsigned int y devuelto por *entero
 * PRE: *entero == 0
 */
static bool IsInt (const char *cadena, unsigned int *entero)
{
	unsigned int i, n;
	char c;
	
	n = strlen (cadena);
	
	for (i=0 ; i<n ; i++) {
		c = cadena[i];
		if (is_ascii_int (c)) {
			/* ASCII DE '0' == 48 */
			if (c != '0')
				*entero += pot (10, (n-i)) * ((unsigned int) c - 48);
		} else
			goto end2;
	}
	
	
	return true;
	
	end2:
			return false;
}



int main (void)
{
	char entero[10];
	char *scan = NULL;
	unsigned int  ascii, way1 = 0, way2 = 0;
	int i; 
	time_t t1,t2;
	char c;
	
	for (c = 32; c < 127; c++) {
		printf("Ascii %d is %c\n", c, c);
		ascii = (unsigned int) c;
		printf("Again, %c is ascii %u\n", c, ascii);
	}
	
	memset (entero, '\0', 10);
	entero[0] = '0';
	entero[1] = '1';
	entero[2] = '2';
	entero[3] = '3';
	entero[4] = '4';
	entero[5] = '5';
	
	/** Forma propia */
	for (i = 0 ; i < 50000000 ; i++) {
		ascii = 0;
		
		(void) time(&t1);
		
		if (IsInt (entero, &ascii))
			/* Do something */;
		else
			/* Do something else */;
		
		(void) time (&t2);
		
		way1 += (unsigned int) t2 - t1;
		
		if (i%10000000 == 0){
			printf ("Iteración NUESTRA # %d\n", i);
			printf ("ascii = %u\n", ascii);
		}
	}
	
	/** Forma Linux */
	for (i = 0 ; i < 50000000 ; i++) {
		(void) time(&t1);
		
		ascii = (unsigned int) strtol (entero, &scan, 10);
		if (*scan == '\0')
			/* Do something */;
		else
			/* Do something else */;
		
		(void) time (&t2);
		
		way2 +=  (unsigned int) t2 - t1;
		
		if (i%10000000 == 0) {
			printf ("Iteración LINUX # %d\n", i);
			printf ("ascii = %u\n", ascii);
		}
	}
	
	printf ("Forma nuestra tarda: %u segundos\n", way1);
	printf ("Forma LINUX   tarda: %u segundos\n", way2);
		
		
	return 0;
}

