/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:15:20 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/26 18:57:51 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (*(s + i))
		write(fd, (s + i++), 1);
}

int	valid_pid(char *pid)
{
	int	i;

	i = 0;
	while (*(pid + i))
	{
		if (*(pid + i) < '0' || *(pid + i) > '9')
			return (0);
		i++;
	}
	return (1);
}

void	send_char(pid_t server_pid, unsigned char c)
{
	int						i;
	unsigned char			curr_bit;

	i = 7;
	while (i >= 0)
	{
		curr_bit = (c >> i--) % 2;
		if (curr_bit == 0)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(600);
	}
}

void	signal_handler(int signal, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	if (signal == SIGUSR1)
		ft_putstr_fd("Message received successfully", 1);
}

int	main(int argc, char **argv)
{
	char							*msg;
	struct sigaction				sa;
	pid_t							server_pid;

	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <pid> <msg>\n", 2);
		exit(1);
	}
	server_pid = atoi(argv[1]);
	if (server_pid <= 0 && !valid_pid(argv[1]) && kill(server_pid, 0) != -1)
	{
		ft_putstr_fd("Usage: ./client <pid> <msg>\n", 2);
		exit(1);
	}
	msg = argv[2];
	while (*msg)
		send_char(server_pid, *(msg++));
	send_char(server_pid, '\0');
	return (0);
}
