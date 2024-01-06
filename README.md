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
# Cual es realmente el problema de este ejercicio

-  Estamos utilizando señales Unix para la comunicación entre procesos y estas señales solo pueden enviar la presencia o ausencia de una señal, por lo tanto enviar bits 0 y 1 es la forma mas efectiva de trasmitir una mayor cantidad de datos

- Antes  de volverme loco con el problema mis investigaciones llegaron a este operador

- `<< >>`
- Para entender como funciona primero usaremos 

- es decir 
```plaintext
00000000 = 0 00000001 = 1
00000010 = 2 00000011 = 3
00000100 = 4 00000101 = 5
00000110 = 6 00000111 = 7
00001000 = 8 00001001 = 9
00001010 = 10 00001011 = 11
etc. hasta llegar a 11111111 = 255 que es el tamaño de un byte
```

```c
int main() {
    int num = 4; 
    printf("Número original: %d\n", num);
	print_binary(num);

    
    int left_shift = num << 1; 
    printf("Desplazamiento a la izquierda: %d\n", left_shift); 
    print_binary(left_shift);
    int right_shift = num >> 1; 
    printf("Desplazamiento a la derecha: %d\n", right_shift);
	print_binary(right_shift);
    return 0;
}
```
```bash
nakama@DESKTOP-FIDJ5EI:~/minitalk$ ./a.out 
Número original: 4
00000000000000000000000000000100
Desplazamiento a la izquierda: 8
00000000000000000000000000001000
Desplazamiento a la derecha: 2
00000000000000000000000000000010
```
- Cuando decimos que`<< 1` `>> 1` corre el bit o desplaza la izquierda estamos diciendo que:
	- empuja afuera por  la izq de nuestros binarios 1 bit y nos añade uno por la derecha
	- empuja afuera por la derecha y nos añade uno por la derecha

- De que me sirve esto ? para recorrer cada bit de cada Byte de Cada array

```c
#include <stdlib.h>
#include <unistd.h>
#include "lib/libft/libft.h"


void convert_byte(char *message)
{
	int bit;
	bit = 7;
	int index = 0;
	if(!message)
		exit(EXIT_FAILURE) ;
	while(message[index])
	{
			
		while(bit >= 0)
		{
			
			if (((message[index] >> bit) & 1) == 1) 
				ft_printf("1");
			else
				ft_printf("0");
			bit--;
		}
		bit = 7;
		index++;
	}
	ft_printf("\n");
}
int main() {
    
	convert_byte("Hola");
    return 0;
}

```
```bash
nakama@DESKTOP-FIDJ5EI:~/minitalk$ ./a.out 
01001000011011110110110001100001

```
-  Nos devuelve por el output los 8 bits  de cada char de nuestra cadena
	1. iteramamos con el index el char en el que estamos
	2. iteramos los 8 bis como las posiciones empiezan en 0 nuestra validacion para cada iteracion sera 7
	3. LA MAGIA `if (((message[index] >> bit) & 1) == 1)`
		1. en la primera iteración no cambia el caracter por que estamos desplazando hacia la derecha 7 veces un char de 8 bits
		2. realiza una puerta logica and con 1 
			1. 0  y 1 es 0
			2. 1 y  1 es 1 
	4. y asi sucesivamente para el resto de los bits de los bytes de el string

- Ya tendriamos la logica para escribir bits solo queda cambiar esto en vez de imprimir 
	por terminal enviar señales a nuestro server.

## Hay pero espera que el servidor tendria que rehacer cada bit no ...

- Logica para debitear? 

```c
void debite(char *bits)
{
    int bite = 0;
    unsigned char ch = '\0';
    int index = 0;

    while(bits[index])
    {
        ch <<= 1;
        if (bits[index] == '1')
            ch |= 1; 

	    bite++;
        if (bite == 8)
        {
            ft_printf("%c", ch);
            bite = 0;
            ch = '\0';
        }

        index++;
    }

}
```
```bash
nakama@DESKTOP-FIDJ5EI:~/minitalk$ ./a.out 
01001000011011110110110001100001
Hola
```

- Bueno lo primero de todo es tener nuesto ch inicializado para ir recibiendo los valores
	- Nos aseguramos de que valga cero dandole `\0`
- al empezar `ch` vale 00000000
	-  desplazamos todos los bits a la izquerda sigue valiendo lo mismo
	- ahora bien si lo que nos llega es 1 hacemos un or por que 0 o 1 siempre va a ser 1
	- si lo que nos llega es un 0 ch sigue valiendo 0
- Resumiendo vamos pintando 1 y 0 reconstruyendo el bite desde la derecha desplazando en cada iteraccion del byte 
	- si tenemos 00000000 y despues del and or vale  00000001
	- en el siguiente desplazamiento seria 00000010
- Cuando el byte valga 8 ya tendremos el char reconstruido y lo podremos sacar por pantalla

