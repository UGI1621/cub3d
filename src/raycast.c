/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:52:46 by saan              #+#    #+#             */
/*   Updated: 2026/02/28 01:15:49 by saan             ###   ########.fr       */
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

static t_tex	*choose_texture(t_game *g, int side, double ray_dx,
		double ray_dy)
{
	if (side == 0)
	{
		if (ray_dx > 0)
			return (&g->map.tex_w);
		else
			return (&g->map.tex_e);
	}
	else
	{
		if (ray_dy > 0)
			return (&g->map.tex_s);
		else
			return (&g->map.tex_n);
	}
}

static int	cal_tex_x_val(t_tex *tex, t_game *g, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * tex->w);
	if (g->rc.side == 0 && g->rc.ray_dx < 0)
		tex_x = tex->w - tex_x - 1;
	if (g->rc.side == 1 && g->rc.ray_dy > 0)
		tex_x = tex->w - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_column(t_game *g, int x, int top, int bot)
{
	t_tex	*tex;
	int		tex_x;
	int		y;
	int		tex_y;
	int		color;

	tex = choose_texture(g, g->rc.side, g->rc.ray_dx, g->rc.ray_dy);
	tex_x = cal_tex_x_val(tex, g, cal_wall_x_val(g));
	y = top;
	while (y <= bot)
	{
		tex_y = (((((y << 8) - (WIN_H << 7) + ((bot - top) << 7)) * tex->h)
					/ (bot - top)) >> 8);
		color = *(int *)(tex->addr + (tex_y * tex->line_len) + (tex_x
					* (tex->bpp / 8)));
		put_pixel(g, x, y, color);
		y++;
	}
}

void	render_3d(t_game *g)
{
	int	x;
	int	line_h;
	int	top;
	int	bot;

	x = 0;
	while (x < WIN_W)
	{
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
