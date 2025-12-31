/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:56:04 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 12:56:06 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>

static t_img	make_solid_tile(void *mlx, int color)
{
	t_img	i;
	int		y;
	int		x;

	i.img = mlx_new_image(mlx, TILE, TILE);
	i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.line_len, &i.endian);
	y = 0;
	while (y < TILE)
	{
		x = 0;
		while (x < TILE)
		{
			*(int *)(i.addr + y * i.line_len + x * (i.bpp / 8)) = color;
			x++;
		}
		y++;
	}
	return (i);
}

static t_img	load_xpm_tile(void *mlx, const char *path, int fallback)
{
	t_img	i;
	int		w;
	int		h;

	w = 0;
	h = 0;
	i.img = mlx_xpm_file_to_image(mlx, (char *)path, &w, &h);
	if (!i.img)
		return (make_solid_tile(mlx, fallback));
	i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.line_len, &i.endian);
	return (i);
}

static void	load_textures(t_game *g)
{
	g->wall = load_xpm_tile(g->mlx, "textures/wall.xpm", 0x00333333);
	g->floor = load_xpm_tile(g->mlx, "textures/floor.xpm", 0x00000000);
	g->exit = load_xpm_tile(g->mlx, "textures/exit.xpm", 0x00FF8800);
	g->collect = load_xpm_tile(g->mlx, "textures/collect.xpm", 0x00FFFF00);
	g->player = load_xpm_tile(g->mlx, "textures/player.xpm", 0x0000FF00);
}

static void	init_game_state(t_game *g)
{
	int	r;
	int	c;

	g->remaining_c = 0;
	g->pr = -1;
	g->pc = -1;
	r = 0;
	while (r < g->map->rows)
	{
		c = 0;
		while (c < g->map->cols)
		{
			if (g->map->grid[r][c] == 'P')
			{
				g->pr = r;
				g->pc = c;
			}
			else if (g->map->grid[r][c] == 'C')
				g->remaining_c++;
			c++;
		}
		r++;
	}
	g->moves = 0;
}

int	game_init_and_draw(t_game *g, t_map *m)
{
	int	win_w;
	int	win_h;

	g->map = m;
	g->mlx = mlx_init();
	if (!g->mlx)
		return (0);
	win_w = m->cols * TILE;
	win_h = m->rows * TILE;
	g->win = mlx_new_window(g->mlx, win_w, win_h, "so_long");
	if (!g->win)
		return (0);
	load_textures(g);
	init_game_state(g);
	redraw_all(g);
	return (1);
}
