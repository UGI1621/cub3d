/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:58:14 by saan              #+#    #+#             */
/*   Updated: 2026/02/10 15:17:50 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char **extract_info(char *line)
{
	char *trim;
	char **res;

	res = NULL;
	if (!line)
	{
		ft_putstr_fd("Error :: invalid xpm header", 2);
		return (NULL);
	}
	line[ft_strlen(line) - 1] = 0;
	trim = ft_strtrim(line, "\",");
	if (!trim)
	{
		ft_putstr_fd("Error :: failed malloc", 2);
		return (NULL);
	}
	res = ft_split(trim, ' ');
	free(trim);
	if (!res)
	{
		ft_putstr_fd("Error :: failed malloc", 2);
		return (NULL);
	}
	return (res);
}

int check_xpm_header(char *line, int *cn)
{
	char **info;

	info = extract_info(line);
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
