# minitalk
Aprender como funcional las señales en unix

## Por que estamos en este proyecto (Mi creencia)

1. Se basa en aprender y manejar señales 
	- Las señales es una forma de comunicacion entre procesos o micodigo.c en los sistemas unix
	- cuando un proceso recibe la señal o una funcionalidad de nuestro programa  se puede reaccionar de varias formas
		-Ignorar la señal
		-Acción predeterminada por el sistema como puede ser un control c para parar la ejecucion 
		- LLamar a una fuincion especifica comunmente llamados signal_handler

	- En este proyecto vamos a tener que manejar `SIGURS1` y `SIGURS2` son dos señales que podemos definir nosotros

## Basicos de las nuevas funciones permitidas 

`#include <singnal.h>`

`signal` 

## AVISO CUIDADO  Segun el man de signal
```bash
 WARNING: the behavior of signal() varies across UNIX versions,
       and has also varied historically across different versions of
       Linux.  Avoid its use: use sigaction(2) instead. 
```
- es mejor usar sigaction para que sea portable a todo tipo de sistema unix 

- La funcion signal recibe la señal que queremos utilizar y un puntero a una funcion que se realizara cada vez que usemos esa señal

```c

signal(SIGUSR1, handler_signal);

```
- Hemos dicho que va a pasar con esa señal cuando sea utilizada

para poder mandar la señal necesitamos una nueva funcion

`kill`

- Esta funcion recibe un pid que puede ser obtenido con `getpid()`
que va ser al proceso donde vamos a enviar la señal,

- y la señal a enviar 

```c
	Kill(pid, SIGURS1);
```
- Veamos como funcionara todo en un pequeño main de ejemplo

```c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>//libreria para signal y kill
#include <sched.h>

void handler_signal(int sig){
	printf("Comunicandome con el mundo despues de recibir el kill %d \n", sig);
}

int main()
{
	pid_t pid;
	signal(SIGUSR1, handler_signal);//recibe
	printf("Estoy en el main\n");
	pid = getpid();
	
	kill (pid, SIGUSR1);
	printf("Estoy en el main despues de la señal\n");
	return (0);
	
}
```
```bash
nakama@DESKTOP-FIDJ5EI:~/minitalk$ ./a.out
Estoy en el main
Comunicandome con el mundo despues de recibir el kill 10
Estoy en el main despues de la señal
```
- otra forma de decirle al programa que hacer con la señal es con la funcion

`sigaction()` y la `struct sigaction`

```c
int sigaction(int signum, const struct sigaction *act,struct sigaction *oldact)
```
- nos permite especificar como debe responder nuestro programa a ciertas señales 
	- El primer argumento es el numero de la señal que queremos manipular, estos numeros estan definidos por la libreria `signal.h`
	- el segundo argumento es un puntero a el `struct singaction` 
		```c
		struct sigaction 
		{
    		void      (*sa_handler)(int);	 // puntero a una función
    		void      (*sa_sigaction)(int, siginfo_t *, void *); // puntero a una función
    		sigset_t  sa_mask;     		// máscara de señales que se bloquearan durante el handler */
    		int       sa_flags;        		//  mascara de señales que se bloquearan durante la ejecucion de la funcion sigaction
    	void      (*sa_restorer)(void); 	// obpoleto NO USAR.
    	}
		
		```
- Actualizamos el main de ejemplo anterior

```c
int main()
{

	struct sigaction sgnl;
	sgnl.sa_handler = handler_signal;
	
	sigaction(SIGUSR1, &sgnl, NULL); 
	
	
	
	pid_t pid;
	printf("Estoy en el main\n");
	pid = getpid();
	
	kill (pid, SIGUSR1);
	printf("Estoy en el main despues de la señal\n");
	return (0);
	
}
```

```bash
nakama@DESKTOP-FIDJ5EI:~/minitalk$ ./a.out 
Estoy en el main
Comunicandome con el mundo despues de recibir el kill 
Estoy en el main despues de la señal
```
	