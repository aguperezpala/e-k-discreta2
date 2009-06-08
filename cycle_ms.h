#ifndef CYCLE_MS_H
#define CYCLE_MS_H

/* Ciclos de CPU */
typedef unsigned long long int ticks;

/* Nos devuelve el valor actual del "time-stamp counter".
   ret = getticks();
   POS : {ret contiene el valor actual del "time-stamp counter"}
*/
ticks getticks(void);

/*  Devuelve la cantidad de ciclos que se deben restar a la medición realizada
    con getticks().
	ret = getResiduo();
	POS : {ret contiene los ciclos empleados para las instrucciones CPUID, 
		   RDTSC, los "left-shifting" y disyunciones bit a bit}
*/
ticks getResiduo (void);

/* 
*/
ticks calcularModa(ticks *array, int longitudArray);
#endif
