/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 17:47:14 by saan              #+#    #+#             */
/*   Updated: 2026/02/22 19:57:30 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_pl_surround(char **grid, int w, int h)
{
	if (grid[h][w + 1] != '0' && grid[h][w + 1] != '1')
		return (0);
	if (grid[h][w - 1] != '0' && grid[h][w - 1] != '1')
		return (0);
	if (grid[h + 1][w] != '0' && grid[h + 1][w] != '1')
		return (0);
	if (grid[h - 1][w] != '0' && grid[h - 1][w] != '1')
		return (0);
	return (1);
}
static void	find_user_position(char **grid, int *w, int *h, int *u)
{
	while (grid[*h])
	{
		while (grid[*h][*w])
		{
			if (is_player(grid, *w, *h))
			{
				(*u)++;
				return ;
			}
			(*w)++;
		}
		(*w) = 0;
		(*h)++;
	}
}

int	valid_user_position(char **grid)
{
	int w;
	int h;
	int u;

	w = 0;
	h = 0;
	u = 0;
	find_user_position(grid, &w, &h, &u);
	if (!u)
		return (error_msg("Error :: no user here"));
	if(!is_pl_surround(grid, w, h))
		return (error_msg("Error :: invalid user position"));
	return (0);
}
