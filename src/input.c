/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:33:24 by saan              #+#    #+#             */
/*   Updated: 2026/02/27 21:54:50 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	can_move(t_game *g, double nx, double ny)
// {
// 	int	mx;
// 	int	my;
// 	int	sig;

// 	sig = 0;
// 	mx = (int)nx;
// 	my = (int)ny;
// 	if (mx < 0 || my < 0 || mx > g->map.w || my > g->map.h)
// 		return (0);
// 	// if (g->map.grid[my][mx] == '1')
// 	// 	return (0);
// 	if (g->map.grid[(int)g->pl.y][mx] == '1')
// 		return (0);
// 	if (g->map.grid[my][(int)g->pl.x] == '1')
// 		return (0);
// 	return (1);
// }

int	can_move(t_game *g, double nx, double ny)
{
	double	r = 0.2;

	if (nx + r >= g->map.w || nx - r < 0
		|| ny + r >= g->map.h || ny - r < 0)
		return (0);

	if (g->map.grid[(int)ny][(int)(nx + r)] == '1')
		return (0);
	if (g->map.grid[(int)ny][(int)(nx - r)] == '1')
		return (0);
	if (g->map.grid[(int)(ny + r)][(int)nx] == '1')
		return (0);
	if (g->map.grid[(int)(ny - r)][(int)nx] == '1')
		return (0);

	return (1);
}

void	apply_movement(t_game *g, double dt)
{
	double m;
	double r;

	m = 3.0 * dt;
	r = 2.0 *dt;
	if (g->keys.left || g->keys.right)
		move_left_right(g, r);
	if (g->keys.w)
		move_w(g, m);
	if (g->keys.s)
		move_s(g, m);
	if (g->keys.a)
		move_a(g, m);
	if (g->keys.d)
		move_d(g, m);
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
	// apply_movement(g);
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
