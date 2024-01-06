#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/libft/libft.h"
//aprender a recorrer un string con un puntero y un while y leer el valor de cada caracter pode mandarlo como signal
//por que mandamos un signal por cada bit y no todo el byte de una vez
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
				printf("1");
			else
				printf("0");
			bit--;
		}
		bit = 7;
		index++;
	}
	printf("\n");
}



int main(void)
{
	//esto es una a en binario
	char  *message = "Hola";
	convert_byte(message);
	return (0);
}