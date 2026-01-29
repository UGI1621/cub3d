/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:06:29 by saan              #+#    #+#             */
/*   Updated: 2026/01/29 19:32:21 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_fc(char *str)
{
	if (*str == 'F' || *str == 'C')
		return (1);
	return (0);
}

static void	free_2ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

static int	append_value(t_game *g, char **rgb, char type)
{
	int	re;
	int	gr;
	int	bl;

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

int	rgb_to_int(char *str, t_game *g)
{
	char	type;
	char	**rgb;

	type = *(str++);
	while (ft_isspace(*str))
		++str;
	rgb = ft_split(str, ',');
	if (!rgb)
		return (error_msg("Error :: split fail"));
	if (append_value(g, rgb, type))
	{
		free_2ptr(rgb);
		return (1);
	}
	free_2ptr(rgb);
	return (0);
}
