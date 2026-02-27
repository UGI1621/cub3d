/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:27:15 by saan              #+#    #+#             */
/*   Updated: 2026/02/28 01:18:51 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_xpm_w(char *line)
{
	char	*trim;

	trim = ft_strtrim(line, "\n,");
	if ((ft_strlen(trim) - 2) / (XPM_W * 2) != 1)
	{
		free(trim);
		free(line);
		return (error_msg("Error :: Unmatched pixel number of col"));
	}
	free(trim);
	return (0);
}

int	check_xpm_pixel(int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '}')
		{
			free(line);
			break ;
		}
		if (check_xpm_w(line))
			return (1);
		free(line);
		i++;
	}
	if (XPM_H != i)
		return (error_msg("Error :: Unmatched pixel number of row"));
	return (0);
}
