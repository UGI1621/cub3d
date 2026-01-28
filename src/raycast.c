/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:52:46 by saan              #+#    #+#             */
/*   Updated: 2026/01/28 13:39:01 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_game *g, int mx, int my)
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
			return (&g->map.tex_s);
		else
			return (&g->map.tex_n);
	}
}
// draw_wall_column(g, x, top, bot, side, ray_dx, ray_dy, prep_dist);
static void	draw_wall_column(t_game *g, int x, int top, int bot, int side, double ray_dx, double ray_dy, double prep_dist)
{
	t_tex	*tex;
	double	wall_x;
	int		tex_x;
	int		y;

	tex = choose_texture(g, side, ray_dx, ray_dy);

	if (side == 0)
		wall_x = g->pl.y + prep_dist * ray_dy;
	else
		wall_x = g->pl.x + prep_dist * ray_dx;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * tex->w);
	if (side == 0 && ray_dx > 0)
		tex_x = tex->w - tex_x - 1;
	if (side == 1 && ray_dy < 0)
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

void render_3d(t_game *g)
{
	int x;

	x = 0;
	while (x < WIN_W)
	{
		double camera_x = (2.0 * x / (double)WIN_W) - 1.0;

		double ray_dx = g->pl.dir_x + g->pl.plane_x * camera_x;
		double ray_dy = g->pl.dir_y + g->pl.plane_y * camera_x;

		int map_x = (int)g->pl.x;
		int map_y = (int)g->pl.y;

		double delta_dist_x;
		if (ray_dx == 0.0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1.0 / ray_dx);

		double delta_dist_y;
		if (ray_dy == 0.0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1.0 / ray_dy);

		double side_dist_x;
		double side_dist_y;
		int step_x;
		int step_y;
		int side;

		if (ray_dx < 0)
		{
			step_x = -1;
			side_dist_x = (g->pl.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - g->pl.x) * delta_dist_x;
		}

		if (ray_dy < 0)
		{
			step_y = -1;
			side_dist_y = (g->pl.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - g->pl.y) * delta_dist_y;
		}

		while (!is_wall(g, map_x, map_y))
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
		}

		double prep_dist;
		if (side == 0)
			prep_dist = side_dist_x - delta_dist_x;
		else
			prep_dist = side_dist_y - delta_dist_y;

		if (prep_dist < 0.0001)
			prep_dist = 0.0001;

		int line_h = (int)(WIN_H / prep_dist);
		int top = WIN_H / 2 - line_h / 2;
		int bot = WIN_H / 2 + line_h / 2;

		draw_wall_column(g, x, top, bot, side, ray_dx, ray_dy, prep_dist);
		x++;
	}
}
