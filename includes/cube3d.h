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

#define M_PI 3.14159265358979323846
// temporal security
#define WIDTH 780
#define HEIGHT 380
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define PLAYER_LEN 10
#define SQUARE_LEN 30
#define GRAY 0x808080
#define WHITE 0xFFFFFF
#define ORANGE 0xFFA500

#define N_MAP_CONFIG 6

# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100

#define SPEED 0.005
#define MOVE_ANGLE 0.005

typedef struct s_list_map
{
	char				*line;
	struct s_list_map	*next;
}				t_list_map;
/* de esta estructura falta por integrar al juego
   las variables q definen las texturas del juego
   y el color de las paredes y el suelo*/
typedef struct	s_parse
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
	bool			player_set; // verifica si el jugador tiene posicion de salida
	unsigned int	floor_color;
    unsigned int	ceiling_color;
}				t_parse;

typedef struct	s_ray
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
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
	bool w,s,d,a;
}				t_player;

typedef struct	s_cube3d
{
	void		*mlx;
	void		*win;
	char		**map;
	t_player	*player;
	t_img		*frame;
	bool		close_game;
}				t_cube3d;

//UTILS
//init_game
t_cube3d	*init_game(t_parse *parse);
t_parse	*init_parser(void); // esto igual habra q quitarlo
//free_game
bool		free_game(t_cube3d  *game);
void		free_map(char **map);
//utils
int			ft_splitlen(char **matrix);
void		free_split(char **split);
//RENDER
//window
char		*init_mlx_components(t_cube3d *game);
int			x_pres(void *data);
void		my_mlx_pixel_put(t_cube3d *game, int x, int y, int color);
//HOOKS
//key_hooks
int		press_key(int keycode, void *data);
int		release_key(int keycode, void *data);
//move
void	move(t_cube3d *game);

//RAYCASTING
void	raycasting(t_cube3d *game);
// PARSING
// parsing
const char	*parser(t_parse *parse, char *path);
// texture
char	*get_extension(t_parse *parse, char **line, char *type);
// colors
const char	*parse_colors(t_parse *parse, char **line, char type);
//reed_map
char	**read_map(t_parse *parse);
//parse map
char	*parse_map(t_parse *parse);

#endif