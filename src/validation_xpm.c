/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_xpm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 20:11:46 by saan              #+#    #+#             */
/*   Updated: 2026/02/06 20:14:03 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int open_xpm_file(char *filename)
{
	int fd;
	char dir_test;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			ft_putendl_fd("Error :: xpm : permission denied", 2);
		else
			ft_putendl_fd("Error :: xpm : open failed", 2);
		return (fd);
	}
	if (read(fd, &dir_test, 1) == -1 && errno == EISDIR)
	{
		close(fd);
		ft_putendl_fd("Error :: xpm : is directory", 2);
		return (-1);
	}
	return (fd);
}

static int gnl_to_xpm_header(int fd)
{
	int cnt;
	char *line;

	cnt = 0;
	while (cnt < 3)
	{
		line = get_next_line(fd);
		if (!line)
			return (error_msg("Error :: invalid xpm file"));
		free(line);
		cnt++;
	}
	return (0);
}

static int	validation_xpm_info(char *path)
{
	int fd;
	char *line;
	int cn;

	cn = 0;
	fd = open_xpm_file(path);
	if (fd == -1)
		return (1);
	if (gnl_to_xpm_header(fd))
		return (1);
	line = get_next_line(fd);
	if (check_xpm_header(line, &cn))
	{
		free(line);
		return (1);
	}
	free(line);
	if (check_xpm_color_def(fd, &cn))
	{
		gnl_drain(fd);
		return (1);
	}
	gnl_drain(fd);
	return (0);
}

int	valid_xpm(char *filename, t_game *g)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	if (extraction_texture_path(g, fd))
	{
		gnl_drain(fd);
		close(fd);
		return (error_msg("Error :: invalid path of texture"));
	}
	close(fd);
	if (validation_xpm_info(g->map.tp_e)
		|| validation_xpm_info(g->map.tp_w)
		|| validation_xpm_info(g->map.tp_s)
		|| validation_xpm_info(g->map.tp_n))
		return (1);
	return (0);
}
