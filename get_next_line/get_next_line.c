/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:11:35 by saan              #+#    #+#             */
/*   Updated: 2025/04/14 23:08:00 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char **remain)
{
	int		idx;
	char	*temp;
	char	*line;

	idx = ft_gnl_strchr(*remain, '\n');
	if (idx != -1)
	{
		temp = *remain;
		line = ft_substr(temp, 0, idx + 1);
		*remain = ft_substr(temp, idx + 1, BUFFER_SIZE);
		free(temp);
	}
	else
	{
		temp = *remain;
		line = ft_strdup(*remain);
		free(*remain);
		*remain = NULL;
	}
	return (line);
}

void	ft_read(int fd, char *buf, char **remain)
{
	int		read_size;
	char	*temp;

	while (1)
	{
		if (ft_gnl_strchr(*remain, '\n') != -1)
			break ;
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size < 0)
		{
			temp = *remain;
			free(temp);
			*remain = NULL;
			break ;
		}
		else
		{
			buf[read_size] = 0;
			temp = *remain;
			*remain = ft_strjoin(temp, buf);
			free(temp);
			if (read_size == 0)
				break ;
		}
	}
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*remain;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remain)
		remain = ft_strdup("");
	if (!remain)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	ft_read(fd, buf, &remain);
	free(buf);
	if (!remain || !remain[0])
	{
		free(remain);
		remain = NULL;
		return (NULL);
	}
	line = ft_get_line(&remain);
	return (line);
}
