/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:19:40 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/26 11:00:11 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	n = n % 10 + '0';
	write(fd, &n, 1);
}

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
	if (++bit_i == 8)
	{
		if (curr_char == '\0')
			ft_putstr_fd("\n", 1);
		else
			write(1, &curr_char, 1);
		bit_i = 0;
		curr_char = 0;
	}
	else
		curr_char <<= 1;
	if (signal == SIGUSR1 || signal == SIGUSR2)
		kill(info->si_pid, signal);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
