/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:10:33 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/06 01:44:43 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"



static void	handler(int sig)
{
	static int bite = 0;
	static unsigned char ch = '\0';
	ch <<= 1;
	if (sig == SIGUSR1)
		ch |= 1; 
	bite++;
	if (bite == 8)
	{
		ft_printf("%c", ch);
		bite = 0;
		ch = '\0';
	}
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
	ft_printf("Welcome to the MiniTalk server by dgomez_m\n");
	ft_printf("MY PID: %d\n", getpid());
	getpid();
	server();

	while(42)
	{

		sleep(300);
	}
	return (0);
}