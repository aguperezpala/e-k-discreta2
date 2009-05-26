#include <stdio.h>
#include <ctype.h>

int main (void)
{
	char c;
	unsigned int  ascii;
	
	for (c = 32; c < 127; c++) {
		printf("Ascii %d is %c\n", c, c);
		ascii = (int) c;
		printf("Again, %c is ascii %u\n", c, ascii);
	}
	
	return 0;
}

