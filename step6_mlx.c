/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step6_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekart <ekart@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:20:03 by ekart             #+#    #+#             */
/*   Updated: 2025/10/05 18:11:07 by ekart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// step6_mlx.c — pencere + tek renk karelerle çizim + ESC/close
#include "so_long.h"
#include <mlx.h>    // MinilibX
#include <unistd.h> 

static void put_tile(t_game *g, t_img *tile, int col, int row)
{
    mlx_put_image_to_window(g->mlx, g->win, tile->img, col * TILE, row * TILE);
}

static void putstr_fd(const char *s, int fd)
{ if(!s) return; while(*s) write(fd, s++, 1); }

static void putnbr_fd(int n, int fd)
{
    char buf[32]; int k=31; buf[k--]='\0';
    if(n==0){ buf[k--]='0'; }
    int sign = (n<0); if(sign) n = -n;
    while(n>0){ buf[k--] = '0' + (n%10); n/=10; }
    if(sign) buf[k--]='-';
    putstr_fd(&buf[k+1], fd);
}

static void redraw_all(t_game *g)
{
    for (int r=0; r<g->map->rows; r++){
        for (int c=0; c<g->map->cols; c++){
            char ch = g->map->grid[r][c];
            t_img *t = &g->floor;
            if (ch=='1') t=&g->wall;
            else if (ch=='E') t=&g->exit;
            else if (ch=='C') t=&g->collect;
            else if (ch=='P') t=&g->player;
            put_tile(g, t, c, r);
        }
    }
}

static void apply_move(t_game *g, int dr, int dc)
{
    int nr = g->pr + dr, nc = g->pc + dc;
    char target = g->map->grid[nr][nc];
    if (target=='1') return;                // duvar -> hareket yok

    // E'ye basma: ancak tüm C toplandıysa bitir
    if (target=='E' && g->remaining_c==0){
        g->moves++;
        putstr_fd("moves: ",1); putnbr_fd(g->moves,1); putstr_fd("\n",1);
        // oyuncuyu E'nin üstünde göstermeye gerek yok; doğrudan bitir
        mlx_loop_end(g->mlx);
        return;
    }
    if (target=='E' && g->remaining_c>0) {
        return; // daha C var -> E'ye giremez
    }

    // C toplama
    if (target=='C'){
        g->remaining_c--;
        g->map->grid[nr][nc] = '0'; // hücreyi boşalt (oyuncuyu ayrı basacağız)
    }

    // Oyuncu taşınsın: eski P'yi 0 yap, yeniyi P yap
    g->map->grid[g->pr][g->pc] = '0';
    g->pr = nr; g->pc = nc;
    g->map->grid[g->pr][g->pc] = 'P';

    g->moves++;
    putstr_fd("moves: ",1); putnbr_fd(g->moves,1); putstr_fd("\n",1); // subject gereği shell’e yaz

    redraw_all(g);
}
/* --- helpers --- */
static t_img make_solid_tile(void *mlx, int color)
{
    t_img i;
    i.img = mlx_new_image(mlx, TILE, TILE);
    i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.line_len, &i.endian);
    for (int y=0; y<TILE; y++) {
        for (int x=0; x<TILE; x++) {
            // 32bpp varsayıyoruz: ARGB veya endian'a göre BGRA olabilir, pratikte çalışır.
            *(int *)(i.addr + y * i.line_len + x * (i.bpp/8)) = color;
        }
    }
    return i;
}



/* --- public API --- */
int  game_init_and_draw(t_game *g, t_map *m)
{
    g->map = m;
    g->mlx = mlx_init();
    if (!g->mlx) return 0;

    int win_w = m->cols * TILE;
    int win_h = m->rows * TILE;
    g->win = mlx_new_window(g->mlx, win_w, win_h, "so_long");
    if (!g->win) return 0;

    // Tek renkli tile’ları hazırla (BGRx gibi düşünülebilir; test et)
    g->wall    = make_solid_tile(g->mlx, 0x00333333); // koyu gri
    g->floor   = make_solid_tile(g->mlx, 0x00000000); // siyah
    g->exit    = make_solid_tile(g->mlx, 0x00FF8800); // turuncu
    g->collect = make_solid_tile(g->mlx, 0x00FFFF00); // sarı
    g->player  = make_solid_tile(g->mlx, 0x0000FF00); // yeşil

    g->remaining_c = 0;
    g->pr = g->pc = -1;
    for (int r=0; r<m->rows; r++){
        for (int c=0; c<m->cols; c++){
            if (m->grid[r][c]=='P'){ g->pr=r; g->pc=c; }
            else if (m->grid[r][c]=='C'){ g->remaining_c++; }
        }
    }
    g->moves = 0;
    
    redraw_all(g);
    
    // Haritayı çiz
    /*
    for (int r=0; r<m->rows; r++) {
        for (int c=0; c<m->cols; c++) {
            char ch = m->grid[r][c];
            t_img *t = &g->floor;
            if (ch=='1') t = &g->wall;
            else if (ch=='E') t = &g->exit;
            else if (ch=='C') t = &g->collect;
            else if (ch=='P') t = &g->player;
            put_tile(g, t, c, r);
        }
    }
        */
    return 1;
}

static int on_key(int keycode, t_game *g)
{
    // Linux oklar: 65361← 65362↑ 65363→ 65364↓ ; ESC: 65307
    if (keycode == 65307) { mlx_loop_end(g->mlx); return 0; }

    if (keycode=='w' || keycode=='W' || keycode==65362) { apply_move(g, -1,  0); }
    else if (keycode=='s' || keycode=='S' || keycode==65364) { apply_move(g,  1,  0); }
    else if (keycode=='a' || keycode=='A' || keycode==65361) { apply_move(g,  0, -1); }
    else if (keycode=='d' || keycode=='D' || keycode==65363) { apply_move(g,  0,  1); }
    return 0;
}

static int on_destroy(t_game *g)
{
    mlx_loop_end(g->mlx);
    return 0;
}

static int on_expose(t_game *g)
{
    // pencere yeniden görünür olduğunda baştan çiz
    redraw_all(g);
    return 0;
}

void game_loop(t_game *g)
{
    // ESC ve pencere çarpısı
    mlx_hook(g->win, 2, 1L<<0, (int (*)(void))on_key, g);       // KeyPress
    mlx_hook(g->win, 17, 1L<<17, (int (*)(void))on_destroy, g); // DestroyNotify
    mlx_expose_hook(g->win, (int (*)(void*))on_expose, g);       // ← expose
    mlx_loop(g->mlx);
}

void game_destroy(t_game *g)
{
    // sırayla image’ları ve pencereyi kapat
    if (g->wall.img)    mlx_destroy_image(g->mlx, g->wall.img);
    if (g->floor.img)   mlx_destroy_image(g->mlx, g->floor.img);
    if (g->exit.img)    mlx_destroy_image(g->mlx, g->exit.img);
    if (g->collect.img) mlx_destroy_image(g->mlx, g->collect.img);
    if (g->player.img)  mlx_destroy_image(g->mlx, g->player.img);
    if (g->win)         mlx_destroy_window(g->mlx, g->win);
    // bazı mlx sürümlerinde display/free gerekebilir (Linux):
#ifdef __linux__
    if (g->mlx)         mlx_destroy_display(g->mlx);
#endif
    // mlx pointer’ı genelde free edilmez; kampüs kurulumuna göre değişebilir
}

