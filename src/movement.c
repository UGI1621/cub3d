/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:10:53 by saan              #+#    #+#             */
/*   Updated: 2026/01/29 19:32:00 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_left_right(t_game *g, double rot)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	angle = rot;
	if (g->keys.left)
		angle = -rot;
	old_dir_x = g->pl.dir_x;
	old_plane_x = g->pl.plane_x;
	g->pl.dir_x = g->pl.dir_x * cos(angle) - g->pl.dir_y * sin(angle);
	g->pl.dir_y = old_dir_x * sin(angle) + g->pl.dir_y * cos(angle);
	g->pl.plane_x = g->pl.plane_x * cos(angle) - g->pl.plane_y * sin(angle);
	g->pl.plane_y = old_plane_x * sin(angle) + g->pl.plane_y * cos(angle);
}

void	move_w(t_game *g, double move)
{
	double	nx;
	double	ny;

	nx = g->pl.x + g->pl.dir_x * move;
	ny = g->pl.y + g->pl.dir_y * move;
	if (can_move(g, nx, ny))
	{
		g->pl.x = nx;
		g->pl.y = ny;
	}
}

void	move_s(t_game *g, double move)
{
	double	nx;
	double	ny;

	nx = g->pl.x - g->pl.dir_x * move;
	ny = g->pl.y - g->pl.dir_y * move;
	if (can_move(g, nx, ny))
	{
		g->pl.x = nx;
		g->pl.y = ny;
	}
}

void	move_a(t_game *g, double move)
{
	double	nx;
	double	ny;

	nx = g->pl.x - g->pl.plane_x * move;
	ny = g->pl.y - g->pl.plane_y * move;
	if (can_move(g, nx, ny))
	{
		g->pl.x = nx;
		g->pl.y = ny;
	}
}

void	move_d(t_game *g, double move)
{
	double	nx;
	double	ny;

	nx = g->pl.x + g->pl.plane_x * move;
	ny = g->pl.y + g->pl.plane_y * move;
	if (can_move(g, nx, ny))
	{
		g->pl.x = nx;
		g->pl.y = ny;
	}
}
