#include "../../includes/cube3d.h"

/*
	Esta funcion de momrnto es pequeña pero se ampliara
	en un futuro haciendo todas las comprobaciones etc
	para calcular el verdadero tamaño
*/
void	init_window(t_cube3d *game)
{
	game->mlx = mlx_init();
	// el tamaño de la ventana es temporal
	game->win = mlx_new_window(game->mlx, 1000, 1000, "Ventana principal");
}