/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:33:24 by saan              #+#    #+#             */
/*   Updated: 2026/01/24 01:49:46 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int on_key_press(int key, t_game *g)
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
	printf("input key\n");
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
