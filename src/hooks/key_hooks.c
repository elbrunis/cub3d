#include "../includes/cube3d.h"


void	move(t_cube3d *game)
{
	t_player *player;
	
	player = game->player;
	player->x_pos = player->x_pos + (player->x_pos * SPEED);
	player->y_pos = player->y_pos + (player->y_pos * SPEED);
}

/*
	Eventos cuando se PULSA la tecla
*/
int	press_key(int keycode, void *data)
{
	t_player *player = (t_player *)data;

	if (keycode == K_W)
		player->w = true;
	if (keycode == K_A)
		player->s = true;
	if (keycode == K_S)
		player->d = true;
	if (keycode == K_D)
		player->a = true;
	return (0);
}

/*
	Eventos cuando se SUELTA la tecla
*/
int	relase_key(int keycode, void *data)
{
	t_player *player = (t_player *)data;

	if (keycode == K_W)
		player->w = false;
	if (keycode == K_A)
		player->s = false;
	if (keycode == K_S)
		player->d = false;
	if (keycode == K_D)
		player->a = false;
	return (0);
}
