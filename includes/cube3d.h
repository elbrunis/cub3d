#ifndef CUBE3D_H
# define CUBE3D_H

#include "../minilibx-linux/mlx.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

# define M_PI 3.14159265358979323846
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define N_MAP_CONFIG 6

# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_ESC 65307
# define K_LEFT 65361
# define K_RIGHT 65363

# define SPEED 0.009
# define MOVE_ANGLE 0.009
# define COLLISION_MARGIN 0.1

typedef struct s_list_map
{
	char				*line;
	struct s_list_map	*next;
}				t_list_map;

typedef struct s_parse
{
	int				fd;
	int				n_config;
	char			**map;
	double			x_pos;
	double			y_pos;
	double			angle;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	bool			player_set;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}				t_parse;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_tex;

typedef struct	s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	int		tex_x;
}				t_ray;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_player
{
	double	x_pos;
	double	y_pos;
	double	dir_x;
	double	dir_y;
	double	angle;
	double	plane_x;
	double	plane_y;
	bool	w;
	bool	s;
	bool	d;
	bool	a;
	bool	left;
	bool	right;
}				t_player;

typedef struct	s_cube3d
{
	void		*mlx;
	void		*win;
	char		**map;
	t_player	*player;
	t_img		*frame;
	t_parse		*parse;
	t_tex		tex[4];
	bool		close_game;
}				t_cube3d;

/* UTILS */
/* init_game */
t_cube3d	*init_game(t_parse *parse);
t_parse		*init_parser(void);
/* free_game */
bool		free_game(t_cube3d *game);
void		free_map(char **map);
void		free_parse(t_parse *parse);
/* utils */
int			ft_splitlen(char **matrix);
void		free_split(char **split);
/* RENDER */
/* window */
char		*init_mlx_components(t_cube3d *game);
int			x_pres(void *data);
void		my_mlx_pixel_put(t_cube3d *game, int x, int y, int color);
/* HOOKS */
/* key_hooks */
int			press_key(int keycode, void *data);
int			release_key(int keycode, void *data);
/* move */
void		move(t_cube3d *game);
/* RAYCASTING */
void		raycasting(t_cube3d *game);
/* PARSING */
/* parsing */
const char	*parser(t_parse *parse, char *path);
/* texture */
char		*get_extension(t_parse *parse, char **line, char *type);
/* colors */
const char	*parse_colors(t_parse *parse, char **line, char type);
/* read_map */
char		**read_map(t_parse *parse);
/* parse_map */
char		*parse_map(t_parse *parse);

#endif