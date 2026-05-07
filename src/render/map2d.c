#include "../../includes/cube3d.h"
/*
void	draw_player(t_cube3d *game, double col, double row, int color)
{
	int y;
	int x;
	int col_start;
	int row_start;


	col_start = (int)(col * SQUARE_LEN);
	row_start = (int)(row * SQUARE_LEN);
	y = 0;
	while (y < PLAYER_LEN) // el -1 es para la linea del cuadrado
	{
		x = 0;
		while (x < PLAYER_LEN)
		{
			my_mlx_pixel_put(game, col_start + x, row_start + y, color);
			x++;
		}
		y++;
	}
	//draw_flecha(game, col_start + (PLAYER_LEN / 2), row_start + (PLAYER_LEN / 2), color);
}
*/

/*
	Esta funcion hay q modificarla, ponieddole parametros
	que reciba el mapa y la longitud maxima permitida de la ventana
	para  asi rechazar en caso de error
*/

// void	get_map2d_len(t_map *map)
// {
// 	int	temp;

// 	temp = 0;
// 	if (!map->rows && !map->cols)
// 	{
// 		while (map->map[map->rows])
// 		{
// 			temp = (int)ft_strlen(map->map[map->rows]);
// 			if (map->cols < temp)
// 				map->cols = temp;
// 			map->rows++;
// 		}
// 	}
// }
/*
// y = filas x = columnas
static void	print_cube(t_cube3d *game, int row, int col, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < SQUARE_LEN - 1) // el -1 es para la linea del cuadrado
	{
		x = 0;
		while (x < SQUARE_LEN - 1)
		{
			my_mlx_pixel_put(game, (col * SQUARE_LEN) + x, (row * SQUARE_LEN) + y, color);
			x++;
		}
		y++;
	}
}

bool	map2d(t_cube3d *game)
{
	int	y;
	int	x;

	y = 0;
	get_map2d_len(game->map);
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->cols)
		{
			if (game->map->map[y][x] == '1')
				print_cube(game, y, x, GRAY);
			else
				print_cube(game, y, x, WHITE);
			x++;
		}
		y++;
	}
	return (true);
}
*/
