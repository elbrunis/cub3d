#include "../includes/cube3d.h"

static char	*get_extension_type(char *line)
{
	int len;

	len = ft_strlen(line);
	if (!line || len < 2)
		return (NULL);
	if (!ft_strncmp(line, "NO", 2))
		return ("NO");
	if (!ft_strncmp(line, "SO", 2))
		return ("SO");
	if (!ft_strncmp(line, "WE", 2))
		return ("WE");
	if (!ft_strncmp(line, "EA", 2))
		return ("EA");
	return (NULL);
}
static const char	*parse_line(t_parse *parse, char *temp)
{
	char	*type;

	type = get_extension_type(temp);
	if (type)
		return (get_extension(parse, &temp, type));
	else if (*temp == 'F' || *temp == 'C')
		return (parse_colors(parse, &temp, *temp));
	else if (*temp != '\n' && *temp != '\0')
		return ("There is an invalid character in the map file");
	return (NULL);
}

static const char	*read_and_check_map(t_parse *parse)
{
	char		*line;
	char		*temp;
	const char	*error;

	while (parse->n_config < N_MAP_CONFIG)
	{
		line = get_next_line(parse->fd);
		if (!line)
			break ;
		temp = line;
		while (*temp == ' ' || *temp == '\t')
			temp++;
		if (*temp && *temp != '\n')
		{
			error = parse_line(parse, temp);
			if (error)
				return (free(line), error);
		}
		free(line);
	}
	return (NULL);
}

const char	*validate_file(t_parse *parse, char *path)
{
	int	len;

	len = (int)ft_strlen(path);
	if (len < 5 || (path[len - 1] != 'b' || path[len - 2] != 'u' 
			|| path[len - 3] != 'c' || path[len - 4] != '.'))
		return ("Invalid extension");
	parse->fd = open(path, O_RDONLY);
	if(parse->fd < 0)
		return ("The file could not be opened correctly");
	return(NULL);
}

const char	*parser(t_parse *parse, char *path)
{
	const char	*error;

	error = validate_file(parse, path);
	if(error)
		return(error);
	error = read_and_check_map(parse);
	if(error)
	{
		close(parse->fd);
		return(error);
	}
	if (parse->n_config < N_MAP_CONFIG)
		return("Missing configurations");
	error = parse_map(parse);
	close(parse->fd);
	if(error)
		return(error);
	return (NULL);
}
