/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step5_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:30:59 by ekart             #+#    #+#             */
/*   Updated: 2025/10/05 13:01:37 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// step5_path.c — flood-fill ile geçerli yol kontrolü
#include <stdlib.h>

typedef struct s_map {
    char **grid;
    int   rows;
    int   cols;
} t_map;

typedef struct s_pt { int r, c; } t_pt;

static int rowlen(const char *s) { int n=0; while(s && s[n]) n++; return n; }

static char **dup_grid(char **g, int rows, int cols) {
    char **cpy = (char**)malloc(sizeof(char*) * rows);
    if (!cpy) return NULL;
    for (int r=0; r<rows; r++) {
        cpy[r] = (char*)malloc(cols + 1);
        if (!cpy[r]) return NULL;
        for (int c=0; c<cols; c++) cpy[r][c] = g[r][c];
        cpy[r][cols] = '\0';
    }
    return cpy;
}

static void free_grid(char **g, int rows) {
    if (!g) return;
    for (int r=0; r<rows; r++) free(g[r]);
    free(g);
}

static int find_player(const t_map *m, t_pt *pout) {
    for (int r=0; r<m->rows; r++) {
        for (int c=0; c<m->cols; c++) {
            if (m->grid[r][c] == 'P') { pout->r = r; pout->c = c; return 1; }
        }
    }
    return 0;
}

// basit DFS; duvar ('1') ve daha önce ziyaret edilen ('V') yerlere girme
static void dfs(char **g, int rows, int cols, int r, int c, int *reach_c, int *reach_e) {
    if (r<0 || r>=rows || c<0 || c>=cols) return;
    char ch = g[r][c];
    if (ch=='1' || ch=='V') return;
    if (ch=='C') (*reach_c)++;
    if (ch=='E') (*reach_e)++;
    g[r][c] = 'V';
    dfs(g, rows, cols, r+1, c, reach_c, reach_e);
    dfs(g, rows, cols, r-1, c, reach_c, reach_e);
    dfs(g, rows, cols, r, c+1, reach_c, reach_e);
    dfs(g, rows, cols, r, c-1, reach_c, reach_e);
}

int validate_path(const t_map *m, int need_c, int need_e, const char **err_msg) {
    if (!m || m->rows <= 0 || m->cols <= 0) { if (err_msg) *err_msg="empty or invalid map dimensions"; return 0; }
    // satır uzunlukları güvence için
    for (int r=0; r<m->rows; r++) if (rowlen(m->grid[r]) != m->cols) { if (err_msg) *err_msg="map is not rectangular"; return 0; }

    t_pt p;
    if (!find_player(m, &p)) { if (err_msg) *err_msg="no player found"; return 0; }

    char **cpy = dup_grid(m->grid, m->rows, m->cols);
    if (!cpy) { if (err_msg) *err_msg="memory error"; return 0; }

    int rc = 0, re = 0;
    dfs(cpy, m->rows, m->cols, p.r, p.c, &rc, &re);
    free_grid(cpy, m->rows);

    if (rc < need_c) { if (err_msg) *err_msg="not all collectibles are reachable"; return 0; }
    if (re < need_e) { if (err_msg) *err_msg="exit is not reachable"; return 0; }
    return 1;
}
