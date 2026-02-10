/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_xpm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 20:11:46 by saan              #+#    #+#             */
/*   Updated: 2026/02/10 16:10:29 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	open_xpm_file(char *filename)
{
	int		fd;
	char	dir_test;

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

static int	gnl_to_xpm_header(int fd)
{
	int		cnt;
	char	*line;

	cnt = 0;
	while (cnt < 3)
	{
		line = get_next_line(fd);
		if (!line || *line == '\n')
		{
			gnl_drain(fd);
			close(fd);
			if (line)
				free(line);
			return (error_msg("Error :: invalid infomation of xpm file"));
		}
		free(line);
		cnt++;
	}
	return (0);
}

static int	free_drain(char *line, int fd, int sig)
{
	if (line)
		free(line);
	if (fd != -1)
	{
		gnl_drain(fd);
		close(fd);
	}
	return (sig);
}

static int	val_info(char *path)
{
	int		fd;
	char	*line;
	int		cn;

	cn = 0;
	fd = open_xpm_file(path);
	if (fd == -1)
		return (1);
	if (gnl_to_xpm_header(fd))
		return (1);
	line = get_next_line(fd);
	if (check_xpm_header(line, &cn))
		return (free_drain(line, fd, 1));
	free(line);
	if (check_xpm_color_def(fd, &cn))
		return (free_drain(NULL, fd, 1));
	gnl_drain(fd);
	close(fd);
	return (0);
}

int	valid_xpm(char *filename, t_game *g)
{
	int	fd;
	int	sig;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	sig = extraction_texture_path(g, fd);
	if (sig)
	{
		gnl_drain(fd);
		close(fd);
		close(g->map.fd);
		free_xpm_path(g);
		if (sig == 1)
			return (error_msg("Error :: invalid path of texture"));
		else
			return (1);
	}
	close(fd);
	if (val_info(g->map.tp_e) || val_info(g->map.tp_w) || val_info(g->map.tp_s)
		|| val_info(g->map.tp_n))
		return (1);
	return (0);
}
