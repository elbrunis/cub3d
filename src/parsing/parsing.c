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


const char	*reed_and_check_map(t_cube3d *game)
{
	char		*line;
	char		*temp;
	const char	*error;
	char		*type;

	error = NULL;
	line = get_next_line(game->p->fd);
	while (line)
	{
		temp = line;
		while (*temp == ' ' || *temp == '\t')
			temp++;
		if (game->p->n_config < N_MAP_CONFIG && !error)
		{
			type = get_extension_type(temp);
			if (type)
				error = get_extension(game, &temp, type);
			else if (*temp == 'F')
				error = parse_colors(game, &temp, 'F');
			else if (*temp == 'C')
				error = parse_colors(game, &temp, 'C');
			else if (*temp != '\n' && *temp != '\0')
				error = "There is an invalid character in the map file";
		}
		free(line);
		if (error)
			return (error);
		line = get_next_line(game->p->fd);
	}
	if (line)
		free(line);
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
	return (NULL);
}
