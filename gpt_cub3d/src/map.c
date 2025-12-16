#include "cub3d.h"

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

int	load_demo_map(t_game *g)
{
	int		i;
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
	g->pl.dir = -M_PI / 2.0;
	return (0);
}
