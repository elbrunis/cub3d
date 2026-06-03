#include "../includes/cube3d.h"

static char	*handle_player(t_parse *parse, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (parse->player_set)
			return ("There is more than one player on the map");
		parse->player_set = true;
		parse->x_pos = (double)x + 0.5;
		parse->y_pos = (double)y + 0.5;
		if (c == 'N')
			parse->angle = (3 * M_PI) / 2;
		else if (c == 'S')
			parse->angle = M_PI / 2;
		else if (c == 'E')
			parse->angle = 0;
		else if (c == 'W')
			parse->angle = M_PI;
	}
	return (NULL);
}

static char	*check_cell(char **map, int y, int x)
{
	int	len;
	int	up_len;
	int	down_len;

	len = (int)ft_strlen(map[y]);
	if (x == 0 || x == len - 1 || y == 0 || map[y + 1] == NULL)
		return ("Map is not closed");
	if (map[y][x + 1] == ' ' || map[y][x + 1] == '\0')
		return ("Map is not closed");
	if (map[y][x - 1] == ' ')
		return ("Map is not closed");
	if (y > 0)
	{
		up_len = (int)ft_strlen(map[y - 1]);
		if (x < up_len && map[y - 1][x] == ' ')
			return ("Map is not closed");
	}
	if (map[y + 1])
	{
		down_len = (int)ft_strlen(map[y + 1]);
		if (x < down_len && map[y + 1][x] == ' ')
			return ("Map is not closed");
	}
	return (NULL);
}

static char	*check_line(t_parse *parse, char **map, int y)
{
	int		x;
	char	*error;

	x = 0;
	while (map[y][x])
	{
		if (!ft_strchr("NSEW10 ", map[y][x]))
			return ("invalid char in the map");
		if (map[y][x] == '0' || ft_strchr("NSEW", map[y][x]))
		{
			error = check_cell(map, y, x);
			if (error)
				return (error);
			error = handle_player(parse, map[y][x], y, x);
			if (error)
				return (error);
		}
		x++;
	}
	return (NULL);
}

static char	*check_empty_end(char **map, int y)
{
	int	x;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != ' ' && map[y][x] != '\n')
				return ("invalid char after map");
			x++;
		}
		y++;
	}
	return (NULL);
}

char	*parse_map(t_parse *parse)
{
	char	**map;
	char	*err;
	int		y;

	map = read_map(parse);
	if (!map || !map[0])
		return ("Empty map");
	y = 0;
	while (map[y] && map[y][0] == '\0')
		y++;
	while (map[y] && map[y][0] != '\0')
	{
		err = check_line(parse, map, y);
		if (err)
		{
			free_map(map);
			return (err);
		}
		y++;
	}
	err = check_empty_end(map, y);
	if (err)
	{
		free_map(map);
		return (err);
	}
	if (!parse->player_set)
	{
		free_map(map);
		return ("Missing player");
	}
	parse->map = map;
	return (NULL);
}

