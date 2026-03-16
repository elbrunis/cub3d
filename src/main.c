#include "../includes/cube3d.h"

// bucle principal del juego
static int	game_loop(void *data)
{
	t_cube3d *game = (t_cube3d *)data;
	
	return (0);
}

int	main()
{
	t_cube3d *game = init_basic();

	init_window(game);

	map2d(game);
	mlx_loop_hook(game->mlx, game_loop, (void *)game);
	mlx_loop(game->mlx);

	free_game(game);
	return (0);
}
