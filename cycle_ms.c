#include "cycle_ms.h"
#include "consts.h"

ticks getticks(void){
	 unsigned int a, d;
		
	__asm__("cpuid");
	__asm__("rdtsc" : "=a" (a), "=d" (d));
	
	return (((ticks)a) | (((ticks)d)<<32));
}

void getEstimate (ticks *CPUID, ticks *shift, ticks *RDTSC){
	ticks t1,t2,res1,res2,res3,res4,res5;
	unsigned int a=0, d=0, c=0;
		
	/* Precondición */
	ASSERT (CPUID != NULL);
	ASSERT (shift != NULL);
	ASSERT (RDTSC != NULL);
	
	t1=getticks();
	c = (((ticks)a) | (((ticks)d)<<32));
	t2=getticks();
	
	res1=t2-t1;
	#ifdef __DEBUG
	printf("\nres1 -> cpuid+rdtsc+shift+shift+cpuid+rdtsc+shift: %llu\n",res1);
	#endif
	
	t1=getticks();
	t2=getticks();
	res2=t2-t1;
	
	#ifdef __DEBUG
	printf("\nres2 -> cpuid+rdtsc+shift+cpuid+rdtsc+shift: %llu\n",res2);
	#endif
	/* En res3 están los ciclos consumidos para efecutar el 
		corrimiento y el "or" bit a bit */
	res3=res1-res2;
	
	#ifdef __DEBUG
	printf("\nres3=res1-res2 -> shift: %llu\n",res3);
	#endif

	t1=getticks();
	__asm__("cpuid");
	t2=getticks();
	
	res4 = (t2-t1);
	
	#ifdef __DEBUG
	printf("\nt2-t1 -> cpuid+rdtsc+shift+cpuid+cpuid+rdtsc+shift: %llu\n",res4);
	#endif

	/* En res4 están los ciclos empleados para efectuar cpuid */
	res4 = res4-res2;
	
	#ifdef __DEBUG
	printf("\nres4=(t2-t1)-res2 -> cpuid: %llu\n",res4);
	#endif
	/* Finalmente, para calcular los ciclos empleados en realizar RDTSC
		le restamos a res 2 los ciclos empleados para CPUID (2*res4) y los
		empleados para el "left-shifting" y para el "or" bit
		a "bit" (2*res3). Lo que obtenemos son los ciclos empleados para 2
	   instrucciones RDTSC. */
	res5 = res2-res4-res4-res3-res3;

	#ifdef __DEBUG
	printf("\nres5=res2-res4-res4-res3-res3 -> rdtsc+rdtsc: %llu\n",res5);
	#endif
}
