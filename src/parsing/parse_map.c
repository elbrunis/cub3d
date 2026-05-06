#include "../includes/cube3d.h"


static char	*handle_player(t_cube3d *game, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (game->p->player_set)
			return ("There is more than one player on the map");
		game->p->player_set = true;
		game->player->x_pos = (double)x + 0.5;
		game->player->y_pos = (double)y + 0.5;
		if (c == 'N')
			game->player->angle = (3 * M_PI) / 2;
		else if (c == 'S')
			game->player->angle = M_PI / 2;
		else if (c == 'E')
			game->player->angle = 0;
		else if (c == 'W')
			game->player->angle = M_PI;
	}
	return (NULL);
}

static char	*check_position(t_cube3d *game, char **map, int y, int x)
{
	int	len;

	len = (int)ft_strlen(map[y]);
	if (y == 0 || map[y + 1] == NULL || x == 0 || x == len - 1)
		return ("Map open at the edges");
	if (map[y][x + 1] == ' ' || map[y][x - 1] == '\0')
		return ("Map open at the sides");
	if ((int)ft_strlen(map[y - 1]) <= x || map[y - 1][x] == ' '
		|| map[y - 1][x] == '\0')
		return ("Map open at the top");
	if ((int)ft_strlen(map[y + 1]) <= x || map[y + 1][x] == ' '
		|| map[y + 1][x] == '\0')
		return ("Map open at the bottom");
	if (map[y][x] != '0')
		return (handle_player(game, map[y][x], y, x));
	return (NULL);
}

static char	*check_line(t_cube3d *game, char **map, int y)
{
	int		x;
	char	*error;

	x = 0;
	while (map[y][x])
	{
		if (!ft_strchr("NSEW10 ", map[y][x]))
			return ("invalid char in de map");
		if (map[y][x] == '0'|| ft_strchr("NSEW", map[y][x]))
		{
			error = check_position(game, map, y, x);
			if (error)
				return (error);
		}
		x++;
	}
	return (NULL);
}


char	*parse_map(t_cube3d *game)
{
	char	**map;
	char	*error;
	int		y;
	bool	start_map;
	int		x;

	map = read_map(game);
	if (!map || !map[0])
		return ("Empty map");
	y = 0;
	start_map = false;
	while (map[y])
	{
		if (map[y][0]  != '\0')
		{
			start_map = true;
			error = check_line(game, map, y);
			if (error)
			{
				free_map(map);
				return (error);
			}
			y++;
		}
		else if (!start_map)
			y++;
		else
			break;
	}
	x = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] != ' ')
				return ("invalid char");
			x++;
		}
		y++;
	}
	
	if (!game->p->player_set)
		return ("Missing player");
	return (NULL);
}
