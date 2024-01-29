/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:14:35 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/29 18:30:28 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_atoi(char *str);
void	exit_handler(void);
void	ft_putstr_fd(char *s, int fd);
int		bytes_count(unsigned char c);

#endif
