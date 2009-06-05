#ifndef CYCLE_MS_H
#define CYCLE_MS_H

/* Ciclos de CPU */
typedef unsigned long long int ticks;

/* Nos devuelve el valor actual del "time-stamp counter".
	ret = getticks();
	POS : {ret contiene el valor actual del "time-stamp counter"}
*/
ticks getticks(void);

/* Devuelve una estimación de los ciclos de CPU que se consumen al
	ejecutarse la instrucción CPUID, la instrucción RDTSC y el corrimiento
	a izquierda en 32 lugares más el "or" bit a bit que efectúa getticks().
	PRE : {CPUID != NULL && shift != NULL && RDTSC != NULL}
	getEstimate(CPUID,shift,RDTSC);
	POS : {*CPUID contiene los ciclos consumidos por CPUID &&
			 *RDTSC "  "   "  "  "   "   "   "   "  "  RDTSC &&
			 *shift "  "   "  "  "   "   "   "   "  "  el corrimiendo
			 más el "or" bit a bit}
*/
void getEstimate(ticks *CPUID, ticks *shift, ticks *RDTSC);

#endif
