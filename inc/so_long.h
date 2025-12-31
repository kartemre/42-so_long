/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:57:39 by ekart             #+#    #+#             */
/*   Updated: 2025/12/31 18:12:51 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define TILE 64

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_counts
{
	int	c;
	int	e;
	int	p;
}	t_counts;

typedef struct s_pt
{
	int	r;
	int	c;
}	t_pt;

typedef struct s_reach
{
	int	rc;
	int	re;
}	t_reach;

typedef struct s_dfs_ctx
{
	char	**g;
	int		rows;
	int		cols;
}	t_dfs_ctx;

typedef struct s_parse
{
	char	**grid;
	int		r;
	int		first_len;
}	t_parse;

typedef struct s_read
{
	size_t	cap;
	size_t	len;
	char	*buf;
	ssize_t	n;
}	t_read;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	wall;
	t_img	floor;
	t_img	exit;
	t_img	collect;
	t_img	player;
	int		pr;
	int		pc;
	int		moves;
	int		remaining_c;
}	t_game;

int		map_load_fd(int fd, t_map *out);
void	map_free(t_map *m);
void	*ft_malloc(size_t n);
int		count_lines(const char *buf, size_t len);
char	*copy_line(const char *buf, size_t start, size_t end);

int		check_rectangle(const t_map *m, const char **err_msg);
int		is_valid_char(char c);
void	count_char(char c, t_counts *cnt);

int		validate_rect_charset_counts(const t_map *m, t_counts *out,
			const char **err_msg);
int		validate_all(t_map *m, t_counts *counts);
int		validate_walls(const t_map *m, const char **err_msg);

char	**dup_grid(char **grid, int rows, int cols);
void	free_grid(char **g, int rows);
int		find_player(const t_map *m, int *pr, int *pc);

int		validate_path(const t_map *m, int need_c, int need_e,
			const char **err);

int		game_init_and_draw(t_game *g, t_map *m);
void	game_loop(t_game *g);
void	game_destroy(t_game *g);
void	redraw_all(t_game *g);
void	put_tile(t_game *g, t_img *tile, int col, int row);
t_img	*get_tile_for_char(t_game *g, char ch);

int		on_key(int keycode, t_game *g);
int		on_destroy(t_game *g);
int		on_expose(t_game *g);

void	ft_putstr_fd(const char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	error_exit(const char *msg);
int		check_ber_extension(const char *path);

#endif
