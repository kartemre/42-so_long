/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:57:10 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 18:13:19 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**dup_grid(char **grid, int rows, int cols)
{
	char	**cpy;
	int		r;

	cpy = (char **)malloc(sizeof(char *) * rows);
	if (!cpy)
		return (NULL);
	r = 0;
	while (r < rows)
	{
		cpy[r] = (char *)malloc(cols + 1);
		if (!cpy[r])
		{
			while (r > 0)
				free(cpy[--r]);
			free(cpy);
			return (NULL);
		}
		memcpy(cpy[r], grid[r], cols);
		cpy[r][cols] = '\0';
		r++;
	}
	return (cpy);
}

void	free_grid(char **g, int rows)
{
	int	i;

	if (!g)
		return ;
	i = 0;
	while (i < rows)
		free(g[i++]);
	free(g);
}

int	find_player(const t_map *m, int *pr, int *pc)
{
	int	r;
	int	c;

	r = 0;
	while (r < m->rows)
	{
		c = 0;
		while (c < (int)ft_strlen(m->grid[r]))
		{
			if (m->grid[r][c] == 'P')
			{
				*pr = r;
				*pc = c;
				return (1);
			}
			c++;
		}
		r++;
	}
	return (0);
}
