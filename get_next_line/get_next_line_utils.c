/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:18:07 by saan              #+#    #+#             */
/*   Updated: 2024/11/30 05:53:43 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *str)
{
	char	*temp;
	size_t	len;
	size_t	i;

	len = 0;
	while (str[len])
		len++;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (++i < len)
		temp[i] = str[i];
	temp[len] = '\0';
	return (temp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;
	size_t	i;

	s1_len = 0;
	s2_len = 0;
	while (s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	total_len = s1_len + s2_len;
	res = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!res)
		return (0);
	i = -1;
	while (++i < s1_len)
		res[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		res[i + s1_len] = s2[i];
	res[total_len] = '\0';
	return (res);
}

int	ft_gnl_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	if (s[i] != c)
		return (-1);
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*temp;
	size_t	i;

	s_len = 0;
	while (s[s_len])
		s_len++;
	if (s_len - start < len)
		len = s_len - start;
	if (s_len < start)
	{
		temp = (char *)malloc(sizeof(char) * 1);
		if (!temp)
			return (0);
		temp[0] = '\0';
		return (temp);
	}
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (++i < len && s[start])
		temp[i] = s[start++];
	temp[len] = '\0';
	return (temp);
}
