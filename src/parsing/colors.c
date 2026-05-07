#include "../includes/cube3d.h"

static char	*rgb_to_int(t_parse *parse, int *rgb, char t)
{
	unsigned int	color;
	unsigned int	*dst;

	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (t == 'F')
		dst = &parse->floor_color;
	else
		dst = &parse->ceiling_color;
	if (*dst != (unsigned int)-1)
		return ("Duplicate configuration detected");
	*dst = color;
	parse->n_config++;
	return (NULL);
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

const char	*parse_colors(t_parse *parse, char **line, char type)
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
	return(rgb_to_int(parse, rgb, type));
}
