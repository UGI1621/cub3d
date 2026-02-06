/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:31:00 by saan              #+#    #+#             */
/*   Updated: 2026/02/06 14:39:01 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_msg(char *msg)
{
	ft_putendl_fd(msg, 1);
	return (1);
}

int error_elements(t_game *g)
{
	if (check_texture(g))
		return (1);
	if (is_map_turn(g))
		return (error_msg("Error :: unexpected element"));
	return (error_msg("Error :: required element is not defined"));
}
