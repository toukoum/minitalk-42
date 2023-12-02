/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:37:06 by rgiraud           #+#    #+#             */
/*   Updated: 2023/12/02 22:16:02 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	encrypt_to_two(unsigned char letter, int pid)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		bit = letter & 128;
		letter <<= 1;
		i++;
		if (bit == 128)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(I_TIME);
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
}

int	main(int argc, char **argv)
{
	int		pid_server;
	char	*message;

	if (argc == 3)
	{
		pid_server = ft_atoi(argv[1]);
		message = argv[2];
		send_message(message, pid_server);
	}
	else
	{
		ft_printf("\033[0;95mError. Try: ./client 'PID' 'MESSAGE'\033[0m\n");
		return (1);
	}
	return (0);
}
