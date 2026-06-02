#include "../../includes/cube3d.h"

int	press_key(int keycode, void *data)
{
	t_cube3d	*game;

	game = (t_cube3d *)data;
	if (keycode == K_ESC)
		game->close_game = true;
	if (keycode == K_A)
		game->player->a = true;
	if (keycode == K_S)
		game->player->s = true;
	if (keycode == K_W)
		game->player->w = true;
	if (keycode == K_D)
		game->player->d = true;
	if (keycode == K_LEFT)
		game->player->left = true;
	if (keycode == K_RIGHT)
		game->player->right = true;
	return (0);
}

int	release_key(int keycode, void *data)
{
	t_cube3d	*game;

	game = (t_cube3d *)data;
	if (keycode == K_A)
		game->player->a = false;
	if (keycode == K_S)
		game->player->s = false;
	if (keycode == K_W)
		game->player->w = false;
	if (keycode == K_D)
		game->player->d = false;
	if (keycode == K_LEFT)
		game->player->left = false;
	if (keycode == K_RIGHT)
		game->player->right = false;
	return (0);
}
