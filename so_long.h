/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 09:47:27 by ekart             #+#    #+#             */
/*   Updated: 2025/10/05 20:31:15 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

// --- temel tipler ---
typedef struct s_map {
    char **grid;
    int   rows;
    int   cols;
} t_map;

typedef struct s_counts { int c, e, p; } t_counts;

#define TILE 64

typedef struct s_img {
    void *img;
    char *addr;
    int   bpp;
    int   line_len;
    int   endian;
} t_img;

typedef struct s_game {
    void *mlx;
    void *win;
    t_map *map;
    t_img wall, floor, exit, collect, player;
    int pr, pc;          // player row/col
    int moves;           // hamle sayısı
    int remaining_c;     // kalan C
} t_game;

// --- API prototipleri ---
int  map_load_fd(int fd, t_map *out);
void map_free(t_map *m);

int  validate_rect_charset_counts(const t_map *m, t_counts *out, const char **err_msg);
int  validate_walls(const t_map *m, const char **err_msg);
int  validate_path(const t_map *m, int need_c, int need_e, const char **err_msg);

int  game_init_and_draw(t_game *g, t_map *m);
void game_loop(t_game *g);
void game_destroy(t_game *g);


#endif