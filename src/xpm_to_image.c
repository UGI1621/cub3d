/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:14:59 by saan              #+#    #+#             */
/*   Updated: 2026/01/26 23:11:13 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_texture(char *str)
{
	if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) || !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
		return (1);
	return (0);
}

static int check_texture(t_game *g)
{
	if (g->map.texture_n == NULL || g->map.texture_s == NULL || g->map.texture_w == NULL || g->map.texture_e == NULL)
		return (1);
	return (0);
}

int xpm_to_image(char *str, t_game *g)
{
	int img_w;
	int img_h;

	img_w = 0;
	img_h = 0;
	str += 2;
	while (ft_isspace(*str))
		str++;
	if (!ft_strncmp(str, "NO", 2))
		g->map.texture_n = mlx_xpm_to_image(g->mlx, str, &img_w, &img_h);
	else if (!ft_strncmp(str, "SO", 2))
		g->map.texture_s = mlx_xpm_to_image(g->mlx, str, &img_w, &img_h);
	else if (!ft_strncmp(str, "WE", 2))
		g->map.texture_w = mlx_xpm_to_image(g->mlx, str, &img_w, &img_h);
	else if (!ft_strncmp(str, "EA", 2))
		g->map.texture_e = mlx_xpm_to_image(g->mlx, str, &img_w, &img_h);
	if (img_w != 16 || img_h != 16)
		return (error_msg("Error :: invalid xmp size"));
	if (check_texture(g))
		return (error_msg("Error :: fail mlx_xpm_to_image"));
	return (0);
}
