/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:10:53 by saan              #+#    #+#             */
/*   Updated: 2026/02/27 22:45:34 by saan             ###   ########.fr       */
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

void	move_player_x(t_game *g, double dx)
{
	double	r;

	if (dx > 0)
		r = 0.2;
	else
		r = -0.2;

	if (!is_wall(g, g->pl.x + dx + r, g->pl.y))
		g->pl.x += dx;
}

void	move_player_y(t_game *g, double dy)
{
	double	r;

	if (dy > 0)
		r = 0.2;
	else
		r = -0.2;

	if (!is_wall(g, g->pl.x, g->pl.y + dy + r))
		g->pl.y += dy;
}

void	move_w(t_game *g, double move)
{
	double	dx;
	double	dy;

	dx = g->pl.dir_x * move;
	dy = g->pl.dir_y * move;

	move_player_x(g, dx);
	move_player_y(g, dy);
}

void	move_d(t_game *g, double move)
{
	double	dx;
	double	dy;

	dx = -g->pl.dir_y * move;
	dy = g->pl.dir_x * move;

	move_player_x(g, dx);
	move_player_y(g, dy);
}

void	move_s(t_game *g, double move)
{
	double	dx;
	double	dy;

	dx = -g->pl.dir_x * move;
	dy = -g->pl.dir_y * move;

	move_player_x(g, dx);
	move_player_y(g, dy);
}

void	move_a(t_game *g, double move)
{
	double	dx;
	double	dy;

	dx = g->pl.dir_y * move;
	dy = -g->pl.dir_x * move;

	move_player_x(g, dx);
	move_player_y(g, dy);
}
