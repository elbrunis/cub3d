#ifndef CUBE3D_H
# define CUBE3D_H

#include "../minilibx-linux/mlx.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// temporal security
#define WIDTH 780
#define HEIGHT 380

#define PLAYER_LEN 10
#define SQUARE_LEN 30
#define GRAY 0x808080
#define WHITE 0xFFFFFF
#define ORANGE 0xFFA500

# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100

#define SPEED 0.05


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
	bool w,s,d,a;
}				t_player;

typedef struct	s_map
{
	char	**map;
	int		rows;
	int		cols;
}				t_map;

typedef struct	s_cube3d
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	*player;
	t_img		*frame;
	bool		close_game;
}				t_cube3d;

//UTILS
//init_game
t_cube3d	*init_basic(void);
//free_game
bool		free_game(t_cube3d  *game);
//RENDER
//window
void		init_window(t_cube3d *game);
int			x_pres(void *data);
void		my_mlx_pixel_put(t_cube3d *game, int x, int y, int color);
//map2d
bool		map2d(t_cube3d *game);
//HOOKS
//key_hooks
int		press_key(int keycode, void *data);
int		relase_key(int keycode, void *data);

#endif