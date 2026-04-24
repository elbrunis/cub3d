#include "../includes/cube3d.h"

static void	move_front(t_cube3d *game)
{
	t_player *player;
	
	player = game->player;
	player->x_pos = player->x_pos + (player->dir_x * SPEED);
	player->y_pos = player->y_pos + (player->dir_y * SPEED);
}

static void	move_right(t_player *player)
{
	player->angle += MOVE_ANGLE; // Aumentamos el ángulo
	if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;

	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -0.66 * sin(player->angle);
	player->plane_y = 0.66 * cos(player->angle);
}

static void	move_left(t_player *player)
{
	player->angle -= MOVE_ANGLE;
	if (player->angle < 0)
		player->angle += 2 * M_PI;

	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -0.66 * sin(player->angle);
	player->plane_y = 0.66 * cos(player->angle);
}

//falta el de pa mover para atras
void	move(t_cube3d *game)
{
	if (game->player->a)
		move_left(game->player);
	if (game->player->d)
		move_right(game->player);
	if (game->player->w)
		move_front(game);
}
