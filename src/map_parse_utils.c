/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:56:33 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 18:13:02 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_malloc(size_t n)
{
	void	*p;

	p = malloc(n);
	if (!p)
		_exit(12);
	return (p);
}

int	count_lines(const char *buf, size_t len)
{
	int		r;
	size_t	i;

	i = 0;
	r = 0;
	while (i < len)
	{
		if (buf[i] == '\n')
			r++;
		i++;
	}
	if (len > 0 && buf[len - 1] != '\n')
		r++;
	return (r);
}

char	*copy_line(const char *buf, size_t start, size_t end)
{
	size_t	len;
	char	*row;

	len = end - start;
	row = (char *)ft_malloc(len + 1);
	if (len)
		memcpy(row, buf + start, len);
	row[len] = '\0';
	return (row);
}

void	map_free(t_map *m)
{
	int	r;

	r = 0;
	if (!m || !m->grid)
		return ;
	while (r < m->rows)
	{
		free(m->grid[r]);
		r++;
	}
	free(m->grid);
	m->grid = NULL;
}
