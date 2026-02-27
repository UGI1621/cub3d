/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:06:29 by saan              #+#    #+#             */
/*   Updated: 2026/02/28 01:16:30 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_already_def_cf(t_game *g, char type)
{
	if (type == 'F')
	{
		if (g->map.f != -1)
			return (error_msg("Error :: multiple define RGB"));
	}
	if (type == 'C')
	{
		if (g->map.c != -1)
			return (error_msg("Error :: multiple define RGB"));
	}
	return (0);
}

static int	append_value(t_game *g, char **rgb, char type)
{
	int	re;
	int	gr;
	int	bl;

	if (is_already_def_cf(g, type))
		return (1);
	re = ft_atoi(rgb[0]);
	gr = ft_atoi(rgb[1]);
	bl = ft_atoi(rgb[2]);
	if (re < 0 || re > 255 || gr < 0 || gr > 255 || bl < 0 || bl > 255)
		return (error_msg("Error :: invalid rgb value"));
	if (type == 'F')
		g->map.f = (re << 16 | gr << 8 | bl);
	else if (type == 'C')
		g->map.c = (re << 16 | gr << 8 | bl);
	return (0);
}

int	valid_rgb(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	rgb_to_int(char *str, t_game *g)
{
	char	type;
	char	**rgb;
	int		i;

	type = *(str++);
	while (ft_isspace(*str))
		++str;
	rgb = ft_split(str, ',');
	if (!rgb)
		return (error_msg("Error :: split fail"));
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3 || valid_rgb(rgb))
	{
		free_2ptr(rgb);
		return (error_msg("Error :: invalid define rgb"));
	}
	if (append_value(g, rgb, type))
	{
		free_2ptr(rgb);
		return (1);
	}
	free_2ptr(rgb);
	return (0);
}
