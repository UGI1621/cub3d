/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:58:01 by saan              #+#    #+#             */
/*   Updated: 2026/01/29 19:31:23 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_keys(t_game *g)
{
	g->keys.w = 0;
	g->keys.a = 0;
	g->keys.s = 0;
	g->keys.d = 0;
	g->keys.left = 0;
	g->keys.right = 0;
}

static void	init_player_info(t_game *g)
{
	g->pl.x = 0;
	g->pl.y = 0;
	g->pl.dir_x = 0;
	g->pl.dir_y = 0;
	g->pl.plane_x = 0;
	g->pl.plane_y = 0;
}

static void	init_map_info(t_game *g)
{
	g->map.tex_n.ptr = NULL;
	g->map.tex_s.ptr = NULL;
	g->map.tex_w.ptr = NULL;
	g->map.tex_e.ptr = NULL;
	g->map.c = 0;
	g->map.f = 0;
	g->map.grid_fd = -1;
	g->map.grid = NULL;
	g->map.copy_grid = NULL;
}

int	init_game(t_game *g)
{
	g->mlx = NULL;
	g->win = NULL;
	g->frame.img = NULL;
	g->map.grid = NULL;
	init_map_info(g);
	init_player_info(g);
	init_keys(g);
	g->mlx = mlx_init();
	if (!g->mlx)
		return (1);
	g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, "cub3D");
	if (!g->win)
		return (1);
	g->frame.img = mlx_new_image(g->mlx, WIN_W, WIN_H);
	if (!g->frame.img)
		return (1);
	g->frame.addr = mlx_get_data_addr(g->frame.img, &g->frame.bpp,
			&g->frame.line_len, &g->frame.endian);
	return (0);
}
