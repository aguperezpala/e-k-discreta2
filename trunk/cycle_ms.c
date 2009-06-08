#include "cycle_ms.h"
#include "consts.h"

/********** Funciones internas **********/

void pivot(ticks *array, int desde, int hasta, int pivot, 
			  int *comienzoSegmentoPivot, int *finalSegmentoPivot);
void swap(ticks *array, int i, int j);
void moda(ticks *array, int desde, int hasta, int *ocurrenciasModa, int *posModa);

/********** Implementaciones **********/

void pivot(ticks *array, int desde, int hasta, int pivot, 
			  int *comienzoSegmentoPivot, int *finalSegmentoPivot){
	int i=0,j=0,pivotLocal;
	
	ASSERT (array != NULL)
	ASSERT (desde <= hasta)
		
	i = desde;
	j = hasta;
	pivotLocal = pivot;
	
	while (i<=j){
		if (array[i] < array[pivotLocal]){
			swap (array,i,pivotLocal);
			i++;
			pivotLocal++;
		}
		else{
			if (array[i] == array[pivotLocal]){
				if (array[i+1] < array[i]){
					swap (array,i,i+1);
					swap (array,i,pivotLocal);
					i++;
					pivotLocal++;
				}
				else i++;
			}
		}
		
		if (array[j] > array[pivotLocal]) j--;
		else{
			if (array[j] <= array[pivotLocal] && array[i] > array[pivotLocal]) 
				swap(array,i,j);
		}
			 
	}
		
	/* pivotLocal señala el comienzo del segmento que contiene las ocurrencias
	   del pivot y j señala su final */
	*comienzoSegmentoPivot = pivotLocal;
	*finalSegmentoPivot = j+1;
}

void swap(ticks *array, int i, int j){
	ticks aux = 0;
	aux = array[i];
	array[i] = array[j];
	array[j] = aux;
}

void moda(ticks *array, int desde, int hasta, int *ocurrenciasModa, 
		  int *posModa){
	int ocModaA=0,ocModaB=0,ocModaC=0,posA=0,posB=0,posC=0,comienzoSegmentoPivot=0,finalSegmentoPivot=0;
	
	if (desde == hasta){
		*posModa = desde;
		*ocurrenciasModa = 1;
	}
	else{
		
		if (desde < hasta){
			pivot(array, desde, hasta, desde, &comienzoSegmentoPivot,&finalSegmentoPivot);
			moda(array, desde, comienzoSegmentoPivot-1, &ocModaA, &posA);
			
			moda(array, finalSegmentoPivot, hasta, &ocModaB, &posB);
			
			ocModaC = max(ocModaA, ocModaB);
			if (ocModaC == ocModaA) posC = posA;
			else posC = posB;
			
			if (ocModaC > finalSegmentoPivot-comienzoSegmentoPivot){
				*posModa = posC;
				*ocurrenciasModa = ocModaC;
			}
			else{
				*posModa = comienzoSegmentoPivot;
				*ocurrenciasModa = finalSegmentoPivot-comienzoSegmentoPivot; 
			}
			
		}
	}
}

ticks calcularModa(ticks *array, int longitudArray){
	int ocurrenciasModa=0,posModa=0;
	
	moda(array, 0, longitudArray-1, &ocurrenciasModa, &posModa);
	
	return array[posModa];
}

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
	ticks t1,t2,limpio,shift,cpuid,rdtsc;
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
