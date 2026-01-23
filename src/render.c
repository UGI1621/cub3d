/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:02:17 by saan              #+#    #+#             */
/*   Updated: 2026/01/24 02:53:02 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *g, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = g->frame.addr + (y * g->frame.line_len + x * (g->frame.bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
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

int game_loop(t_game *g)
{
	clear_frame(g, 0x00C8C8C8, 0x00505050);
	render_3d(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	return (0);
}
