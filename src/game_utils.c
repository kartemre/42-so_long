/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:56:12 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 18:12:14 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_tile(t_game *g, t_img *tile, int col, int row)
{
	mlx_put_image_to_window(g->mlx, g->win, tile->img,
		col * TILE, row * TILE);
}

t_img	*get_tile_for_char(t_game *g, char ch)
{
	if (ch == '1')
		return (&g->wall);
	else if (ch == 'E')
		return (&g->exit);
	else if (ch == 'C')
		return (&g->collect);
	else if (ch == 'P')
		return (&g->player);
	return (&g->floor);
}
