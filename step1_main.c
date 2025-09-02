/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step1_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarr <ekartk@student.42istanbul.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 09:46:59 by ekart             #+#    #+#             */
/*   Updated: 2025/09/02 18:36:30 by ekarr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static void putstr_fd(const char *s, int fd)
{
	if (!s)
		return;
	while (*s)
		write(fd, s++, 1);
}

static void error_msg(const char *msg)
{
	putstr_fd("Error\n", 2);
	if (msg)
	{
		putstr_fd(msg, 2);
		putstr_fd("\n", 2);
	}
}

static int ends_with_ber(const char *p)
{
	int	i;

	i = 0;
	while (p[i])
		i++;
	if (i < 4)
		return (0);
	return (p[i - 4] == '.' && p[i - 3] == 'b' && p[i - 2] == 'e' && p[i - 1] == 'r' );
}

int main (int argc, char **argv)
{
	if(argc != 2)
	{
		error_msg("Usage: ./so_long <map.ber>");
		return 1;
	}
	const char *path = argv[1];
	if (!ends_with_ber(path))
	{
		error_msg("Map file must have .ber extension");
        	return 1;
	}
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		putstr_fd("Error\ncannot open ", 2);
		putstr_fd(path, 2);
		putstr_fd(": ", 2);
		putstr_fd(strerror(errno), 2);
		putstr_fd("\n", 2);
		return 1;
	}
	putstr_fd("ok. opened map file", 1);
	close(fd);
	return (0);
}
