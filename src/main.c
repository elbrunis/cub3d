#include "../includes/cube3d.h"

// bucle principal del juego

/*
	!!!ESTA TODO COMENTADO TEMPORALMENTE!!!
*/

// static int	game_loop(void *data)
// {
// 	t_cube3d *game = (t_cube3d *)data;
// 	if	(game->close_game)
// 	{
// 		free_game(game);
// 		exit(0);
// 	}
// 	move(game);
// 	//map2d(game);
// 	get_map2d_len(game->map);
// 	raycasting(game);
// 	//draw_player(game, game->player->x_pos, game->player->y_pos, ORANGE);
// 	mlx_put_image_to_window(game->mlx, game->win, game->frame->img, 0, 0);
// 	return (0);
// }

void	debug_print_parser(t_cube3d *game)
{
	if (!game || !game->p)
	{
		printf("Error: Estructura de parseo no inicializada.\n");
		return ;
	}
	printf("--- DEBUG PARSER ---\n");
	printf("NO Path:  [%s]\n", game->p->no_path ? game->p->no_path : "NULL");
	printf("SO Path:  [%s]\n", game->p->so_path ? game->p->so_path : "NULL");
	printf("WE Path:  [%s]\n", game->p->we_path ? game->p->we_path : "NULL");
	printf("EA Path:  [%s]\n", game->p->ea_path ? game->p->ea_path : "NULL");
	printf("Floor:    Hex: 0x%06X | Dec: %u\n", game->p->floor_color, game->p->floor_color);
	printf("Ceiling:  Hex: 0x%06X | Dec: %u\n", game->p->ceiling_color, game->p->ceiling_color);
	printf("--------------------\n");
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return(printf("Error missing arguments\n"));
	t_cube3d *game = init_basic();
	const char *error = parser(game, argv[1]);
	if (error)
		return(printf("Error\n%s: %s\n", error, strerror(errno)));
	debug_print_parser(game);
	free_game(game); // CUIDADO CUANDO DESSCOMENTES LO DEMAS POR Q TIENES Q ELIMINAR ESTE FREE

// 	//rellenar lo restante de estas funciones
// 	mlx_hook(game->win, 2, 1L<<0, press_key, (void *)game->player);
// 	mlx_hook(game->win, 3, 1L<<1, release_key, (void *)game->player);
// 	// esta funcion la he guardadop donde la ventana ya q es la de cerrar la ventana
// 	mlx_hook(game->win, 17, 0, x_pres, (void *)game);

// 	mlx_loop_hook(game->mlx, game_loop, (void *)game);
// 	mlx_loop(game->mlx);

// 	free_game(game);
	return (0);
}
