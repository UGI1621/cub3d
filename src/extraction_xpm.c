/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction_xpm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:25:25 by saan              #+#    #+#             */
/*   Updated: 2026/03/16 14:21:50 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	emwf(char *type, char *temp, char *msg)
{
	free(type);
	free(temp);
	return (error_msg(msg));
}

static int	put_texture_path(t_game *g, char *line, char *temp)
{
	char	*type;

	type = ft_substr(line, 0, 2);
	line += 2;
	while (ft_isspace(*line))
		line++;
	if (is_already_def(g, type))
		return (emwf(type, temp, "Error :: multiple define wall texture"));
	if (!is_right_extention(line, "xpm"))
		return (emwf(type, temp, "Errror :: is not xpm file"));
	if (!ft_strncmp(type, "NO", 2))
		g->map.tp_n = ft_strdup(line);
	if (!ft_strncmp(type, "SO", 2))
		g->map.tp_s = ft_strdup(line);
	if (!ft_strncmp(type, "WE", 2))
		g->map.tp_w = ft_strdup(line);
	if (!ft_strncmp(type, "EA", 2))
		g->map.tp_e = ft_strdup(line);
	free(type);
	return (0);
}

static int	map_turn(t_game *g)
{
	if (g->map.f == -1 || g->map.c == -1 || !g->map.tp_e || !g->map.tp_n
		|| !g->map.tp_s || !g->map.tp_w)
		return (0);
	return (1);
}

static int	parse_type(t_game *g, char *line, char *temp)
{
	if (!*line)
		return (0);
	if (is_texture(line))
	{
		if (put_texture_path(g, line, temp))
			return (1);
	}
	else if (*line == 'F' || *line == 'C')
	{
		if (rgb_to_int(line, g))
		{
			free(temp);
			return (1);
		}
	}
	else if (!map_turn(g))
	{
		free(temp);
		return (error_msg("Error :: invalid (elements or order) of file"));
	}
	return (0);
}

int	extraction_texture_path(t_game *g, int fd)
{
	char	*line;
	char	*temp;
	int		sig;

	sig = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = line;
		while (ft_isspace(*line))
			line++;
		line[ft_strlen(line) - 1] = 0;
		if (parse_type(g, line, temp))
			return (2);
		free(temp);
	}
	if (!g->map.tp_e || !g->map.tp_n || !g->map.tp_s || !g->map.tp_w)
		sig = 1;
	return (sig);
}
