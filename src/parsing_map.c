/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:29:08 by saan              #+#    #+#             */
/*   Updated: 2026/01/27 02:43:41 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_only_space(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (!(*str))
		return (1);
	return (0);
}

static int make_grid_file(t_game *g)
{
	char *line;

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
	return (0);
}

static int is_valid_elements(char *str, t_game *g, int *user)
{
	int width;

	width = 0;
	while (str[width])
	{
		if (!is_right_map_element(str[width], user))
			return (0);
		width++;
	}
	if (g->map.w < width)
		g->map.w = width;
	return (1);
}

static int check_element(t_game *g)
{
	char *line;
	int height;
	int user;

	user = 0;
	height = 0;
	while (1)
	{
		line = get_next_line(g->map.grid_fd);
		if (!line)
			break ;
		if (!is_valid_elements(line, g, &user))
			return (error_msg("Error :: invalid map element"));
		height++;
		free(line);
	}
	g->map.h = height;
	return (0);
}

int parsing_map(t_game *g)
{
	if (make_grid_file(g))
		return (1);
	if (check_element(g))
		return (1);
	// g->map.grid = (char **)ft_calloc(g->map.h, sizeof(char *));
	// if (!g->map.grid)
	// 	return (error_msg("Error :: fail malloc"));
	return (0);
}
