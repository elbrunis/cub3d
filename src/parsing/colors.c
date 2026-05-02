#include "../includes/cube3d.h"

static void	rgb_to_int(t_cube3d *game, int *rgb, char type)
{
	if (type == 'F')
		game->p->floor_color =  (unsigned int)((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	if (type == 'C')
		game->p->ceiling_color = (unsigned int)((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	game->p->n_config++;
}

static int	get_color(char **line)
{
	int		i;
	int		j;
	char	str[5];
	int		num;

	i = 0;
	while (ft_isdigit(line[0][i]))
		i++;
	if (i == 0 || i > 3)
		return (-1);
	if (line[0][i] != ',' && line[0][i] != ' ' && line[0][i] != '\n')
		return (-1);
	j = 0;
	while (j < i)
	{
		str[j] = line[0][j];
		j++;
	}
	str[j] = '\0';
	num = atoi(str);
	if (num < 0 || num > 255) 
		return (-1);
	line[0] += i;
	return(num);
}

const char	*parse_colors(t_cube3d *game, char **line, char type)
{
	int	rgb[3];
	int	i;

	if ((*line)[1] != ' ' || !ft_isdigit((*line)[2]))
		return("Invalid character in the map's color values");
	(*line) += 2;
	i = 0;
	while(i < 3)
	{
		rgb[i] = get_color(line);
		if (rgb[i] < 0)
			return ("Invalid color; ensure the numeric values are correct");
		if (i < 2)
		{
			if (*(*line) != ',')
				return ("Missing comma in color");
			(*line)++;
		}
		i++;
	}
	while (**line == ' ' || **line == '\t')
		(*line)++;

	if (**line != '\0' && **line != '\n')
		return ("Invalid characters after color values");
	rgb_to_int(game, rgb, type);
	return (NULL);
}
