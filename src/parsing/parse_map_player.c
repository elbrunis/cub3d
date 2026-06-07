#include "../includes/cube3d.h"

char	*handle_player(t_parse *parse, char c, int y, int x)
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

char	*check_empty_end(char **map, int y)
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