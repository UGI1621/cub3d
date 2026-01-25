/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:59:01 by saan              #+#    #+#             */
/*   Updated: 2026/01/25 20:31:36 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_right_extention(char fname, char *ext)
{
	char *ptr;
	int		ext_len;

	ext_len = ft_strlen(ext);
	ptr = ft_strrchr(fname, '.') + 1;
	if (!ptr || ft_strlen(ptr) != ext_len)
		return (0);
	if (!ft_strncmp(ptr, ext, ext_len))
		return (0);
	return (1);
}

int valid_args(int ac, char **av, t_game *g)
{
	int fd;
	char dir_test;

	if (ac != 2 || !is_right_extention(av[1], "cub"))
		return (error_msg("Usage :: ./cub3d {path_of_cub_file}"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (error_msg("Error :: permission denied"));
		else
			return (error_msg("Error :: open failed"));
	}
	if (read(fd, &dir_test, 1) == -1 && errno == EISDIR)
	{
		close(fd);
		return (error_msg("Error :: is directory"));
	}
	close(fd);
	g->map.fd = open(av[1], O_RDONLY);
	return (0);
}
