#include "cub3d.h"

int	main(void)
{
	t_game	g;

	if (init_game(&g) != 0)
		return (1);
	mlx_hook(g.win, 2, 1L << 0, on_key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, on_key_release, &g);
	mlx_hook(g.win, 17, 0, on_close, &g);
	mlx_loop_hook(g.mlx, game_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}
