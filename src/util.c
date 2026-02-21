/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:59:59 by saan              #+#    #+#             */
/*   Updated: 2026/02/21 18:16:25 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_only_space(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (!(*str))
		return (1);
	return (0);
}

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

int	handle_sig(int sig, t_game *g)
{
	if (sig == 1)
	{
		free_2ptr(g->map.copy_grid);
		return (error_msg("Error :: grid : not surrounded map"));
	}
	else if (sig == 2)
		return (error_msg("Error :: copy_grid : fail malloc"));
	else
		free_2ptr(g->map.copy_grid);
	return(1);
}
