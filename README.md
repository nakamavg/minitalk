# minitalk
Aprender como funcional las señales en unix

## Basicos de las nuevas funciones permitidas 

`#include <singnal.h>`

`signal`

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