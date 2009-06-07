#include "cycle_ms.h"
#include "consts.h"

INLINE ticks getticks(void){
	 unsigned int a, d;
		
	__asm__("cpuid");
	__asm__("rdtsc" : "=r" (a), "=r" (d));
	/* Le efectuamos un "left-shifting" en 32 lugares, a la variable donde están 
	   almacenados los 32 bits de mayor peso y luego efectuamos un "or" bit a
	   bit con los 32 bits de menor peso. Hemos recuperado el contenido del
	   "time-stamp counter */
	return (((ticks)a) | (((ticks)d)<<32));
}

INLINE ticks getResiduo (void){
	ticks t1,t2,completo,shift,cpuid,rdtsc;
	unsigned a,d;/* Para acceder al contenido de los registros a y d */
	
	/* Simplemente llamamos a rdtsc 2 veces, una "inmediatamente" después de la
	   otra. El resultado de esta medición nos servirá para obtener en limpio
	   los ciclos que emplean las instrucciones que nos interesan. */
	/************************************/
	__asm__("cpuid");
	__asm__("rdtsc" : "=a" (a), "=d" (d));
	t1=((ticks)a) | (((ticks)d)<<32);
	/************************************/
	
	/************************************/
	__asm__("cpuid");
	__asm__("rdtsc" : "=a" (a), "=d" (d));
	t2=((ticks)a) | (((ticks)d)<<32);
	/************************************/
	limpio=t2-t1;
	
	
	/************************************/
	__asm__("cpuid");
	__asm__("rdtsc" : "=a" (a), "=d" (d));
	t1=((ticks)a) | (((ticks)d)<<32);
	/************************************/
	d=((ticks)a) | (((ticks)d)<<32);
	/************************************/
	__asm__("cpuid");
	__asm__("rdtsc" : "=a" (a), "=d" (d));
	t2=((ticks)a) | (((ticks)d)<<32);
	/************************************/
	/* en shift ahora tenemos los ciclos consumidos para un "left-shifting" y un
	   "or" bit a bit */
	shift=(t2-t1)-limpio;
	
	/************************************/
	__asm__("cpuid");
	__asm__("rdtsc" : "=a" (a), "=d" (d));
	t1=((ticks)a) | (((ticks)d)<<32);
	/************************************/
	__asm__("cpuid");
	/************************************/
	__asm__("cpuid");
	__asm__("rdtsc" : "=a" (a), "=d" (d));
	t2=((ticks)a) | (((ticks)d)<<32);
	/************************************/
	/* en cpuid ahora tenemos los ciclos consumidos por una instrucción CPUID */
	cpuid=(t2-t1)-limpio;
	
	/************************************/
	__asm__("cpuid");
	__asm__("rdtsc" : "=a" (a), "=d" (d));
	t1=((ticks)a) | (((ticks)d)<<32);
	/************************************/
	__asm__("rdtsc" : "=a" (a), "=d" (d));
	/************************************/
	__asm__("cpuid");
	__asm__("rdtsc" : "=a" (a), "=d" (d));
	t2=((ticks)a) | (((ticks)d)<<32);
	/************************************/
	/* en shift ahora tenemos los ciclos consumidos por una instrucción RDTSC */
	rdtsc=(t2-t1)-limpio;
	
	/* Los ciclos que se deben restar a la medición son los empleados para
	   2 instrucciones cpuid, 2 instrucciones rdtsc y 2 "left-shifting" junto 
	   con 2 disyunciones bit a bit */
	
	return 2*cpuid + 2*rdtsc + 2*shift;
}
