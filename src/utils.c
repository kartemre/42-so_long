/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:57:24 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 17:59:12 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>

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
	(void)msg;
	ft_putstr_fd("Error\n", 2);
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
