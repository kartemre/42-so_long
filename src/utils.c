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

void	error_exit(const char *msg)
{
	write(1, "Error\n", 6);
	if (msg)
	{
		write(1, msg, ft_strlen(msg));
		write(1, "\n", 1);
	}
	exit(1);
}

int	check_ber_extension(const char *path)
{
	int	i;
	int	last_slash;

	i = 0;
	last_slash = -1;
	while (path[i])
	{
		if (path[i] == '/')
			last_slash = i;
		i++;
	}
	if (i < 5)
		return (0);
	if (last_slash >= 0 && last_slash == i - 5)
		return (0);
	if (path[i - 4] == '.' && path[i - 3] == 'b'
		&& path[i - 2] == 'e' && path[i - 1] == 'r'
		&& (last_slash < 0 || path[last_slash + 1] != '.'))
		return (1);
	return (0);
}
