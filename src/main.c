/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:56:27 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 12:56:29 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		error_exit("Usage: ./so_long <map.ber>");
		return (0);
	}
	if (!check_ber_extension(argv[1]))
	{
		error_exit("Map file must have .ber extension");
		return (0);
	}
	return (1);
}

static int	open_map_file(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_putstr_fd("Error\n", 2);
	return (fd);
}

static int	load_and_validate_map(int fd, t_map *m, t_counts *counts)
{
	if (map_load_fd(fd, m) != 0)
	{
		error_exit("failed to read map");
		return (0);
	}
	return (validate_all(m, counts));
}

static int	init_and_run_game(t_map *m)
{
	t_game	g;

	g = (t_game){0};
	if (!game_init_and_draw(&g, m))
	{
		error_exit("mlx init/draw failed");
		map_free(m);
		return (0);
	}
	game_loop(&g);
	game_destroy(&g);
	return (1);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_map		m;
	t_counts	counts;

	if (!validate_arguments(argc, argv))
		return (1);
	fd = open_map_file(argv[1]);
	if (fd < 0)
		return (1);
	m = (t_map){0};
	counts = (t_counts){0};
	if (!load_and_validate_map(fd, &m, &counts))
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (!init_and_run_game(&m))
		return (1);
	map_free(&m);
	return (0);
}
