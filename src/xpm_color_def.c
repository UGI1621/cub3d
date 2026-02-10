/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_color_def.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:06:09 by saan              #+#    #+#             */
/*   Updated: 2026/02/10 16:05:00 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_rgb_val(char *rgb)
{
	int	i;

	if (!rgb)
		return (1);
	if (rgb[0] != '#')
		return (1);
	if (rgb[7] != '\0')
		return (1);
	i = 1;
	while (i < 7)
	{
		if (!((rgb[i] >= '0' && rgb[i] <= '9') || (rgb[i] >= 'a'
					&& rgb[i] <= 'f') || (rgb[i] >= 'A' && rgb[i] <= 'F')))
			return (1);
		i++;
	}
	return (0);
}

static char	**init_info(char *trim)
{
	char	**res;

	res = (char **)ft_calloc(3, sizeof(char *));
	if (!res)
	{
		free(trim);
		return (NULL);
	}
	res[0] = ft_substr(trim, XPM_CPP + 1, 1);
	res[1] = ft_substr(trim, XPM_CPP + 3, 7);
	res[2] = NULL;
	free(trim);
	if (!res[0] || !res[1])
	{
		if (res[0])
			free(res[0]);
		if (res[1])
			free(res[1]);
		free(res);
		return (NULL);
	}
	return (res);
}

static int	check_xpm_color_info(char *line)
{
	char	*trim;
	char	**info;

	trim = ft_strtrim(line, "\"\n");
	if (!trim)
		return (error_msg("Error :: failed malloc"));
	info = init_info(trim);
	if (!info)
		return (error_msg("Error :: failed malloc"));
	if (info[0][0] != 'c' || check_rgb_val(info[1]))
	{
		free_2ptr(info);
		return (error_msg("Error :: invalid color define"));
	}
	free_2ptr(info);
	return (0);
}

int	check_xpm_color_def(int fd, int *cn)
{
	char	*line;
	int		cnt;

	cnt = 0;
	line = get_next_line(fd);
	while (!ft_strnstr(line, "pixels", ft_strlen(line)))
	{
		if (!line)
			break ;
		cnt++;
		if (check_xpm_color_info(line))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (cnt != *cn)
		return (error_msg("Error :: unmatched color amount with xpm header"));
	return (0);
}
