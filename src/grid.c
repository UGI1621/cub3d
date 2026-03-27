/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 08:42:38 by saan              #+#    #+#             */
/*   Updated: 2026/03/27 19:31:50 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	copy_map_to_grid(t_game *g, char *str, int i)
{
	int	j;

	g->map.grid[i] = (char *)ft_calloc(g->map.w + 2, sizeof(char));
	if (!g->map.grid[i])
		return (error_msg("Error :: grid : malloc error"));
	g->map.grid[i][0] = 'X';
	j = 1;
	while (j < g->map.w + 1)
	{
		if (j >= (int)ft_strlen(str) || ft_isspace(str[j - 1]))
			g->map.grid[i][j] = 'X';
		else
			g->map.grid[i][j] = str[j - 1];
		j++;
	}
	return (0);
}

char	**copy_grid(char **grid)
{
	char	**res;
	int		h;
	int		i;

	h = 0;
	while (grid[h])
		h++;
	res = (char **)ft_calloc(h + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < h)
		res[i] = ft_strdup(grid[i]);
	res[i] = NULL;
	return (res);
}

void	dfs(t_game *g, int w, int h, int *sig)
{
	if (w < 0 || h < 0 || w > g->map.w + 1 || h > g->map.h + 1)
		return ;
	if (!g->map.copy_grid[h][w] || g->map.copy_grid[h][w] == '1'
		|| g->map.copy_grid[h][w] == 'B')
		return ;
	if (g->map.copy_grid[h][w] == 'X')
	{
		*sig = 1;
		return ;
	}
	g->map.copy_grid[h][w] = 'B';
	dfs(g, w + 1, h, sig);
	dfs(g, w - 1, h, sig);
	dfs(g, w, h + 1, sig);
	dfs(g, w, h - 1, sig);
}

static int	validation_grid(t_game *g)
{
	int	w;
	int	h;
	int	sig;

	sig = 0;
	w = 0;
	h = 0;
	g->map.copy_grid = copy_grid(g->map.grid);
	if (!g->map.copy_grid)
		return (2);
	if (valid_user_position(g, g->map.copy_grid))
		return (3);
	while (g->map.copy_grid[h])
	{
		while (g->map.copy_grid[h][w] && g->map.copy_grid[h][w] != '0')
			w++;
		dfs(g, w, h, &sig);
		if (sig)
			return (sig);
		if (!(w < g->map.w + 1))
			h++;
		w = 0;
	}
	free_2ptr(g->map.copy_grid);
	return (0);
}

int	fill_grid(t_game *g)
{
	char	*line;
	int		i;
	int		sig;

	i = 1;
	g->map.grid_fd = open("map_grid.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(g->map.grid_fd);
		if (!line)
			break ;
		if (copy_map_to_grid(g, line, i))
			return (1);
		free(line);
		i++;
	}
	close(g->map.grid_fd);
	sig = validation_grid(g);
	if (sig)
		return (handle_sig(sig, g));
	return (0);
}
