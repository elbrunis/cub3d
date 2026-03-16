#include "../../includes/cube3d.h"

/*
	Esta funcion hay q modificarla, ponieddole parametros
	que reciba el mapa y la longitud maxima permitida de la ventana
	para  asi rechazar en caso de error
*/
static void	get_map2d_len(t_map *map)
{
	int	temp;

	temp = 0;
	if (!map->rows && !map->cols)
	{
		while (map->map[map->rows])
		{
			temp = (int)ft_strlen(map->map[map->rows]);
			if (map->cols < temp)
				map->cols = temp;
			map->rows++;
		}
	}
}
// y = filas x = columnas
static void	print_cube(t_cube3d *game, int row, int col, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < SQUARE_LEN - 1)
	{
		x = 0;
		while (x < SQUARE_LEN - 1)
		{
			mlx_pixel_put(game->mlx, game->win, (col * SQUARE_LEN) + x, (row * SQUARE_LEN) + y, color);
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
	printf("hola");
	mlx_pixel_put(game->mlx, game->win, 50, 50, 0xFF0000);
	get_map2d_len(game->map);
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->cols)
		{
			if (game->map->map[y][x] == '1')
				print_cube(game, y, x, 0x808080);
			else
				print_cube(game, y, x, 0xFFFFFF);
			x++;
		}
		y++;
	}
	return (true);
}
