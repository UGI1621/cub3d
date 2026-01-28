/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:34:15 by saan              #+#    #+#             */
/*   Updated: 2026/01/28 10:38:19 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_sig(char *str, t_game *g)
{
	int len;

	if (!(*str))
		return (0);
	len = ft_strlen(str);
	str[len - 1] = 0;
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

int is_map_turn(t_game *g)
{
	if (!g->map.c || !g->map.f || !g->map.texture_e || !g->map.texture_n || !g->map.texture_s || !g->map.texture_w)
		return (0);
	return (1);
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
			return (1); // 순서 안맞음
		}
		free(temp);
		if (is_map_turn(g))
			break ;
		line = get_next_line(g->map.fd);
	}
	if (check_texture(g))
			return (error_msg("Error :: fail mlx_xpm_file_to_image"));
	return (0);
}
