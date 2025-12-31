/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:57:16 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 12:57:17 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

static void	dfs(t_dfs_ctx ctx, t_pt p, t_reach *r)
{
	char	ch;

	if (p.r < 0 || p.r >= ctx.rows || p.c < 0 || p.c >= ctx.cols)
		return ;
	ch = ctx.g[p.r][p.c];
	if (ch == '1' || ch == 'V')
		return ;
	if (ch == 'C')
		r->rc++;
	if (ch == 'E')
		r->re++;
	ctx.g[p.r][p.c] = 'V';
	dfs(ctx, (t_pt){p.r + 1, p.c}, r);
	dfs(ctx, (t_pt){p.r - 1, p.c}, r);
	dfs(ctx, (t_pt){p.r, p.c + 1}, r);
	dfs(ctx, (t_pt){p.r, p.c - 1}, r);
}

static int	check_all_reachable(const t_map *m, int need_c, int need_e)
{
	char		**cpy;
	int			pr;
	int			pc;
	t_reach		reach;
	t_dfs_ctx	ctx;

	if (!find_player(m, &pr, &pc))
		return (0);
	cpy = dup_grid(m->grid, m->rows, m->cols);
	if (!cpy)
		return (0);
	reach.rc = 0;
	reach.re = 0;
	ctx = (t_dfs_ctx){cpy, m->rows, m->cols};
	dfs(ctx, (t_pt){pr, pc}, &reach);
	free_grid(cpy, m->rows);
	if (reach.rc < need_c || reach.re < need_e)
		return (0);
	return (1);
}

static int	validate_basic_map(const t_map *m, const char **err)
{
	if (!m || m->rows <= 0 || m->cols <= 0)
	{
		if (err)
			*err = "empty or invalid map dimensions";
		return (0);
	}
	return (1);
}

int	validate_path(const t_map *m, int need_c, int need_e, const char **err)
{
	if (!validate_basic_map(m, err))
		return (0);
	if (!check_all_reachable(m, need_c, need_e))
	{
		if (err)
			*err = "not all collectibles are reachable";
		return (0);
	}
	return (1);
}
