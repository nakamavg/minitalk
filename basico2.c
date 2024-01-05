#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void sumar(int a, int b)
{
	int c = a + b;
	printf("La suma es %d , con un pid de %d: \n", c,getpid());
}


int main()
{
	int fd[2];
	printf("Estoy en el main\n");
	printf("El pid es %d \n", getpid());
	sumar(2,3);
}