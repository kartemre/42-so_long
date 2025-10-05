/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step1_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 09:46:59 by ekart             #+#    #+#             */
/*   Updated: 2025/10/05 19:15:04 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static void putstr_fd(const char *s, int fd)
{
	if (!s)
		return;
	while (*s)
		write(fd, s++, 1);
}

static void error_msg(const char *msg)
{
	putstr_fd("Error\n", 2);
	if (msg)
	{
		putstr_fd(msg, 2);
		putstr_fd("\n", 2);
	}
}

static int ends_with_ber(const char *p)
{
	int	i;

	i = 0;
	while (p[i])
		i++;
	if (i < 4)
		return (0);
	return (p[i - 4] == '.' && p[i - 3] == 'b' && p[i - 2] == 'e' && p[i - 1] == 'r' );
}

int main (int argc, char **argv)
{
	if(argc != 2)
	{
		error_msg("Usage: ./so_long <map.ber>");
		return 1;
	}
	const char *path = argv[1];
	if (!ends_with_ber(path))
	{
		error_msg("Map file must have .ber extension");
        	return 1;
	}
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		putstr_fd("Error\ncannot open ", 2);
		putstr_fd(path, 2);
		putstr_fd(": ", 2);
		putstr_fd(strerror(errno), 2);
		putstr_fd("\n", 2);
		return 1;
	}
	putstr_fd("ok. opened map file\n", 1);
	t_map m = {0};
	if (map_load_fd(fd, &m) != 0)
	{
		putstr_fd("Error\n failed to read map\n", 2);
		close(fd);
		return (1);
	}
	close(fd);
	putstr_fd("MAP: rows=", 1);
	{
		char buf[32]; int n = m.rows, k = 31; buf[k--] = '\0';
		if (n==0) buf[k--]='0';
		while (n>0) { buf[k--] = '0' + (n%10); n/=10; }
		putstr_fd(&buf[k+1], 1);
	}
	putstr_fd(" cols=", 1);
	{
		char buf[32]; int n = m.cols, k = 31; buf[k--] = '\0';
		if (n==0) buf[k--]='0';
		while (n>0) { buf[k--] = '0' + (n%10); n/=10; }
		putstr_fd(&buf[k+1], 1);
	}
	putstr_fd("\n", 1);

	if (m.rows > 0) {
		putstr_fd("row0: ", 1);
		putstr_fd("\n", 1);
		putstr_fd(m.grid[0], 1);
		putstr_fd("\n", 1);
		putstr_fd(m.grid[1], 1);
		putstr_fd("\n", 1);
		putstr_fd(m.grid[2], 1);
		putstr_fd("\n", 1);
		putstr_fd(m.grid[3], 1);
		putstr_fd("\n", 1);
	}

	const char *err = NULL;
	t_counts counts = {0};
	if (!validate_rect_charset_counts(&m, &counts, &err))
	{
		putstr_fd("Error\n", 2);
		if (err) {	putstr_fd(err, 2); putstr_fd("\n", 2); }
		map_free(&m);
		return 1;
	}
	putstr_fd("OK: rectangular + charset + counts\n", 1);
	const char *err2 = NULL;
	if (!validate_walls(&m, &err2)) {
		putstr_fd("Error\n", 2);
		if (err2) { putstr_fd(err2, 2); putstr_fd("\n", 2); }
		map_free(&m);
		return 1;
	}
	putstr_fd("OK: surrounded by walls\n", 1);
	const char *err3 = NULL;
	if (!validate_path(&m, counts.c, 1, &err3)) {
		putstr_fd("Error\n", 2);
		if (err3) { putstr_fd(err3, 2); putstr_fd("\n", 2); }
		map_free(&m);
		return 1;
	}
	putstr_fd("OK: valid path (all C & E reachable)\n", 1);
	// --- MLX başlat & çiz ---
	t_game G = {0};
	if (!game_init_and_draw(&G, &m)) {
		putstr_fd("Error\nmlx init/draw failed\n", 2);
		map_free(&m);
		return 1;
	}
	putstr_fd("OK: window opened, press ESC to quit\n", 1);
	game_loop(&G);
	game_destroy(&G);
	map_free(&m);
	return (0);
}
