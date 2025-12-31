/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:55:54 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 12:55:56 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>

int	on_destroy(t_game *g)
{
	mlx_loop_end(g->mlx);
	return (0);
}

int	on_expose(t_game *g)
{
	redraw_all(g);
	return (0);
}
