/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:52:46 by saan              #+#    #+#             */
/*   Updated: 2026/01/24 03:46:33 by saan             ###   ########.fr       */
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

static void	draw_wall_column(t_game *g, int x, int top, int bot, int color)
{
	int	y;

	if (top < 0)
		top = 0;
	if (bot >= WIN_H)
		bot = WIN_H - 1;
	y = top;
	while (y <= bot)
	{
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
			delta_dist_x = 1e30; // 왜이렇게 큰값이 들어가지
		else
			delta_dist_x = fabs(1.0 / ray_dx); // sqrt((ray_dx^2 / ray_dy^2) + 1)이 아니지?

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

		int color = 0x00FFAA00;
		if (side == 1)
			color = 0x00CC8800;
		draw_wall_column(g, x, top, bot, color);
		x++;
	}
}
