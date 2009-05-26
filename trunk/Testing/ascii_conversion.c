#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define is_int(x)	( ((x == '0') || (x == '1') || (x == '2') || (x == '3') \
			   (x == '4') || (x == '5') || (x == '6') || (x == '7') \
			   (x == '8') || (x == '9')) ? true : false )


static inline bool IsInt (const char *cadena, unsigned int *entero)
{
	unsigned short i, n;
	char c;
	
	n = strlen (cadena);
	
	for (i=0 ; i<n ; i++) {
		c = cadena[i];
		if (is_int (c))
			*entero += pow (10, (n-i)) * (unsigned int) c;
		else
			goto end2;
	}
	
	end1:
			return true;
	end2:
			return false;
}


/* Devuelve el resultado de x elevado a la n-ésima potencia 
   PRE: n > 0
*/
static inline unsigned int pow (unsigned int x, unsigned int n)
{
	unsigned int i, y=x;
	
	for (i=1 ; i<n ; i++)
		y *= x;
	
	return y;
}

		
int main (void)
{
	char c;
	char entero[10], nonetero[10];
	unsigned int  ascii;
	
/*	for (c = 32; c < 127; c++) {
		printf("Ascii %d is %c\n", c, c);
		ascii = (unsigned int) c;
		printf("Again, %c is ascii %u\n", c, ascii);
	}
*/	
	memset (entero, '\0', 10);
	memset (noentero, '\0', 10);
	entero[0] = '0';
	entero[1] = '1';
	entero[2] = '2';
	entero[3] = '3';
	entero[4] = '4';
	entero[5] = '5';
	noentero[0] = '0';
	noentero[0] = '1';
	noentero[0] = '2';
	noentero[0] = ' ';
	noentero[0] = '0';
	noentero[0] = '0';
	if (IsInt (entero, &ascii))
		printf ("cadena: %s\tentero: %u\n", entero, ascii);
	
	return 0;
}

