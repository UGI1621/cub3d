/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 10:38:04 by saan              #+#    #+#             */
/*   Updated: 2026/03/06 10:40:49 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rc(t_game *g)
{
	g->rc.map_x = 0;
	g->rc.map_y = 0;
	g->rc.ray_dx = 0;
	g->rc.ray_dy = 0;
	g->rc.delta_dist_x = 0;
	g->rc.delta_dist_y = 0;
	g->rc.prep_dist = 0;
	g->rc.step_x = 0;
	g->rc.step_y = 0;
	g->rc.side = 0;
}
