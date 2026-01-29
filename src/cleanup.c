/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:34:27 by saan              #+#    #+#             */
/*   Updated: 2026/01/29 19:30:57 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_game *g)
{
	int	i;

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

void	cleanup_and_exit(t_game *g, int code)
{
	free_map(g);
	if (g->mlx && g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx && g->map.tex_s.ptr)
		mlx_destroy_image(g->mlx, g->map.tex_s.ptr);
	if (g->mlx && g->map.tex_n.ptr)
		mlx_destroy_image(g->mlx, g->map.tex_n.ptr);
	if (g->mlx && g->map.tex_e.ptr)
		mlx_destroy_image(g->mlx, g->map.tex_e.ptr);
	if (g->mlx && g->map.tex_w.ptr)
		mlx_destroy_image(g->mlx, g->map.tex_w.ptr);
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
	int	i;

	i = -1;
	while (grid[++i])
		free(grid[i]);
	free(grid);
	grid = NULL;
}
