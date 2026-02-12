/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:14:59 by saan              #+#    #+#             */
/*   Updated: 2026/02/12 17:40:14 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture_info(t_game *g)
{
	g->map.tex_n.addr = mlx_get_data_addr(g->map.tex_n.ptr, &g->map.tex_n.bpp,
			&g->map.tex_n.line_len, &g->map.tex_n.endian);
	if (!g->map.tex_n.addr)
		return (1);
	g->map.tex_s.addr = mlx_get_data_addr(g->map.tex_s.ptr, &g->map.tex_s.bpp,
			&g->map.tex_s.line_len, &g->map.tex_s.endian);
	if (!g->map.tex_s.addr)
		return (1);
	g->map.tex_e.addr = mlx_get_data_addr(g->map.tex_e.ptr, &g->map.tex_e.bpp,
			&g->map.tex_e.line_len, &g->map.tex_e.endian);
	if (!g->map.tex_e.addr)
		return (1);
	g->map.tex_w.addr = mlx_get_data_addr(g->map.tex_w.ptr, &g->map.tex_w.bpp,
			&g->map.tex_w.line_len, &g->map.tex_w.endian);
	if (!g->map.tex_w.addr)
		return (1);
	return (0);
}

int	check_texture(t_game *g)
{
	if (g->map.tex_n.ptr == NULL || g->map.tex_s.ptr == NULL
		|| g->map.tex_w.ptr == NULL || g->map.tex_e.ptr == NULL)
		return (error_msg("Error :: fail mlx_xpm_file_to_image"));
	if (g->map.tex_n.w != XPM_W || g->map.tex_n.h != XPM_H)
		return (error_msg("Error :: invalid size of xpm"));
	if (g->map.tex_s.w != XPM_W || g->map.tex_s.h != XPM_H)
		return (error_msg("Error :: invalid size of xpm"));
	if (g->map.tex_e.w != XPM_W || g->map.tex_e.h != XPM_H)
		return (error_msg("Error :: invalid size of xpm"));
	if (g->map.tex_w.w != XPM_W || g->map.tex_w.h != XPM_H)
		return (error_msg("Error :: invalid size of xpm"));
	if (load_texture_info(g))
		return (error_msg("Error :: fail mlx_get_data_addr"));
	if (g->map.c == -1 || g->map.f == -1)
		return (error_msg("Error :: not define c or f"));
	return (0);
}

int is_already_def(t_game *g, char *type)
{
	if (!ft_strncmp(type, "NO", 2))
	{
		if (g->map.tp_n)
			return (error_msg("Error :: multiple define of wall texture"));
	}
	if (!ft_strncmp(type, "SO", 2))
	{
		if (g->map.tp_s)
			return (error_msg("Error :: multiple define of wall texture"));
	}
	if (!ft_strncmp(type, "WE", 2))
	{
		if (g->map.tp_w)
			return (error_msg("Error :: multiple define of wall texture"));
	}
	if (!ft_strncmp(type, "EA", 2))
	{
		if (g->map.tp_e)
			return (error_msg("Error :: multiple define of wall texture"));
	}
	return (0);
}

static int xpm_file_to_image(t_game *g, char *str, char *type)
{
	if (!ft_strncmp(type, "NO", 2))
		g->map.tex_n.ptr = mlx_xpm_file_to_image(g->mlx, str, &g->map.tex_n.w,
				&g->map.tex_n.h);
	if (!ft_strncmp(type, "SO", 2))
		g->map.tex_s.ptr = mlx_xpm_file_to_image(g->mlx, str, &g->map.tex_s.w,
				&g->map.tex_s.h);
	if (!ft_strncmp(type, "WE", 2))
		g->map.tex_w.ptr = mlx_xpm_file_to_image(g->mlx, str, &g->map.tex_w.w,
				&g->map.tex_w.h);
	if (!ft_strncmp(type, "EA", 2))
		g->map.tex_e.ptr = mlx_xpm_file_to_image(g->mlx, str, &g->map.tex_e.w,
				&g->map.tex_e.h);
	return (0);
}

int	xpm_to_image(char *str, t_game *g)
{
	char	*type;

	type = ft_substr(str, 0, 2);
	str += 2;
	while (ft_isspace(*str))
		str++;
	if (xpm_file_to_image(g, str, type))
		return (1);
	free(type);
	return (0);
}
