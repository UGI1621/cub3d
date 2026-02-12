/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_to_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:20:32 by saan              #+#    #+#             */
/*   Updated: 2026/02/12 17:36:53 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	gtm_is_texture(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (is_texture(line))
		return (1);
	return (0);
}

void	gnl_to_map(int fd)
{
	char	*line;
	int tex;
	int fc;

	tex = 0;
	fc = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (gtm_is_texture(line))
			tex++;
		if (*line == 'F' || *line == 'C')
			fc++;
		if (tex == 4 && fc == 2)
		{
			free(line);
			break ;
		}
		free(line);
	}
}
