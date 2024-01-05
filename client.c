/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:50:10 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/05 02:56:59 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void check_arguments(int argc)
{
	if (argc == 1)
	{
		ft_putstr_fd(ARGUMENTS_ERROR, 2);
		exit(EXIT_FAILURE);
	}
	else if (argc > 3)
	{
		ft_putstr_fd(ARGUMENTS_MAX_ERROR, 2);
		exit(EXIT_FAILURE);
	}
}
int get_pid(char *pid)
{
	int pid_int;
	pid_int = ft_atoi(pid);
	if (pid_int <= 0)
	{
		ft_putstr_fd(PID_ERROR, 2);
		exit(EXIT_FAILURE);
	}
	return (pid_int);
	
}
static void  send_signal(const int pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		ft_putstr_fd(FAILED_MESSAGE, 2);
		exit(EXIT_FAILURE);
	}
	usleep(300); //sirve para que el servidor tenga tiempo de recibir la señal
}
static void convert_byte(int pid, char *message)
{
	int i;
	int j;
	int bit;
	// hola en binario es 01101000 01101111 01101100 01100001
	i = 0;
	if(!message)
		exit(EXIT_FAILURE) ;
	while(message[i])
	{
		j = 0;
		while (j < 8)
		{
			bit = (message[i] >> (7 - j)) & 1;
			printf("bit %d\n", bit);
			if (bit == 1)
				send_signal(pid, SIGUSR1);
			else
				send_signal(pid, SIGUSR2);
			++j;
			usleep(100);
		}
		++i;
	}
}

int main(int argc , char **argv)
{
	int pid;
	int i;
	
	check_arguments(argc);
	pid = get_pid(argv[1]);
	convert_byte(pid, argv[2]);
}