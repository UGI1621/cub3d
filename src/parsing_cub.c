/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:34:15 by saan              #+#    #+#             */
/*   Updated: 2026/02/12 17:42:55 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_sig(char *str, t_game *g)
{
	int	len;

	if (!(*str))
		return (0);
	len = ft_strlen(str);
	str[len - 1] = 0;
	if (is_texture(str))
	{
		if (xpm_to_image(str, g))
			return (1);
	}
	else if (*str == 'F' || *str == 'C')
		return (0);
	else
		return (error_elements(g));
	return (0);
}

int	is_map_turn(t_game *g)
{
	if (!g->map.tex_e.ptr || !g->map.tex_n.ptr
		|| !g->map.tex_s.ptr || !g->map.tex_w.ptr)
		return (0);
	return (1);
}

int	parsing_cub(t_game *g)
{
	char	*line;
	char	*temp;

	line = get_next_line(g->map.fd);
	while (line)
	{
		temp = line;
		while (ft_isspace(*line))
			line++;
		if (parse_sig(line, g))
		{
			get_next_line(-1);
			free(temp);
			return (1);
		}
		free(temp);
		if (is_map_turn(g))
			break ;
		line = get_next_line(g->map.fd);
	}
	gnl_drain(g->map.fd);
	if (check_texture(g))
		return (1);
	return (0);
}
