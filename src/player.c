/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:58:59 by saan              #+#    #+#             */
/*   Updated: 2026/01/28 19:17:20 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_player(char **grid, int w, int h)
{
	if (grid[h][w] == 'N' || grid[h][w] == 'S' || grid[h][w] == 'E' || grid[h][w] == 'W')
		return (1);
	return (0);
}

void set_player_dir(t_game *g, char dir)
{
	if (dir == 'N')
	{
		g->pl.dir_x = 0;
		g->pl.dir_y = -1;
	}
	if (dir == 'S')
	{
		g->pl.dir_x = 0;
		g->pl.dir_y = 1;
	}
	if (dir == 'W')
	{
		g->pl.dir_x = -1;
		g->pl.dir_y = 0;
	}
	if (dir == 'E')
	{
		g->pl.dir_x = 1;
		g->pl.dir_y = 0;
	}
}

void update_player_data(t_game *g, int w, int h, char dir)
{
	g->pl.x = w + 0.5;
	g->pl.y = h + 0.5;
	set_player_dir(g, dir);
	if (dir == 'N')
	{
		g->pl.plane_x = 1;
		g->pl.plane_y = 0;
	}
	if (dir == 'S')
	{
		g->pl.plane_x = -1;
		g->pl.plane_y = 0;
	}
	if (dir == 'W')
	{
		g->pl.plane_x = 0;
		g->pl.plane_y = -1;
	}
	if (dir == 'E')
	{
		g->pl.plane_x = 0;
		g->pl.plane_y = 1;
	}
}
