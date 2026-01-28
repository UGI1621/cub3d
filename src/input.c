/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:33:24 by saan              #+#    #+#             */
/*   Updated: 2026/01/28 14:28:17 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move(t_game *g, double nx, double ny)
{
	int	mx;
	int	my;

	mx = (int)nx;
	my = (int)ny;
	if (mx < 0 || my < 0 || mx >= g->map.w || my >= g->map.h)
		return (0);
	if (g->map.grid[my][mx] == '1')
		return (0);
	return (1);
}

static void apply_movement(t_game *g)
{
	double move = 0.06;
	double rot = 0.04;
	double nx;
	double ny;

	if (g->keys.left || g->keys.right)
	{
		double angle = (g->keys.left ? rot : -rot);
		double old_dir_x = g->pl.dir_x;
		double old_plane_x = g->pl.plane_x;

		g->pl.dir_x = g->pl.dir_x * cos(angle) - g->pl.dir_y * sin(angle);
		g->pl.dir_y = old_dir_x * sin(angle) + g->pl.dir_y * cos(angle);

		g->pl.plane_x = g->pl.plane_x * cos(angle) - g->pl.plane_y * sin(angle);
		g->pl.plane_y = old_plane_x * sin(angle) + g->pl.plane_y * cos(angle);
	}

	if (g->keys.w)
	{
		nx = g->pl.x + g->pl.dir_x * move;
		ny = g->pl.y + g->pl.dir_y * move;
		if (can_move(g, nx, ny))
		{
			g->pl.x = nx;
			g->pl.y = ny;
		}
	}

	if (g->keys.s)
	{
		nx = g->pl.x - g->pl.dir_x * move;
		ny = g->pl.y - g->pl.dir_y * move;
		if (can_move(g, nx, ny))
		{
			g->pl.x = nx;
			g->pl.y = ny;
		}
	}

	if (g->keys.a)
	{
		nx = g->pl.x - g->pl.plane_x * move;
		ny = g->pl.y - g->pl.plane_y * move;
		if (can_move(g, nx, ny))
		{
			g->pl.x = nx;
			g->pl.y = ny;
		}
	}

	if (g->keys.d)
	{
		nx = g->pl.x + g->pl.plane_x * move;
		ny = g->pl.y + g->pl.plane_y * move;
		if (can_move(g, nx, ny))
		{
			g->pl.x = nx;
			g->pl.y = ny;
		}
	}

}

int on_key_press(int key, t_game *g)
{
	if (key == KEY_ESC)
		cleanup_and_exit(g, 0);
	if (key == KEY_W)
		g->keys.w = 1;
	if (key == KEY_A)
		g->keys.a = 1;
	if (key == KEY_S)
		g->keys.s = 1;
	if (key == KEY_D)
		g->keys.d = 1;
	if (key == KEY_LEFT)
		g->keys.left = 1;
	if (key == KEY_RIGHT)
		g->keys.right = 1;
	apply_movement(g);
	return (0);
}

int	on_key_release(int key, t_game *g)
{
	if (key == KEY_W)
		g->keys.w = 0;
	if (key == KEY_A)
		g->keys.a = 0;
	if (key == KEY_S)
		g->keys.s = 0;
	if (key == KEY_D)
		g->keys.d = 0;
	if (key == KEY_LEFT)
		g->keys.left = 0;
	if (key == KEY_RIGHT)
		g->keys.right = 0;
	return (0);
}

int	on_close(t_game *g)
{
	cleanup_and_exit(g, 0);
	return (0);
}
