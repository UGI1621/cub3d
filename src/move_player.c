/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:17:46 by saan              #+#    #+#             */
/*   Updated: 2026/03/09 16:44:54 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_x(t_game *g, double dx)
{
	double	r;

	if (dx > 0)
		r = 0.2;
	else
		r = -0.2;
	if (!is_wall(g, g->pl.x + dx + r, g->pl.y + r) && \
		!is_wall(g, g->pl.x + dx + r, g->pl.y - r))
		g->pl.x += dx;
}

void	move_player_y(t_game *g, double dy)
{
	double	r;

	if (dy > 0)
		r = 0.2;
	else
		r = -0.2;
	if (!is_wall(g, g->pl.x + r, g->pl.y + dy + r) && \
		!is_wall(g, g->pl.x - r, g->pl.y + dy + r))
		g->pl.y += dy;
}
