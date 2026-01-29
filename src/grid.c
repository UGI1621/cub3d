/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 08:42:38 by saan              #+#    #+#             */
/*   Updated: 2026/01/29 21:46:12 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	copy_map_to_grid(t_game *g, char *str, int i)
{
	int	j;

	g->map.grid[i] = (char *)ft_calloc(g->map.w + 1, sizeof(char));
	if (!g->map.grid[i])
		return (error_msg("Error :: grid : malloc error"));
	j = 0;
	while (j < g->map.w)
	{
		if (j >= (int)ft_strlen(str) || ft_isspace(str[j]))
			g->map.grid[i][j] = 'X';
		else if (str[j] == 'W' || str[j] == 'E' || str[j] == 'N'
			|| str[j] == 'S')
			g->map.grid[i][j] = str[j];
		else
			g->map.grid[i][j] = str[j];
		j++;
	}
	return (0);
}

void	print_grid(char **grid)
{
	int	i;

	i = -1;
	printf("----------- grid -----------\n");
	while (grid[++i])
		printf("%s\n", grid[i]);
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

void	bfs(t_game *g, int w, int h, int *sig)
{
	if (w < 0 || h < 0 || w > g->map.w || h > g->map.h)
		return ;
	if (!g->map.copy_grid[h][w] || g->map.copy_grid[h][w] == '1'
		|| g->map.copy_grid[h][w] == 'B')
		return ;
	if (g->map.copy_grid[h][w] == 'X')
	{
		*sig = 1;
		return ;
	}
	if (is_player(g->map.copy_grid, w, h))
		update_player_data(g, w, h, g->map.copy_grid[h][w]);
	g->map.copy_grid[h][w] = 'B';
	// print_grid(g->map.copy_grid);
	// usleep(50000); // 1000000 = 1sec
	bfs(g, w + 1, h, sig);
	bfs(g, w - 1, h, sig);
	bfs(g, w, h + 1, sig);
	bfs(g, w, h - 1, sig);
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
	while (g->map.copy_grid[h])
	{
		while (g->map.copy_grid[h][w] && g->map.copy_grid[h][w] != '0')
			w++;
		bfs(g, w, h, &sig);
		if (sig)
			return (1);
		if (!(w < g->map.w - 1))
			h++;
		w = 0;
	}
	free_grid(g->map.copy_grid);
	return (0);
}

int	fill_grid(t_game *g)
{
	char	*line;
	int		i;
	int		sig;

	i = 0;
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
	g->map.grid[g->map.h] = NULL;
	close(g->map.grid_fd);
	sig = validation_grid(g);
	if (sig == 1)
		return (error_msg("Error :: grid : not surrounded map"));
	else if (sig == 2)
		return (error_msg("Error :: copy_grid : fail malloc"));
	return (0);
}
