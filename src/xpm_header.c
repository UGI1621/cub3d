/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:58:14 by saan              #+#    #+#             */
/*   Updated: 2026/02/06 20:12:01 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_xpm_header(char *line, int *cn)
{
	char *trim;
	char **info;

	if (!line)
		return (error_msg("Error :: invalid xpm header"));
	trim = ft_strtrim(line, "\",\n");
	if (!trim)
		return (error_msg("Error :: failed malloc"));
	info = ft_split(trim, ' ');
	if (!info)
		return (error_msg("Error :: failed malloc"));
	if (two_ptr_len(info) != 4)
	{
		free_2ptr(info);
		return (error_msg("Error :: invalid xpm header"));
	}
	*cn = ft_atoi(info[2]);
	if (ft_atoi(info[0]) != XPM_W || ft_atoi(info[1]) != XPM_H || ft_atoi(info[3]) != XPM_CPP)
	{
		free_2ptr(info);
		return (error_msg("Error :: invalid xpm header"));
	}
	free_2ptr(info);
	return (0);
}
