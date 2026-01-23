/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:34:27 by saan              #+#    #+#             */
/*   Updated: 2026/01/24 01:37:21 by saan             ###   ########.fr       */
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
	if (g->mlx && g->frame.img)
		mlx_destroy_image(g->mlx, g->frame.img);
	if (g->mlx && g->win)
		mlx_destroy_window(g->mlx, g->win);
	exit(code);
}
