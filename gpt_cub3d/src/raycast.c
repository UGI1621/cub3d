#include "cub3d.h"

static int	is_wall(t_game *g, int mx, int my)
{
	if (mx < 0 || my < 0 || mx >= g->map.w || my >= g->map.h)
		return (1);
	if (g->map.grid[my][mx] == '1')
		return (1);
	return (0);
}

static void	draw_wall_column(t_game *g, int x, int top, int bot, int color)
{
	int	y;

	if (top < 0)
		top = 0;
	if (bot >= WIN_H)
		bot = WIN_H - 1;
	y = top;
	while (y <= bot)
	{
		put_pixel(g, x, y, color);
		y++;
	}
}

void	render_3d(t_game *g)
{
	int		x;
	double	fov;
	double	ray_ang;

	fov = M_PI / 3.0;
	x = 0;
	while (x < WIN_W)
	{
		double	camera_x = (2.0 * x / (double)WIN_W) - 1.0;
		ray_ang = g->pl.dir + atan(camera_x * tan(fov / 2.0));
		double	ray_dx = cos(ray_ang);
		double	ray_dy = sin(ray_ang);

		int		map_x = (int)g->pl.x;
		int		map_y = (int)g->pl.y;

		double	side_dist_x;
		double	side_dist_y;
		double	delta_x = (ray_dx == 0.0) ? 1e30 : fabs(1.0 / ray_dx);
		double	delta_y = (ray_dy == 0.0) ? 1e30 : fabs(1.0 / ray_dy);

		int		step_x;
		int		step_y;
		int		side;

		if (ray_dx < 0.0)
		{
			step_x = -1;
			side_dist_x = (g->pl.x - map_x) * delta_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - g->pl.x) * delta_x;
		}
		if (ray_dy < 0.0)
		{
			step_y = -1;
			side_dist_y = (g->pl.y - map_y) * delta_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - g->pl.y) * delta_y;
		}

		side = 0;
		while (!is_wall(g, map_x, map_y))
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_y;
				map_y += step_y;
				side = 1;
			}
		}

		double	perp_dist;
		if (side == 0)
			perp_dist = (side_dist_x - delta_x);
		else
			perp_dist = (side_dist_y - delta_y);
		if (perp_dist < 0.0001)
			perp_dist = 0.0001;

		int	line_h = (int)(WIN_H / perp_dist);
		int	top = (WIN_H / 2) - (line_h / 2);
		int	bot = (WIN_H / 2) + (line_h / 2);

		int	color = 0x00FFAA00;
		if (side == 1)
			color = 0x00CC8800;
		draw_wall_column(g, x, top, bot, color);
		x++;
	}
}
