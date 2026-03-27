/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:21:52 by saan              #+#    #+#             */
/*   Updated: 2026/03/27 19:31:09 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_ray(t_game *g, int x)
{
	double	camera_x;

	camera_x = (2.0 * x / (double)WIN_W) - 1.0;
	g->rc.ray_dx = g->pl.dir_x + g->pl.plane_x * camera_x;
	g->rc.ray_dy = g->pl.dir_y + g->pl.plane_y * camera_x;
}

void	calc_delta_dists(t_game *g)
{
	if (g->rc.ray_dx == 0.0)
		g->rc.delta_dist_x = 1e30;
	else
		g->rc.delta_dist_x = fabs(1.0 / g->rc.ray_dx);
	if (g->rc.ray_dy == 0.0)
		g->rc.delta_dist_y = 1e30;
	else
		g->rc.delta_dist_y = fabs(1.0 / g->rc.ray_dy);
}

void	calc_step_side_dist(t_game *g)
{
	if (g->rc.ray_dx < 0)
	{
		g->rc.step_x = -1;
		g->rc.side_dist_x = (g->pl.x - g->rc.map_x) * g->rc.delta_dist_x;
	}
	else
	{
		g->rc.step_x = 1;
		g->rc.side_dist_x = (g->rc.map_x + 1.0 - g->pl.x) * g->rc.delta_dist_x;
	}
	if (g->rc.ray_dy < 0)
	{
		g->rc.step_y = -1;
		g->rc.side_dist_y = (g->pl.y - g->rc.map_y) * g->rc.delta_dist_y;
	}
	else
	{
		g->rc.step_y = 1;
		g->rc.side_dist_y = (g->rc.map_y + 1.0 - g->pl.y) * g->rc.delta_dist_y;
	}
}

void	calc_append_delta_dist(t_game *g)
{
	while (!is_wall(g, g->rc.map_x, g->rc.map_y))
	{
		if (g->rc.side_dist_x < g->rc.side_dist_y)
		{
			g->rc.side_dist_x += g->rc.delta_dist_x;
			g->rc.map_x += g->rc.step_x;
			g->rc.side = 0;
		}
		else
		{
			g->rc.side_dist_y += g->rc.delta_dist_y;
			g->rc.map_y += g->rc.step_y;
			g->rc.side = 1;
		}
	}
	if (g->rc.side == 0)
		g->rc.prep_dist = (g->rc.map_x - g->pl.x + (1 - g->rc.step_x) / 2)
			/ g->rc.ray_dx;
	else
		g->rc.prep_dist = (g->rc.map_y - g->pl.y + (1 - g->rc.step_y) / 2)
			/ g->rc.ray_dy;
}

void	calculate_rc(t_game *g, int x)
{
	calc_ray(g, x);
	g->rc.map_x = (int)g->pl.x;
	g->rc.map_y = (int)g->pl.y;
	calc_delta_dists(g);
	calc_step_side_dist(g);
	calc_append_delta_dist(g);
}
