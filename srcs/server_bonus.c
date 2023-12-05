/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:50:55 by rgiraud           #+#    #+#             */
/*   Updated: 2023/12/05 12:07:38 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int		g_pid_server;

char	*ft_realloc_str(char *message, int idx_message, int byte)
{
	static int	buffer_size;
	char		*result;

	if (idx_message >= buffer_size)
	{
		if (buffer_size == 0)
			buffer_size = 128;
		else
			buffer_size *= 2;
		result = malloc(buffer_size * sizeof(char));
		if (!result)
		{
			free(message);
			exit(1);
		}
		ft_memcpy(result, message, idx_message);
		free(message);
	}
	else
		result = message;
	result[idx_message] = byte;
	result[idx_message + 1] = '\0';
	return (result);
}

void	ft_add_char_to_str(int byte)
{
	static char	*message;
	static int	idx_message;

	if (byte == '\0')
	{
		write(1, message, idx_message);
		write(1, "\n", 1);
		free(message);
		message = NULL;
		idx_message = 0;
		kill(g_pid_server, SIGUSR1);
		return ;
	}
	if (!message)
	{
		message = malloc(128 * sizeof(char));
		if (!message)
			exit(1);
		message[idx_message] = byte;
		message[1] = '\0';
		idx_message++;
		return ;
	}
	message = ft_realloc_str(message, idx_message, byte);
	idx_message++;
}

void	add_byte_to_seq(int bit)
{
	static int	byte;
	static int	byte_size;

	byte <<= 1;
	byte += bit;
	if (byte_size == 7)
	{
		ft_add_char_to_str(byte);
		byte = 0;
		byte_size = 0;
	}
	else
		byte_size++;
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	g_pid_server = info->si_pid;
	if (signum == SIGUSR1)
		add_byte_to_seq(1);
	else
		add_byte_to_seq(0);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	ft_printf("\033[1;92mServeur démarré !\033[0m\n");
	ft_printf("\033[1;94m--> PID Serveur: \033[1;93m%d\033[0m\n", getpid());
	ft_printf("\033[1;90mEn attente de messages...\033[0m\n");
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
