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

int	is_blocked(t_cube3d *game, double x, double y)
{
	if (is_wall(game, x - COLLISION_MARGIN, y - COLLISION_MARGIN))
		return (1);
	if (is_wall(game, x + COLLISION_MARGIN, y - COLLISION_MARGIN))
		return (1);
	if (is_wall(game, x - COLLISION_MARGIN, y + COLLISION_MARGIN))
		return (1);
	if (is_wall(game, x + COLLISION_MARGIN, y + COLLISION_MARGIN))
		return (1);
	return (0);
}