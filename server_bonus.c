/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:19:40 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/29 18:36:31 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

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

void	print_char_uni(unsigned char c, pid_t pid)
{
	int						i;
	static int				a;
	static int				b;
	static pid_t			prev_pid;
	static unsigned char	bytes[4];

	if (prev_pid != pid)
	{
		a = 0;
		b = 0;
		prev_pid = pid;
	}
	if (a == 0)
		a = bytes_count(c);
	bytes[b] = c;
	b++;
	if (b == a)
	{
		i = 0;
		while (i < b)
			write(1, &bytes[i++], 1);
		a = 0;
		b = 0;
	}
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
			kill(info->si_pid, SIGUSR1);
		else
			print_char_uni(curr_char, c_pid);
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
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
