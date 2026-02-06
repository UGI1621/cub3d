/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_xpm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 20:11:46 by saan              #+#    #+#             */
/*   Updated: 2026/02/06 14:49:49 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_xpm_file(int fd)
{
	char *line = get_next_line(fd);
	printf("line : %s\n",line);
	free(line);
	return (0);
}
