/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:37:51 by saan              #+#    #+#             */
/*   Updated: 2026/03/30 15:54:50 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dup_texture_path(t_game *g, char *type, char *path)
{
	if (!ft_strncmp(type, "NO", 2))
	{
		g->map.tp_n = ft_strdup(path);
		if (!g->map.tp_n)
			return (error_msg("Error :: malloc faile"));
	}
	if (!ft_strncmp(type, "SO", 2))
	{
		g->map.tp_s = ft_strdup(path);
		if (!g->map.tp_s)
			return (error_msg("Error :: malloc faile"));
	}
	if (!ft_strncmp(type, "WE", 2))
	{
		g->map.tp_w = ft_strdup(path);
		if (!g->map.tp_w)
			return (error_msg("Error :: malloc faile"));
	}
	if (!ft_strncmp(type, "EA", 2))
	{
		g->map.tp_e = ft_strdup(path);
		if (!g->map.tp_e)
			return (error_msg("Error :: malloc faile"));
	}
	return (0);
}
