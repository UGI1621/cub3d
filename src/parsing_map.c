/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:29:08 by saan              #+#    #+#             */
/*   Updated: 2026/01/31 20:21:41 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_only_space(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (!(*str))
		return (1);
	return (0);
}

static int	make_grid_file(t_game *g)
{
	char	*line;

	g->map.grid_fd = open("map_grid.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (g->map.grid_fd == -1)
		return (error_msg("Error :: open error"));
	while (1)
	{
		line = get_next_line(g->map.fd);
		if (is_only_space(line))
		{
			free(line);
			continue ;
		}
		else
			break ;
	}
	while (line)
	{
		ft_putstr_fd(line, g->map.grid_fd);
		free(line);
		line = get_next_line(g->map.fd);
	}
	close(g->map.fd);
	close(g->map.grid_fd);
	return (0);
}

static int	is_valid_elements(char *str, int *ori_width, int *user)
{
	int	new_width;

	new_width = 0;
	while (str[new_width])
	{
		if (!is_right_map_element(str[new_width], user))
			return (0);
		new_width++;
	}
	if (*ori_width < new_width)
		*ori_width = new_width;
	return (1);
}

static int	check_element(t_game *g)
{
	char	*line;
	int		height;
	int		width;
	int		user;

	user = 0;
	height = 0;
	width = 0;
	g->map.grid_fd = open("map_grid.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(g->map.grid_fd);
		if (!line)
			break ;
		if (!is_valid_elements(line, &width, &user))
			return (error_msg("Error :: invalid map element"));
		height++;
		free(line);
	}
	g->map.h = height;
	g->map.w = width;
	close(g->map.grid_fd);
	return (0);
}

int	parsing_map(t_game *g)
{
	if (make_grid_file(g))
		return (1);
	if (check_element(g))
		return (1);
	g->map.grid = (char **)ft_calloc(g->map.h + 1, sizeof(char *));
	if (!g->map.grid)
		return (error_msg("Error :: fail malloc"));
	if (fill_grid(g))
		return (1);
	return (0);
}
