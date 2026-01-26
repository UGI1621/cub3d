/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:53:18 by saan              #+#    #+#             */
/*   Updated: 2026/01/27 02:04:31 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_W 800
# define WIN_H 600

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
	int		fd;
	int		w;
	int		h;
	int		f;
	int		c;
	char	**grid;
	int		grid_fd;
	void		*texture_n;
	void		*texture_s;
	void		*texture_w;
	void		*texture_e;
}	t_map;

typedef struct s_player
{
	double x;
	double y;
	double dir_x;
	double dir_y;
	double fov;
	double plane_x;
	double plane_y;
}	t_player;

typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	int left;
	int right;
}	t_keys;

typedef struct s_game
{
	void *mlx;
	void *win;
	t_img frame;
	t_map map;
	t_player pl;
	t_keys keys;
}	t_game;


// cleanup.c
void cleanup_and_exit(t_game *g, int code);

// error.c
int error_msg(char *msg);

// init.c
int	init_game(t_game *g);

// input.c
int on_key_press(int key, t_game *g);
int	on_key_release(int key, t_game *g);
int	on_close(t_game *g);

// parsing_cub.c
int parsing_cub(t_game *g);

// parsing_map.c
int parsing_map(t_game *g);

// raycast.c
void render_3d(t_game *g);

// render.c
int 	game_loop(t_game *g);
void	put_pixel(t_game *g, int x, int y, int color);
void	clear_frame(t_game *g, int ceil_c, int floor_c);

// rgb_to_int.c
int is_fc(char *str);
int rgb_to_int(char *str, t_game *g);

// validation.c
int valid_args(int ac, char **av, t_game *g);
int	is_right_extention(char *fname, char *ext);
int is_right_map_element(char c, int *user);

// xpm_to_image.c
int is_texture(char *str);
int check_texture(t_game *g);
int xpm_to_image(char *str, t_game *g);

#endif
