/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:59:01 by saan              #+#    #+#             */
/*   Updated: 2026/01/31 20:29:58 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture(char *str)
{
	if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
		|| !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
		return (1);
	return (0);
}

int	is_right_extention(char *fname, char *ext)
{
	char	*ptr;
	int		ext_len;

	ext_len = ft_strlen(ext);
	ptr = ft_strrchr(fname, '.');
	if (!ptr)
		return (0);
	ptr++;
	if ((ft_strlen(ptr) != (size_t)ext_len))
		return (0);
	if (ft_strncmp(ptr, ext, ext_len))
		return (0);
	return (1);
}

int	is_right_map_element(char c, int *user)
{
	if (c == ' ' || c == '1' || c == '0' || c == '\n')
		return (1);
	if (user)
	{
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			(*user)++;
			if ((*user) > 1)
				return (0);
			return (1);
		}
	}
	return (0);
}

int	valid_files(char *str, char* type)
{
	char dir_test;
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		free(type);
		if (errno == EACCES)
			return (error_msg("Error :: xmp : permission denied"));
		else
			return (error_msg("Error :: xmp : open failed"));
	}
	if (read(fd, &dir_test, 1) == -1 && errno == EISDIR)
	{
		free(type);
		close(fd);
		return (error_msg("Error :: xmp : is directory"));
	}
	if (!valid_xpm_file(fd))
	{
		free(type);
		return (1);
	}
	close(fd);
	return (0);
}

int	valid_args(int ac, char **av, t_game *g)
{
	int		fd;
	char	dir_test;

	if (ac != 2)
		return (error_msg("Usage :: ./cub3d {path_of_cub_file}"));
	if (!is_right_extention(av[1], "cub"))
		return (error_msg("Error :: not a .cub file"));
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
