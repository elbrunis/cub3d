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
static const char	*parse_line(t_cube3d *game, char *temp)
{
	char	*type;

	type = get_extension_type(temp);
	if (type)
		return (get_extension(game, &temp, type));
	else if (*temp == 'F' || *temp == 'C')
		return (parse_colors(game, &temp, *temp));
	else if (*temp != '\n' && *temp != '\0')
		return ("There is an invalid character in the map file");
	return (NULL);
}

static const char	*reed_and_check_map(t_cube3d *game)
{
	char		*line;
	char		*temp;
	const char	*error;

	while (game->p->n_config < N_MAP_CONFIG)
	{
		line = get_next_line(game->p->fd);
		if (!line)
			break ;
		temp = line;
		while (*temp == ' ' || *temp == '\t')
			temp++;
		if (*temp && *temp != '\n')
		{
			error = parse_line(game, temp);
			if (error)
				return (free(line), error);
		}
		free(line);
	}
	return (NULL);
}

const char	*validate_file(t_cube3d *game, char *path)
{
	int	len;

	len = (int)ft_strlen(path);
	if (len < 5 || (path[len - 1] != 'b' || path[len - 2] != 'u' 
			|| path[len - 3] != 'c' || path[len - 4] != '.'))
		return ("Invalid extension");
	game->p->fd = open(path, O_RDONLY);
	if(game->p->fd < 0)
		return ("The file could not be opened correctly");
	return(NULL);
}

const char	*parser(t_cube3d *game, char *path)
{
	const char	*error;

	error = validate_file(game, path);
	if(error)
		return(error);
	error = reed_and_check_map(game);
	if(error)
	{
		close(game->p->fd);
		return(error);
	}
	if (game->p->n_config < N_MAP_CONFIG)
		return("Missing configurations");
	error = parse_map(game);
	if(error)
	{
		close(game->p->fd);
		return(error);
	}
	return (NULL);
}
