#include "../includes/cube3d.h"

/*
	Eventos cuando se PULSA la tecla
*/
int	press_key(int keycode, void *data)
{
	t_player *player;

	player = (t_player *)data;
	if (keycode == K_A)
		player->a = true;
	if (keycode == K_S)
		player->s = true;
	if (keycode == K_W)
		player->w = true;
	if (keycode == K_D)
		player->d = true;
	return (0);
}

/*
	Eventos cuando se SUELTA la tecla
*/
int	relase_key(int keycode, void *data)
{
	t_player *player = (t_player *)data;

	if (keycode == K_A)
		player->a = false;
	if (keycode == K_S)
		player->s = false;
	if (keycode == K_W)
		player->w = false;
	if (keycode == K_D)
		player->d = false;
	return (0);
}
