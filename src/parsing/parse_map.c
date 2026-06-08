/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

char	*handle_player(t_parse *parse, char c, int y, int x);
char	*check_empty_end(char **map, int y);

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
	up_len = (int)ft_strlen(map[y - 1]);
	if (x >= up_len || map[y - 1][x] == ' ')
		return ("Map is not closed");
	down_len = (int)ft_strlen(map[y + 1]);
	if (x >= down_len || map[y + 1][x] == ' ')
		return ("Map is not closed");
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

static int	skip_empty_lines(char **map)
{
	int	y;

	y = 0;
	while (map[y] && map[y][0] == '\0')
		y++;
	return (y);
}

char	*parse_map(t_parse *parse)
{
	char	**map;
	char	*err;
	int		y;

	map = read_map(parse);
	if (!map || !map[0])
		return ("Empty map");
	y = skip_empty_lines(map);
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
