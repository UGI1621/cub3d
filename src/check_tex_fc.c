/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tex_fc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:41:58 by saan              #+#    #+#             */
/*   Updated: 2026/03/16 13:51:06 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_return(int tex, int fc, int fd)
{
	close(fd);
	if (tex < 4 || fc < 2)
		return (error_msg("Error :: Missing texture or ceiling/floor definition."));
	if (tex > 4)
		return (error_msg("Error :: Multiple define texture"));
	if (fc > 2)
		return (error_msg("Error :: Multiple define floor/ceiling"));
	return (0);
}

int check_tex_fc(char *path)
{
	int fd;
	int tex;
	int fc;
	char *line;

	tex = 0;
	fc = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (error_msg("Error :: open error"));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (gtm_is_texture(line))
			tex++;
		if (gtm_is_fc(line))
			fc++;
		free(line);
	}
	return (handle_return(tex, fc, fd));
}
