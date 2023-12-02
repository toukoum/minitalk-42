/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:37:02 by rgiraud           #+#    #+#             */
/*   Updated: 2023/12/02 22:16:11 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_signal_data	g_sigdata;

void	add_byte_to_seq(int bit)
{
	g_sigdata.byte <<= 1;
	g_sigdata.byte += bit;
	if (g_sigdata.byte_size == 8)
	{
		ft_printf("%c", g_sigdata.byte);
		g_sigdata.byte = 0;
		g_sigdata.byte_size = 1;
	}
	else
		g_sigdata.byte_size++;
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		add_byte_to_seq(1);
	else
		add_byte_to_seq(0);
}

int	main(void)
{
	struct sigaction	act;

	g_sigdata.byte = 0;
	g_sigdata.byte_size = 1;
	act.sa_handler = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	ft_printf("\033[1;92mServeur démarré !\033[0m\n");
	ft_printf("\033[1;94m--> PID Serveur: \033[1;93m%d\033[0m\n", getpid());
	ft_printf("\033[1;90mEn attente de messages...\033[0m\n");
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
