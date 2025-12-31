/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:57:24 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 18:11:13 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putstr_fd(const char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buf[32];
	int		k;
	int		sign;

	k = 31;
	buf[k--] = '\0';
	if (n == 0)
		buf[k--] = '0';
	sign = (n < 0);
	if (sign)
		n = -n;
	while (n > 0)
	{
		buf[k--] = '0' + (n % 10);
		n /= 10;
	}
	if (sign)
		buf[k--] = '-';
	ft_putstr_fd(&buf[k + 1], fd);
}

void	error_exit(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(1);
}

int	check_ber_extension(const char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i < 4)
		return (0);
	if (path[i - 4] == '.' && path[i - 3] == 'b'
		&& path[i - 2] == 'e' && path[i - 1] == 'r')
		return (1);
	return (0);
}
