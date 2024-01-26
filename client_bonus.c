/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:15:20 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/26 09:15:43 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	exit_handler(void)
{
	printf("Usage: ./client <pid> <msg>\n");
	exit(1);
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
		usleep(50);
	}
}

void	signal_handler(int signal, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	if (signal == SIGUSR1)
		printf("Bit 1 delivired successfully!\n");
	else if (signal == SIGUSR2)
		printf("Bit 0 delivired successfully!\n");
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
		exit_handler();
	server_pid = atoi(argv[1]);
	if (server_pid <= -1)
		exit_handler();
	msg = argv[2];
	while (*msg)
		send_char(server_pid, *(msg++));
	send_char(server_pid, '\0');
	return (0);
}
