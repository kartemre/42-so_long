/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:56:20 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 12:56:22 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>

static void	draw_row(t_game *g, int r)
{
	int		c;
	t_img	*t;

	c = 0;
	while (c < g->map->cols)
	{
		t = get_tile_for_char(g, g->map->grid[r][c]);
		put_tile(g, t, c, r);
		c++;
	}
}

void	redraw_all(t_game *g)
{
	int	r;

	r = 0;
	while (r < g->map->rows)
	{
		draw_row(g, r);
		r++;
	}
}

void	game_loop(t_game *g)
{
	mlx_hook(g->win, 2, 1L << 0, on_key, g);
	mlx_hook(g->win, 17, 1L << 17, on_destroy, g);
	mlx_expose_hook(g->win, on_expose, g);
	mlx_loop(g->mlx);
}

void	game_destroy(t_game *g)
{
	if (g->wall.img)
		mlx_destroy_image(g->mlx, g->wall.img);
	if (g->floor.img)
		mlx_destroy_image(g->mlx, g->floor.img);
	if (g->exit.img)
		mlx_destroy_image(g->mlx, g->exit.img);
	if (g->collect.img)
		mlx_destroy_image(g->mlx, g->collect.img);
	if (g->player.img)
		mlx_destroy_image(g->mlx, g->player.img);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}
