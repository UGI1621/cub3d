/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:15:20 by saan              #+#    #+#             */
/*   Updated: 2026/01/24 09:43:50 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	t_game	g;

	if (!valid_args(ac, av))
		return (1);
	init_game(&g);
	mlx_hook(g.win, 2, 1L << 0, on_key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, on_key_release, &g);
	mlx_hook(g.win, 17, 0, on_close, &g);
	mlx_loop_hook(g.mlx, game_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}
