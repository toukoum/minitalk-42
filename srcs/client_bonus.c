/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:51:03 by rgiraud           #+#    #+#             */
/*   Updated: 2023/12/02 22:15:48 by rgiraud          ###   ########.fr       */
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
	encrypt_to_two('\0', pid);
}

void	check_send(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("\033[0;95mMessage well send bro !\033[0m\n");
}

int	main(int argc, char **argv)
{
	int					pid_server;
	char				*message;
	struct sigaction	action;

	if (argc == 3)
	{
		action.sa_flags = 0;
		sigemptyset(&action.sa_mask);
		action.sa_handler = check_send;
		sigaction(SIGUSR1, &action, NULL);
		pid_server = ft_atoi(argv[1]);
		message = argv[2];
		send_message(message, pid_server);
	}
	else
	{
		ft_printf("\033[0;95mError\n");
		ft_printf("Try: ./client_bonus 'PID' 'MESSAGE'\033[0m\n");
		return (1);
	}
	return (0);
}
