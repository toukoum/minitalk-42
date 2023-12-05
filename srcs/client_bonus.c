/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:51:03 by rgiraud           #+#    #+#             */
/*   Updated: 2023/12/05 17:14:12 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

int		g_synch_bit;

void	encrypt_to_two(unsigned char letter, int pid)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		if (kill(pid, 0) < 0)
		{
			ft_printf("invalid or null PID : %d\n", pid);
			exit(EXIT_FAILURE);
		}
		g_synch_bit = 0;
		bit = letter & 128;
		letter <<= 1;
		i++;
		if (bit == 128)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_synch_bit != 1)
			usleep(10);
	}
}

void	send_message(char *message, int pid)
{
	int	i;

	i = 0;
	while (message[i])
	{
		encrypt_to_two(message[i], pid);
		i++;
	}
	encrypt_to_two('\0', pid);
}

void	check_send(int signum)
{
	if (signum == SIGUSR2)
	{
		ft_printf("\033[0;95mMessage well send bro !\033[0m\n");
		exit(EXIT_SUCCESS);
	}
	else if (signum == SIGUSR1)
		g_synch_bit = 1;
}

int	main(int argc, char **argv)
{
	int	pid_server;

	if (argc != 3)
	{
		ft_printf("\033[0;95mError\n");
		ft_printf("Try: ./client_bonus 'PID' 'MESSAGE'\033[0m\n");
		return (1);
	}
	signal(SIGUSR1, &check_send);
	signal(SIGUSR2, &check_send);
	pid_server = ft_atoi(argv[1]);
	if (!pid_server)
	{
		ft_printf("INVALID PIN !");
		exit(EXIT_FAILURE);
	}
	send_message(argv[2], pid_server);
	while (1)
		sleep(1);
	return (0);
}
