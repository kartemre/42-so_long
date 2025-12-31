/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:55:43 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 18:11:59 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	try_exit(t_game *g)
{
	g->moves++;
	ft_putstr_fd("moves: ", 1);
	ft_putnbr_fd(g->moves, 1);
	ft_putstr_fd("\n", 1);
	mlx_loop_end(g->mlx);
	return (0);
}

static void	collect_item(t_game *g, int nr, int nc)
{
	g->remaining_c--;
	g->map->grid[nr][nc] = '0';
}

static void	move_player(t_game *g, int nr, int nc)
{
	g->map->grid[g->pr][g->pc] = '0';
	g->pr = nr;
	g->pc = nc;
	g->map->grid[g->pr][g->pc] = 'P';
	g->moves++;
	ft_putstr_fd("moves: ", 1);
	ft_putnbr_fd(g->moves, 1);
	ft_putstr_fd("\n", 1);
	redraw_all(g);
}

static void	apply_move(t_game *g, int dr, int dc)
{
	int		nr;
	int		nc;
	char	target;

	nr = g->pr + dr;
	nc = g->pc + dc;
	target = g->map->grid[nr][nc];
	if (target == '1')
		return ;
	if (target == 'E' && g->remaining_c == 0)
	{
		try_exit(g);
		return ;
	}
	if (target == 'E' && g->remaining_c > 0)
		return ;
	if (target == 'C')
		collect_item(g, nr, nc);
	move_player(g, nr, nc);
}

int	on_key(int keycode, t_game *g)
{
	if (keycode == 65307)
	{
		mlx_loop_end(g->mlx);
		return (0);
	}
	if (keycode == 'w' || keycode == 'W' || keycode == 65362)
		apply_move(g, -1, 0);
	else if (keycode == 's' || keycode == 'S' || keycode == 65364)
		apply_move(g, 1, 0);
	else if (keycode == 'a' || keycode == 'A' || keycode == 65361)
		apply_move(g, 0, -1);
	else if (keycode == 'd' || keycode == 'D' || keycode == 65363)
		apply_move(g, 0, 1);
	return (0);
}
