#include "../../includes/cube3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

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
	free(game);
	return (true);
}