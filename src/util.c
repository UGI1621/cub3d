/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:59:59 by saan              #+#    #+#             */
/*   Updated: 2026/02/06 18:02:40 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	cal_wall_x_val(t_game *g)
{
	double	wall_x;

	if (g->rc.side == 0)
		wall_x = g->pl.y + g->rc.prep_dist * g->rc.ray_dy;
	else
		wall_x = g->pl.x + g->rc.prep_dist * g->rc.ray_dx;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	two_ptr_len(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void	gnl_drain(int fd)
{
	char *line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		free(line);
	}
}
