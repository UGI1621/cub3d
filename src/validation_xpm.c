/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_xpm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 20:11:46 by saan              #+#    #+#             */
/*   Updated: 2026/01/31 20:32:37 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static is_right_info(char **line)
{

}

int	valid_xpm_file(int fd)
{
	char *line;
	int cnt;

	cnt = 0;
	while (cnt < 2)
	{
		line = get_next_line(fd);
		free(line);
		cnt++;
	}
	line = get_next_line(fd);
	printf("line : %s\n", line);
	// if (!is_right_info(line))
	// {
	// 	close(fd);
	// 	return (1);
	// }
	free(line);
	return (0);
}
