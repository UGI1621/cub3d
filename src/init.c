/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:58:01 by saan              #+#    #+#             */
/*   Updated: 2026/01/24 03:20:50 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_keys(t_game *g)
{
	g->keys.w = 0;
	g->keys.a = 0;
	g->keys.s = 0;
	g->keys.d = 0;
	g->keys.left = 0;
	g->keys.right = 0;
}

static char	*dup_line(const char *s)
{
	int		i;
	char	*res;

	i = 0;
	while (s[i])
		i++;
	res = (char *)malloc(i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int load_demo_map(t_game *g)
{
	int i;
	char	*tmp[10];

	tmp[0] = "111111111111";
	tmp[1] = "100000000001";
	tmp[2] = "101111111101";
	tmp[3] = "100100000001";
	tmp[4] = "101101111101";
	tmp[5] = "100001000001";
	tmp[6] = "111101011101";
	tmp[7] = "1000000E0001";
	tmp[8] = "111111111111";
	tmp[9] = NULL;

	g->map.h = 9;
	g->map.w = 12;

	g->map.grid = (char **)malloc(sizeof(char *) * (g->map.h + 1));
	if (!g->map.grid)
		return (1);

	i = 0;
	while (i < g->map.h)
	{
		g->map.grid[i] = dup_line(tmp[i]);
		if (!g->map.grid[i])
			return (1);
		i++;
	}
	g->map.grid[i] = NULL;

	g->pl.x = 7.5;
	g->pl.y = 7.5;
	g->pl.dir_x = 1;
	g->pl.dir_y = 0;
	g->pl.plane_x = 0;
	g->pl.plane_y = -1;
	return (0);
}

int	init_game(t_game *g)
{
	g->mlx = NULL;
	g->win = NULL;
	g->frame.img = NULL;
	g->map.grid = NULL;
	init_keys(g);
	if (load_demo_map(g) != 0)
		return (0);
	g->mlx = mlx_init();
	if (!g->mlx)
		return (1);
	g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, "cub3D");
	if (!g->win)
		return (1);
	g->frame.img = mlx_new_image(g->mlx, WIN_W, WIN_H);
	if (!g->frame.img)
		return (1);
	g->frame.addr = mlx_get_data_addr(g->frame.img, &g->frame.bpp, &g->frame.line_len, &g->frame.endian);
	return (0);
}
