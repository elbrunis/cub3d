#include "../../includes/cube3d.h"

bool	free_game(t_cube3d  *game)
{
	//libera explicitamente t_cube3d
	if (game)
	{
		mlx_destroy_window(game->mlx, game->win);

		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}