/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:34:15 by saan              #+#    #+#             */
/*   Updated: 2026/01/26 23:10:17 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_sig(char *str, t_game *g)
{
	if (is_texture(str))
	{
		if (xpm_to_image(str, g))
			return (1);
	}
	else if (is_fc(str))
	{
		if (rgb_to_int(str, g))
			return (1);
	}
	return (0);
}

int parsing_cub(t_game *g)
{
	char	*line;
	char	*temp;

	line = get_next_line(g->map.fd);
	while(line)
	{
		temp = line;
		while (ft_isspace(*line))
			line++;
		if (parse_sig(line, g))
		{
			free(temp);
			return (1);
		}
		free(temp);
		line = get_next_line(g->map.fd);
	}
	return (0);
}
