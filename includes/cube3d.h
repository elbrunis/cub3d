#ifndef CUBE3D_H
# define CUBE3D_H

#include "../minilibx-linux/mlx.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define SQUARE_LEN 30
#define BLACK 0
#define WHITE 16777215

typedef struct	s_map
{
	char	**map;
	int		rows;
	int		cols;
}				t_map;

typedef struct	s_cube3d
{
	void	*mlx;
	void	*win;
	t_map	*map;
}				t_cube3d;

//init_game
t_cube3d	*init_basic(void);
// utils
bool		free_game(t_cube3d  *game);
//window
void		init_window(t_cube3d *game); 
//map2d
bool	map2d(t_cube3d *game);

#endif