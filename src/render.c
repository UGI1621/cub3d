/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:02:17 by saan              #+#    #+#             */
/*   Updated: 2026/02/27 23:47:10 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *g, int x, int y, int color)
{
	unsigned int	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = (unsigned int *)g->frame.addr;
	dst[y * (g->frame.line_len / 4) + x] = color;
}

void	clear_frame(t_game *g, int ceil_c, int floor_c)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
				put_pixel(g, x, y, ceil_c);
			else
				put_pixel(g, x, y, floor_c);
			x++;
		}
		y++;
	}
}

int	game_loop(t_game *g)
{
	double ct;
	double dt;
	double ft;

	ct = get_time();
	dt = ct - g->lt;
	g->lt = ct;
	if (dt > 0.1)
		dt = 0.1;
	apply_movement(g, dt);
	clear_frame(g, g->map.c, g->map.f);
	render_3d(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	ft = get_time() - ct;
	if (ft < FRAME_TIME)
		usleep((FRAME_TIME - ft) * 1000000);
	return (0);
}
