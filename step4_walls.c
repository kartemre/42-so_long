/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step4_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:39:59 by ekart             #+#    #+#             */
/*   Updated: 2025/09/19 22:58:51 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_map {
    char **grid;
    int   rows;
    int   cols;
} t_map;

static int is_all_ones(const char *row, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (row[i] != '1')
			return 0;
		i++;
	}
	return (1);
}

int validate_walls(const t_map *m, const char **err_msg)
{
	int r;

	if (!m || m->rows <= 0 || m->cols <= 0)
	{
		if (err_msg) 
			*err_msg = "empty or invalid map dimensions";
        	return 0;
	}
	if (!is_all_ones(m->grid[0], m->cols) || !is_all_ones(m->grid[m->rows - 1], m->cols))
	{
		if (err_msg)
			*err_msg = "map borders must be walls (top/bottom)";
		return 0;
	}
	r = 1;
	while (r < m->rows - 1)
	{
        	if (m->grid[r][0] != '1' || m->grid[r][m->cols - 1] != '1') 
		{
		        if (err_msg) *err_msg = "map borders must be walls (sides)";
        		return 0;
		}
		r++;
	}
	return 1;
}
