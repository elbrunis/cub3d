#include "../../includes/cube3d.h"

bool	free_game(t_cube3d  *game)
{
	//libera explicitamente t_cube3d
	if (!game)
		return (false);
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->map)
	{
		free(game->map);
		game->map = NULL;
	}
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
	if (game->frame)
	{
		free(game->frame); //añadir aqui pa eliminar la imagen
		game->frame = NULL;
	}	
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		game->mlx =  NULL;
	}
	if (game->p)
	{
		free(game->p);
		game->p = NULL;
	}
	free(game);
	return (true);
}