/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:13:44 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/29 18:29:00 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

int	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
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

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (*(s + i))
		write(fd, (s + i++), 1);
}

int	bytes_count(unsigned char c)
{
	if (c >= 240)
		return (4);
	else if (c >= 224 && c < 240)
		return (3);
	else if (c >= 192 && c < 224)
		return (2);
	else
		return (1);
}

void	exit_handler(void)
{
	ft_putstr_fd("Usage: ./client <pid> <msg>\n", 2);
	exit(1);
}
