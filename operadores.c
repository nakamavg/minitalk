/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operadores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:46:11 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/06 02:33:22 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/libft/libft.h"
#include <signal.h>

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




char *convert_byte(char *message)
{
    int bit = 7;
    int index = 0;
    char *bits = malloc(strlen(message) * 8 + 1); // Asignar memoria para la cadena de bits
    int bit_index = 0;

    if(!message || !bits)
        exit(EXIT_FAILURE);

    while(message[index])
    {
        while(bit >= 0)
        {
            if (((message[index] >> bit) & 1) == 1) 
			{
                bits[bit_index++] = '1';
				printf("1");
			}
            else
			{
                bits[bit_index++] = '0';
				printf("0");
			}
			bit--;
        }
        bit = 7;
        index++;
    }
    bits[bit_index] = '\0'; // Terminar la cadena de bits con un carácter nulo
    return bits;
}
int main() {
	char a = 'h';

   	char *bits = convert_byte("Hola");
	printf("\n");
    debite(bits);
	printf("\n");
    free(bits);
    return 0;
}
