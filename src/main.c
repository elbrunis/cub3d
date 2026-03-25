#include "../includes/cube3d.h"

// bucle principal del juego
static int	game_loop(void *data)
{
	t_cube3d *game = (t_cube3d *)data;
	if	(game->close_game)
	{
		free_game(game);
		exit(0);
	}
	move(game);
	map2d(game);
	return (0);
}

int	main()
{
	t_cube3d *game = init_basic();
	

	//rellenar lo restante de estas funciones
	mlx_hook(game->win, 2, 1L<<0, press_key, (void *)game->player);
	mlx_hook(game->win, 3, 1L<<1, relase_key, (void *)game->player);
	// esta funcion la he guardadop donde la ventana ya q es la de cerrar la ventana
	mlx_hook(game->win, 17, 0, x_pres, (void *)game);

	mlx_loop_hook(game->mlx, game_loop, (void *)game);
	mlx_loop(game->mlx);

	free_game(game);
	return (0);
}
