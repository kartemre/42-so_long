/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:57:03 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 12:57:05 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_row_walls(const char *row, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (row[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	check_side_walls(const t_map *m)
{
	int	r;

	r = 1;
	while (r < m->rows - 1)
	{
		if (m->grid[r][0] != '1' || m->grid[r][m->cols - 1] != '1')
			return (0);
		r++;
	}
	return (1);
}

int	validate_walls(const t_map *m, const char **err_msg)
{
	if (!m || m->rows <= 0 || m->cols <= 0)
	{
		if (err_msg)
			*err_msg = "Not surrounded by walls";
		return (0);
	}
	if (!check_row_walls(m->grid[0], m->cols))
	{
		if (err_msg)
			*err_msg = "Not surrounded by walls";
		return (0);
	}
	if (!check_row_walls(m->grid[m->rows - 1], m->cols))
	{
		if (err_msg)
			*err_msg = "Not surrounded by walls";
		return (0);
	}
	if (!check_side_walls(m))
	{
		if (err_msg)
			*err_msg = "Not surrounded by walls";
		return (0);
	}
	return (1);
}
