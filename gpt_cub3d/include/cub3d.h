#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>

# define WIN_W 800
# define WIN_H 600

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

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
	int		w;
	int		h;
	char	**grid;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
}	t_player;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_map		map;
	t_player	pl;
	t_keys		keys;
}	t_game;

/* init */
int		init_game(t_game *g);

/* render */
int		game_loop(t_game *g);
void	clear_frame(t_game *g, int ceil_c, int floor_c);
void	put_pixel(t_game *g, int x, int y, int color);

/* raycast */
void	render_3d(t_game *g);

/* input */
int		on_key_press(int key, t_game *g);
int		on_key_release(int key, t_game *g);
int		on_close(t_game *g);

/* map */
int		load_demo_map(t_game *g);

/* cleanup */
void	cleanup_and_exit(t_game *g, int code);

#endif
