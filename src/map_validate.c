/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:56:56 by ekart             #+#    #+#             */
/*   Updated: 2026/01/11 19:06:17 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_chars_and_count(const t_map *m, t_counts *cnt,
		const char **err)
{
	int	r;
	int	c;

	r = 0;
	while (r < m->rows)
	{
		c = 0;
		while (m->grid[r][c])
		{
			if (!is_valid_char(m->grid[r][c]))
			{
				if (err)
					*err = "Wrong characters";
				return (0);
			}
			count_char(m->grid[r][c], cnt);
			c++;
		}
		r++;
	}
	return (1);
}

static int	validate_exit_player(const t_counts *cnt, const char **err_msg)
{
	if (cnt->e == 0)
	{
		if (err_msg)
			*err_msg = "No exit";
		return (0);
	}
	if (cnt->e > 1)
	{
		if (err_msg)
			*err_msg = "Duplicate exit";
		return (0);
	}
	if (cnt->p == 0)
	{
		if (err_msg)
			*err_msg = "No player";
		return (0);
	}
	if (cnt->p > 1)
	{
		if (err_msg)
			*err_msg = "Duplicate player";
		return (0);
	}
	return (1);
}

static int	validate_counts(const t_counts *cnt, const char **err_msg)
{
	if (!validate_exit_player(cnt, err_msg))
		return (0);
	if (cnt->c < 1)
	{
		if (err_msg)
			*err_msg = "No object";
		return (0);
	}
	return (1);
}

int	validate_rect_charset_counts(const t_map *m, t_counts *out,
		const char **err_msg)
{
	t_counts	cnt;

	cnt.c = 0;
	cnt.e = 0;
	cnt.p = 0;
	if (!check_rectangle(m, err_msg))
		return (0);
	if (!check_chars_and_count(m, &cnt, err_msg))
		return (0);
	if (!validate_counts(&cnt, err_msg))
		return (0);
	if (out)
		*out = cnt;
	return (1);
}

int	validate_all(t_map *m, t_counts *counts)
{
	const char	*err;

	err = NULL;
	if (!validate_rect_charset_counts(m, counts, &err))
	{
		map_free(m);
		error_exit(err);
		return (0);
	}
	if (!validate_walls(m, &err))
	{
		map_free(m);
		error_exit(err);
		return (0);
	}
	if (!validate_path(m, counts->c, 1, &err))
	{
		map_free(m);
		error_exit(err);
		return (0);
	}
	return (1);
}
