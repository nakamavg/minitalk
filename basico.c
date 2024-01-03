/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basico.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:51:33 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/03 21:06:37 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Programa basico para ver como funcional las señales de unix en C con procesos padre e hijo
*/

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

