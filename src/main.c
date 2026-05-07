#include "../includes/cube3d.h"

// bucle principal del juego

/*
	!!!ESTA TODO COMENTADO TEMPORALMENTE!!!
*/

static int	game_loop(void *data)
{
	t_cube3d *game = (t_cube3d *)data;
	if	(game->close_game)
	{
		free_game(game);
		exit(0);
	}
	move(game);
	//map2d(game);
	// get_map2d_len(game->map);
	raycasting(game);
	//draw_player(game, game->player->x_pos, game->player->y_pos, ORANGE);
	mlx_put_image_to_window(game->mlx, game->win, game->frame->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube3d	*game;
	t_parse		*parse;

	if (argc != 2)
		return(printf("Error missing arguments\n"));
	parse = init_parser();
	const char *error = parser(parse, argv[1]);
	if (error)
		return(printf("Error\n%s: %s\n", error, strerror(errno)));
	game = init_game(parse);
	if (!game)
		return(1);

	//rellenar lo restante de estas funciones
	mlx_hook(game->win, 2, 1L<<0, press_key, (void *)game->player);
	mlx_hook(game->win, 3, 1L<<1, release_key, (void *)game->player);
	// esta funcion la he guardadop donde la ventana ya q es la de cerrar la ventana
	mlx_hook(game->win, 17, 0, x_pres, (void *)game);

	mlx_loop_hook(game->mlx, game_loop, (void *)game);
	mlx_loop(game->mlx);

	free_game(game);
	return (0);
}

// #include "../includes/cube3d.h"

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return(printf("Error missing arguments\n"));
// 	t_parse *parse = init_parser();
// 	const char *error = parser(parse, argv[1]);
// 	if (error)
// 		return(printf("Error\n%s: %s\n", error, strerror(errno)));
// 	return (0);
// }
