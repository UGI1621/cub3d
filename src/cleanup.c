/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:34:27 by saan              #+#    #+#             */
/*   Updated: 2026/01/28 12:20:39 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void free_map(t_game *g)
{
	int i;

	if (!g->map.grid)
		return ;
	i = 0;
	while (g->map.grid[i])
	{
		free(g->map.grid[i]);
		i++;
	}
	free(g->map.grid);
	g->map.grid = NULL;
}

void cleanup_and_exit(t_game *g, int code)
{
	free_map(g);
	if (g->mlx && g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx && g->map.texture_s)
		mlx_destroy_image(g->mlx, g->map.texture_s);
	if (g->mlx && g->map.texture_n)
		mlx_destroy_image(g->mlx, g->map.texture_n);
	if (g->mlx && g->map.texture_e)
		mlx_destroy_image(g->mlx, g->map.texture_e);
	if (g->mlx && g->map.texture_w)
		mlx_destroy_image(g->mlx, g->map.texture_w);
	if (g->mlx && g->frame.img)
		mlx_destroy_image(g->mlx, g->frame.img);
	if (g->mlx)
		mlx_destroy_display(g->mlx);
	free(g->mlx);
	unlink("map_grid.txt");
	exit(code);
}

void	free_grid(char **grid)
{
	int i;

	i = -1;
	while (grid[++i])
		free(grid[i]);
	free(grid);
	grid = NULL;
}
