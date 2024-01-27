/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:16:26 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/27 12:40:00 by mmouhiid         ###   ########.fr       */
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

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (*(str + i) == ' ' || *(str + i) == '\t' || *(str + i) == '\n'
		|| *(str + i) == '\v' || *(str + i) == '\f' || *(str + i) == '\r')
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
	{
		res = res * 10 + (*(str + i) - '0');
		i++;
	}
	return (res * sign);
}

void	send_char(pid_t server_pid, unsigned char c)
{
	int						i;
	unsigned char			curr_bit;
	int						signal;

	i = 7;
	while (i >= 0)
	{
		curr_bit = (c >> i--) % 2;
		if (curr_bit == 0)
			signal = SIGUSR2;
		else
			signal = SIGUSR1;
		usleep(600);
		if (kill(server_pid, signal) == -1)
		{
			ft_putstr_fd("Usage: ./client <pid> <msg>\n", 2);
			exit(1);
		}
	}
}

int	main(int argc, char **argv)
{
	char		*msg;
	pid_t		server_pid;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <pid> <msg>\n", 2);
		exit(1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0 || !valid_pid(argv[1]) || kill(server_pid, 0) == -1)
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
