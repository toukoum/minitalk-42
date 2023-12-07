/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:50:55 by rgiraud           #+#    #+#             */
/*   Updated: 2023/12/07 08:25:32 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	add_byte_to_seq(int bit, int pid_server)
{
	static int	byte = 0;
	static int	byte_size = 1;

	byte <<= 1;
	byte += bit;
	if (byte_size == 8)
	{
		if (byte == '\0')
		{
			kill(pid_server, SIGUSR2);
			write(1, "\n", 1);
		}
		else
			ft_printf("%c", byte);
		byte = 0;
		byte_size = 1;
	}
	else
		byte_size++;
	kill(pid_server, SIGUSR1);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		add_byte_to_seq(1, info->si_pid);
	else
		add_byte_to_seq(0, info->si_pid);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	ft_printf("\033[1;92mServeur démarré !\033[0m\n");
	ft_printf("\033[1;94m--> PID Serveur: \033[1;93m%d\033[0m\n", getpid());
	ft_printf("\033[1;90mEn attente de messages...\033[0m\n");
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
		sleep(1);
	return (0);
}
