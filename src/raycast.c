/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:52:46 by saan              #+#    #+#             */
/*   Updated: 2026/01/28 19:09:08 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *g, int mx, int my)
{
	if (mx < 0 || my < 0 || mx >= g->map.w || my >= g->map.h)
		return (1);
	if (g->map.grid[my][mx] == '1')
		return (1);
	return (0);
}

static t_tex *choose_texture(t_game *g, int side, double ray_dx, double ray_dy)
{
	if (side == 0)
	{
		if (ray_dx > 0)
			return (&g->map.tex_e);
		else
			return (&g->map.tex_w);
	}
	else
	{
		if (ray_dy > 0)
			return (&g->map.tex_n);
		else
			return (&g->map.tex_s);
	}
}

static void	draw_wall_column(t_game *g, int x, int top, int bot)
{
	t_tex	*tex;
	double	wall_x;
	int		tex_x;
	int		y;

	tex = choose_texture(g, g->rc.side, g->rc.ray_dx, g->rc.ray_dy);

	if (g->rc.side == 0)
		wall_x = g->pl.y + g->rc.prep_dist * g->rc.ray_dy;
	else
		wall_x = g->pl.x + g->rc.prep_dist * g->rc.ray_dx;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * tex->w);
	if (g->rc.side == 0 && g->rc.ray_dx < 0)
		tex_x = tex->w - tex_x - 1;
	if (g->rc.side == 1 && g->rc.ray_dy > 0)
		tex_x = tex->w - tex_x - 1;

	y = top;
	while (y <= bot)
	{
		int d = y * 256 - WIN_H * 128 + (bot - top) * 128;
		int tex_y = ((d * tex->h) / (bot - top)) / 256;
		int color = *(int *)(tex->addr
			+ tex_y * tex->line_len
			+ tex_x * (tex->bpp / 8));

		put_pixel(g, x, y, color);
		y++;
	}
}

// static void	draw_wall_column(t_game *g, int x, int top, int bot)
// {
// 	t_tex	*tex;
// 	double	wall_x;
// 	int		tex_x;
// 	int		y;
// 	int		height;

// 	/* --- 1. 높이 방어 (division by zero + 즉사 방지) --- */
// 	height = bot - top;
// 	if (height <= 0)
// 		return;

// 	/* --- 2. 화면 클램핑 (이미지 범위 보호) --- */
// 	if (top < 0)
// 		top = 0;
// 	if (bot >= WIN_H)
// 		bot = WIN_H - 1;

// 	tex = choose_texture(g, g->rc.side, g->rc.ray_dx, g->rc.ray_dy);

// 	/* --- 3. wall_x 계산 --- */
// 	if (g->rc.side == 0)
// 		wall_x = g->pl.y + g->rc.prep_dist * g->rc.ray_dy;
// 	else
// 		wall_x = g->pl.x + g->rc.prep_dist * g->rc.ray_dx;
// 	wall_x -= floor(wall_x);

// 	/* --- 4. tex_x 계산 + 클램핑 --- */
// 	tex_x = (int)(wall_x * tex->w);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= tex->w)
// 		tex_x = tex->w - 1;

// 	if (g->rc.side == 0 && g->rc.ray_dx < 0)
// 		tex_x = tex->w - tex_x - 1;
// 	if (g->rc.side == 1 && g->rc.ray_dy > 0)
// 		tex_x = tex->w - tex_x - 1;

// 	/* --- 5. draw loop --- */
// 	y = top;
// 	while (y <= bot)
// 	{
// 		int d = y * 256 - WIN_H * 128 + height * 128;
// 		int tex_y = ((d * tex->h) / height) / 256;

// 		/* --- 6. tex_y 클램핑 (색 깨짐 + segfault 방지) --- */
// 		if (tex_y < 0)
// 			tex_y = 0;
// 		if (tex_y >= tex->h)
// 			tex_y = tex->h - 1;

// 		int color = *(int *)(tex->addr
// 			+ tex_y * tex->line_len
// 			+ tex_x * (tex->bpp / 8));

// 		put_pixel(g, x, y, color);
// 		y++;
// 	}
// }



void render_3d(t_game *g)
{
	int x;

	x = 0;
	while (x < WIN_W)
	{
		int line_h;
		int top;
		int bot;

		calculate_rc(g, x);
		if (g->rc.prep_dist < 0.0001)
			g->rc.prep_dist = 0.0001;
		line_h = (int)(WIN_H / g->rc.prep_dist);
		top = WIN_H / 2 - line_h / 2;
		bot = WIN_H / 2 + line_h / 2;
		draw_wall_column(g, x, top, bot);
		x++;
	}
}
