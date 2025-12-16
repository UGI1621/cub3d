#include "cub3d.h"

static void	init_keys(t_game *g)
{
	g->keys.w = 0;
	g->keys.a = 0;
	g->keys.s = 0;
	g->keys.d = 0;
	g->keys.left = 0;
	g->keys.right = 0;
}

int	init_game(t_game *g)
{
	g->mlx = NULL;
	g->win = NULL;
	g->frame.img = NULL;
	g->map.grid = NULL;
	init_keys(g);
	if (load_demo_map(g) != 0)
		return (1);
	g->mlx = mlx_init();
	if (!g->mlx)
		return (1);
	g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, "cub3D proto");
	if (!g->win)
		return (1);
	g->frame.img = mlx_new_image(g->mlx, WIN_W, WIN_H);
	if (!g->frame.img)
		return (1);
	g->frame.addr = mlx_get_data_addr(g->frame.img, &g->frame.bpp,
			&g->frame.line_len, &g->frame.endian);
	return (0);
}
