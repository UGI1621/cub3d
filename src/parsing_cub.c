/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:34:15 by saan              #+#    #+#             */
/*   Updated: 2026/01/25 21:44:28 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_sig(char *str, t_game *g)
{
	int img_w;
	int img_h;

	if (!ft_strncmp(str, "NO", 2))
	{
		str += 2;
		while (ft_isspace(*str))
			str++;
		g->map.texture_n = mlx_xpm_to_image(g->mlx, str, &img_w, &img_h);
		if (img_w != 16 || img_h != 16 || g->map.texture_n == NULL)
			return (error_msg("Error :: invalid xmp file"));
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
