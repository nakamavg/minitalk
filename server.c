/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:10:33 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/05 03:36:08 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void mini_print(void)
{
	ft_printf("__   __    ___     __    _  ___     _______  _______  ___      ___   _    ______   _______  __   __  ___   ______     _______         __   __ \n");
    ft_printf("|  |_|  |  |   |   |  |  | ||   |   |       ||   _   ||   |    |   | | |  |      | |   _   ||  | |  ||   | |      |   |       |       |  |_|  |\n");
    ft_printf("|       |  |   |   |   |_| ||   |   |_     _||  |_|  ||   |    |   |_| |  |  _    ||  |_|  ||  |_|  ||   | |  _    |  |    ___| ____  |       |\n");
    ft_printf("|       |  |   |   |       ||   |     |   |  |       ||   |    |      _|  | | |   ||       ||       ||   | | | |   |  |   | __ |____| |       |\n");
    ft_printf("|       |  |   |   |  _    ||   |     |   |  |       ||   |___ |     |_   | |_|   ||       ||       ||   | | |_|   |  |   ||  |       |       |\n");
    ft_printf("| ||_|| |  |   |   | | |   ||   |     |   |  |   _   ||       ||    _  |  |       ||   _   | |     | |   | |       |  |   |_| |       | ||_|| |\n");
    ft_printf("|_|   |_|  |___|   |_|  |__||___|     |___|  |__| |__||_______||___| |_|  |______| |__| |__|  |___|  |___| |______|   |_______|       |_|   |_|\n");
}

static void	handler(int sig)
{
	static int bit_count = 0;
	static unsigned char bit = 0;
	//en caso de que hayamos recibido una a
	//la es en binario es 01100101
	bit <<= 1;
	if (sig == SIGUSR1)
		bit |= 1; // el operador |= es un OR bit a bit que significa que si alguno de los dos bits es 1 el resultado es 1
	++bit_count;
	if (bit_count == 8)
	{
		printf("%c", bit);
		write(1, &bit, 1);
		bit_count = 0;
		bit = 0;
	}
	kill(getpid(), SIGUSR2);
}



static void server(void)
{
	struct sigaction talk;
	talk.sa_handler = handler;
	talk.sa_flags = SA_RESTART; 
	
	
	if (sigaction(SIGUSR1, &talk, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &talk, NULL) == -1)
		exit(EXIT_FAILURE);
}




int	main()

{
	mini_print();
	ft_printf("Welcome to the MiniTalk server by dgomez_m\n");
	ft_printf("MY PID: %d\n", getpid());
	getpid();
	server();
	while(42)
	{

		server();
		pause();
	}
	return (0);
}