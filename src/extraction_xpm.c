/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction_xpm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:25:25 by saan              #+#    #+#             */
/*   Updated: 2026/02/06 20:26:32 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_texture_path(t_game *g, char *line)
{
	char	*type;

	type = ft_substr(line, 0, 2);
	line += 2;
	while (ft_isspace(*line))
		line++;
	if (is_already_def(g, type) || !is_right_extention(line, "xpm"))
	{
		free(type);
		return (1);
	}
	if (!ft_strncmp(type, "NO", 2))
		g->map.tp_n = ft_strdup(line);
	if (!ft_strncmp(type, "SO", 2))
		g->map.tp_s = ft_strdup(line);
	if (!ft_strncmp(type, "WE", 2))
		g->map.tp_w = ft_strdup(line);
	if (!ft_strncmp(type, "EA", 2))
		g->map.tp_e = ft_strdup(line);
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
		if (is_texture(line))
			if (put_texture_path(g, line))
				return (1);
		free(temp);
	}
	if (!g->map.tp_e || !g->map.tp_n || !g->map.tp_s || !g->map.tp_w)
		sig = 1;
	return (sig);
}
