#include "../../includes/cube3d.h"

static int	is_wall(t_cube3d *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || !game->map[map_y])
		return (1);
	if (map_x < 0 || map_x >= (int)ft_strlen(game->map[map_y]))
		return (1);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
		return (1);
	return (0);
}

static void	move_front(t_cube3d *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = game->player;
	new_x = p->x_pos + (p->dir_x * SPEED);
	new_y = p->y_pos + (p->dir_y * SPEED);
	if (!is_wall(game, new_x, p->y_pos))
		p->x_pos = new_x;
	if (!is_wall(game, p->x_pos, new_y))
		p->y_pos = new_y;
}

static void	move_back(t_cube3d *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = game->player;
	new_x = p->x_pos - (p->dir_x * SPEED);
	new_y = p->y_pos - (p->dir_y * SPEED);
	if (!is_wall(game, new_x, p->y_pos))
		p->x_pos = new_x;
	if (!is_wall(game, p->x_pos, new_y))
		p->y_pos = new_y;
}

static void	strafe_left(t_cube3d *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = game->player;
	new_x = p->x_pos - (p->dir_y * SPEED);
	new_y = p->y_pos + (p->dir_x * SPEED);
	if (!is_wall(game, new_x, p->y_pos))
		p->x_pos = new_x;
	if (!is_wall(game, p->x_pos, new_y))
		p->y_pos = new_y;
}

static void	strafe_right(t_cube3d *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = game->player;
	new_x = p->x_pos + (p->dir_y * SPEED);
	new_y = p->y_pos - (p->dir_x * SPEED);
	if (!is_wall(game, new_x, p->y_pos))
		p->x_pos = new_x;
	if (!is_wall(game, p->x_pos, new_y))
		p->y_pos = new_y;
}

static void	rotate_left(t_player *p)
{
	p->angle -= MOVE_ANGLE;
	if (p->angle < 0)
		p->angle += 2 * M_PI;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
	p->plane_x = -0.66 * sin(p->angle);
	p->plane_y = 0.66 * cos(p->angle);
}

static void	rotate_right(t_player *p)
{
	p->angle += MOVE_ANGLE;
	if (p->angle > 2 * M_PI)
		p->angle -= 2 * M_PI;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
	p->plane_x = -0.66 * sin(p->angle);
	p->plane_y = 0.66 * cos(p->angle);
}

void	move(t_cube3d *game)
{
	if (game->player->left)
		rotate_left(game->player);
	if (game->player->right)
		rotate_right(game->player);
	if (game->player->w)
		move_front(game);
	if (game->player->s)
		move_back(game);
	if (game->player->a)
		strafe_left(game);
	if (game->player->d)
		strafe_right(game);
}
