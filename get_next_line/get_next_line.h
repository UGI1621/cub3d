/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:18:23 by saan              #+#    #+#             */
/*   Updated: 2026/02/06 14:56:23 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line(int fd);
void	clear_remain(char **remain);


char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_gnl_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
