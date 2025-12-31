/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:56:49 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 12:56:51 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	while (s && s[n])
		n++;
	return (n);
}

int	check_rectangle(const t_map *m, const char **err_msg)
{
	int	r;

	if (!m || m->rows <= 0 || m->cols <= 0)
	{
		if (err_msg)
			*err_msg = "No rectangular";
		return (0);
	}
	r = 0;
	while (r < m->rows)
	{
		if (ft_strlen(m->grid[r]) != m->cols)
		{
			if (err_msg)
				*err_msg = "No rectangular";
			return (0);
		}
		r++;
	}
	return (1);
}

int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P')
		return (1);
	return (0);
}

void	count_char(char c, t_counts *cnt)
{
	if (c == 'C')
		cnt->c++;
	else if (c == 'E')
		cnt->e++;
	else if (c == 'P')
		cnt->p++;
}
