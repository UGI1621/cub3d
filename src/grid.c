/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 08:42:38 by saan              #+#    #+#             */
/*   Updated: 2026/01/28 09:38:19 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int copy_map_to_grid(t_game *g, char *str, int i)
{
	int j;

	g->map.grid[i] = (char *)ft_calloc(g->map.w, sizeof(char));
	if (!g->map.grid[i])
		return (error_msg("Error :: grid : malloc error"));
	j = 0;
	while (j < g->map.w - 1)
	{
		if (j > ft_strlen(str) || ft_isspace(str[j]) || !is_right_map_element(str[j], NULL))
			g->map.grid[i][j] = 'X';
		else
			g->map.grid[i][j] = str[j];
		j++;
	}
	return (0);
}

void	print_grid(char **grid)
{
	int i = -1;

	printf("----------- grid -----------\n");
	while (grid[++i])
		printf("%s\n", grid[i]);
}

int	fill_grid(t_game *g)
{
	char	*line;
	int		i;

	i = 0;
	g->map.grid_fd = open("map_grid.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(g->map.grid_fd);
		if (!line)
			break ;
		if (copy_map_to_grid(g, line, i))
			return (1);
		i++;
	}
	g->map.grid[g->map.h] = NULL;
	close(g->map.grid_fd);
	print_grid(g->map.grid);
	return (0);
}
