/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:59:01 by saan              #+#    #+#             */
/*   Updated: 2026/01/24 09:59:54 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int valid_args(int ac, char **av)
{
	int fd;

	if (ac != 2)
		return (error_msg("Usage :: ./cub3d {path_of_cub_file}"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (error_msg("Error :: permission denied"));
		else
			return (error_msg("Error :: open failed"));
	}

	return (0);
}
