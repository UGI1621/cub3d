/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:33:24 by saan              #+#    #+#             */
/*   Updated: 2026/02/25 17:40:21 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	can_move(t_game *g, double nx, double ny)
{
	int	mx;
	int	my;

	mx = (int)nx;
	my = (int)ny;
	if (mx < 0 || my < 0 || mx > g->map.w || my > g->map.h)
		return (0);
	if (g->map.grid[my][mx] == '1')
		return (0);
	return (1);
}

static void	apply_movement(t_game *g)
{
	if (g->keys.left || g->keys.right)
		move_left_right(g, 0.04);
	if (g->keys.w)
		move_w(g, 0.06);
	if (g->keys.s)
		move_s(g, 0.06);
	if (g->keys.a)
		move_a(g, 0.06);
	if (g->keys.d)
		move_d(g, 0.06);
}

int	on_key_press(int key, t_game *g)
{
	if (key == KEY_ESC)
		cleanup_and_exit(g, 0);
	if (key == KEY_W)
		g->keys.w = 1;
	if (key == KEY_A)
		g->keys.a = 1;
	if (key == KEY_S)
		g->keys.s = 1;
	if (key == KEY_D)
		g->keys.d = 1;
	if (key == KEY_LEFT)
		g->keys.left = 1;
	if (key == KEY_RIGHT)
		g->keys.right = 1;
	apply_movement(g);
	return (0);
}

int	on_key_release(int key, t_game *g)
{
	if (key == KEY_W)
		g->keys.w = 0;
	if (key == KEY_A)
		g->keys.a = 0;
	if (key == KEY_S)
		g->keys.s = 0;
	if (key == KEY_D)
		g->keys.d = 0;
	if (key == KEY_LEFT)
		g->keys.left = 0;
	if (key == KEY_RIGHT)
		g->keys.right = 0;
	return (0);
}

int	on_close(t_game *g)
{
	cleanup_and_exit(g, 0);
	return (0);
}
