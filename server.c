/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:15:03 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/26 09:15:10 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	signal_handler(int signal, siginfo_t *info, void *ctx)
{
	static int						bit_i;
	static unsigned char			curr_char;
	static pid_t					c_pid;

	(void)ctx;
	if (info->si_pid != c_pid)
	{
		c_pid = info->si_pid;
		bit_i = 0;
		curr_char = 0;
	}
	curr_char |= (signal == SIGUSR1);
	bit_i++;
	if (bit_i == 8)
	{
		if (curr_char == '\0')
			printf("\n");
		else
			printf("%c", curr_char);
		bit_i = 0;
		curr_char = 0;
	}
	else
		curr_char <<= 1;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	printf("%d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
