#include "../../includes/cube3d.h"

/*
	Esta funcion de momrnto es pequeña pero se ampliara
	en un futuro haciendo todas las comprobaciones etc
	para calcular el verdadero tamaño
*/
void	my_mlx_pixel_put(t_cube3d *game, int x, int y, int color)
{
	char *dst;

	dst = game->frame->addr + (y * game->frame->line_length + x * (game->frame->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int		x_pres(void *data)
{
	t_cube3d *game = (t_cube3d *)data;
	game->close_game = true;
	return (0);
}

void	init_window(t_cube3d *game)
{
	game->mlx = mlx_init();
	// el tamaño de la ventana es temporal
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Ventana principal");
}