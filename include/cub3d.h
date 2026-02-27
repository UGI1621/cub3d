/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:53:18 by saan              #+#    #+#             */
/*   Updated: 2026/02/27 23:39:10 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_W 1280
# define WIN_H 720

# define XPM_W 128
# define XPM_H 128
# define XPM_CPP 2

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define TARGET_FPS 60
# define FRAME_TIME (1.0 / TARGET_FPS)

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_tex
{
	void		*ptr;
	char		*addr;
	int			w;
	int			h;
	int			bpp;
	int			line_len;
	int			endian;
}				t_tex;

typedef struct s_map
{
	int			fd;
	int			w;
	int			h;
	int			f;
	int			c;
	char		**grid;
	char		**copy_grid;
	int			grid_fd;
	char		*tp_n;
	char		*tp_s;
	char		*tp_w;
	char		*tp_e;
	t_tex		tex_n;
	t_tex		tex_s;
	t_tex		tex_w;
	t_tex		tex_e;
}				t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_rc
{
	int			map_x;
	int			map_y;
	double		ray_dx;
	double		ray_dy;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		prep_dist;
	int			step_x;
	int			step_y;
	int			side;
}				t_rc;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_map		map;
	t_player	pl;
	t_keys		keys;
	t_rc		rc;
	double		lt;
}				t_game;

// calc_rc.c
void			calculate_rc(t_game *g, int x);
void			calc_append_delta_dist(t_game *g);
void			calc_step_side_dist(t_game *g);
void			calc_delta_dists(t_game *g);
void			calc_ray(t_game *g, int x);

// cleanup.c
void			cleanup_and_exit(t_game *g, int code);
void			free_xpm_path(t_game *g);
void			free_2ptr(char **grid);

// error.c
int				error_msg(char *msg);
int				error_elements(t_game *g);

// grid.c
int				fill_grid(t_game *g);

// init.c
int				init_game(t_game *g);
int init_mlx(t_game *g);

// input.c
void	apply_movement(t_game *g, double dt);
int				can_move(t_game *g, double nx, double ny);
int				on_key_press(int key, t_game *g);
int				on_key_release(int key, t_game *g);
int				on_close(t_game *g);

// movement.c
void			move_left_right(t_game *g, double rot);
void			move_w(t_game *g, double move);
void			move_a(t_game *g, double move);
void			move_s(t_game *g, double move);
void			move_d(t_game *g, double move);

// parsing_cub.c
int				is_map_turn(t_game *g);
int				parsing_cub(t_game *g);

// parsing_map.c
int	parsing_map(char *path, t_game *g);

// player.c
int				is_player(char **grid, int w, int h);
void			update_player_data(t_game *g, int w, int h, char dir);

// raycast.c
int				is_wall(t_game *g, int mx, int my);
void			render_3d(t_game *g);

// render.c
int				game_loop(t_game *g);
void			put_pixel(t_game *g, int x, int y, int color);
void			clear_frame(t_game *g, int ceil_c, int floor_c);

// rgb_to_int.c
int valid_rgb(char **rgb);
int				rgb_to_int(char *str, t_game *g);


// extraction_xpm.c
int	extraction_texture_path(t_game *g, int fd);


// validation_xpm.c
// int				valid_xpm_file(int fd);
int	valid_xpm(char *filename, t_game *g);

// xpm_header.c
int check_xpm_header(char *line, int *cn);

// xpm_pixel.c
int	check_xpm_pixel(int fd);

// xpm_color_def.c
int check_xpm_color_def(int fd, int *cn);

// validation.c
int				is_texture(char *str);
int				valid_args(int ac, char **av, t_game *g);
int				is_right_extention(char *fname, char *ext);
int				is_right_map_element(char c, int *user);
int				valid_files(char * str, char* type);

// xpm_to_image.c
int				is_already_def(t_game *g, char *type);
int				check_texture(t_game *g);
int				xpm_to_image(char *str, t_game *g);

// gnl_to_map.c
void	gnl_to_map(int fd);

// util.c
int	is_only_space(char *str);
double			cal_wall_x_val(t_game *g);
int	two_ptr_len(char **ptr);
void			gnl_drain(int fd);
int	handle_sig(int sig, t_game *g);

// player_position.c
int	valid_user_position(char **grid);

double	get_time(void);

void	print_grid(char **grid);

#endif
